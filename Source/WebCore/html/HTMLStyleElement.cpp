/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2001 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2003, 2010, 2013 Apple Inc. All rights reserved.
 *           (C) 2007 Rob Buis (buis@kde.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "HTMLStyleElement.h"

#include "Attribute.h"
#include "Document.h"
#include "Event.h"
#include "EventSender.h"
#include "HTMLNames.h"
#include "MediaList.h"
#include "RuntimeEnabledFeatures.h"
#include "ScriptableDocumentParser.h"
#include "ShadowRoot.h"
#include "StyleSheetContents.h"

namespace WebCore {

using namespace HTMLNames;

static StyleEventSender& styleLoadEventSender()
{
    DEFINE_STATIC_LOCAL(StyleEventSender, sharedLoadEventSender, (eventNames().loadEvent));
    return sharedLoadEventSender;
}

inline HTMLStyleElement::HTMLStyleElement(const QualifiedName& tagName, Document& document, bool createdByParser)
    : HTMLElement(tagName, document)
    , m_styleSheetOwner(document, createdByParser)
    , m_firedLoad(false)
    , m_loadedSheet(false)
#if ENABLE(STYLE_SCOPED)
    , m_scopedStyleRegistrationState(NotRegistered)
#endif
{
    ASSERT(hasTagName(styleTag));
}

HTMLStyleElement::~HTMLStyleElement()
{
    // During tear-down, willRemove isn't called, so m_scopedStyleRegistrationState may still be RegisteredAsScoped or RegisteredInShadowRoot here.
    // Therefore we can't ASSERT(m_scopedStyleRegistrationState == NotRegistered).
    m_styleSheetOwner.clearDocumentData(&document(), this);

    styleLoadEventSender().cancelEvent(this);
}

PassRefPtr<HTMLStyleElement> HTMLStyleElement::create(const QualifiedName& tagName, Document& document, bool createdByParser)
{
    return adoptRef(new HTMLStyleElement(tagName, document, createdByParser));
}

void HTMLStyleElement::parseAttribute(const QualifiedName& name, const AtomicString& value)
{
    if (name == titleAttr && sheet())
        sheet()->setTitle(value);
#if ENABLE(STYLE_SCOPED)
    else if (name == scopedAttr && RuntimeEnabledFeatures::styleScopedEnabled())
        scopedAttributeChanged(!value.isNull());
#endif
    else if (name == mediaAttr) {
        m_styleSheetOwner.setMedia(value);
        if (sheet()) {
            sheet()->setMediaQueries(MediaQuerySet::createAllowingDescriptionSyntax(value));
            if (inDocument() && document().hasLivingRenderTree())
                document().styleResolverChanged(RecalcStyleImmediately);
        }
    } else if (name == typeAttr)
        m_styleSheetOwner.setContentType(value);
    else
        HTMLElement::parseAttribute(name, value);
}

void HTMLStyleElement::finishParsingChildren()
{
    m_styleSheetOwner.finishParsingChildren(this);
    HTMLElement::finishParsingChildren();
}

#if ENABLE(STYLE_SCOPED)
void HTMLStyleElement::scopedAttributeChanged(bool scoped)
{
    ASSERT(RuntimeEnabledFeatures::styleScopedEnabled());

    if (!inDocument())
        return;

    if (scoped) {
        // As any <style> in a shadow tree is treated as "scoped",
        // need to remove the <style> from its shadow root.
        if (m_scopedStyleRegistrationState == RegisteredInShadowRoot)
            unregisterWithScopingNode(containingShadowRoot());

        if (m_scopedStyleRegistrationState != RegisteredAsScoped)
            registerWithScopingNode(true);
        return;
    }

    // If the <style> was scoped, need to remove the <style> from the scoping
    // element, i.e. the parent node.
    if (m_scopedStyleRegistrationState == RegisteredAsScoped)
        unregisterWithScopingNode(parentNode());

    // As any <style> in a shadow tree is treated as "scoped",
    // need to add the <style> to its shadow root.
    if (isInShadowTree() && m_scopedStyleRegistrationState != RegisteredInShadowRoot)
        registerWithScopingNode(false);
}

void HTMLStyleElement::registerWithScopingNode(bool scoped)
{
    // Note: We cannot rely on the 'scoped' element already being present when this method is invoked.
    // Therefore we cannot rely on scoped()!
    ASSERT(m_scopedStyleRegistrationState == NotRegistered);
    ASSERT(inDocument());
    if (m_scopedStyleRegistrationState != NotRegistered)
        return;

    ContainerNode* scope = scoped ? parentNode() : containingShadowRoot();
    if (!scope)
        return;
    if (!scope->isElementNode() && !scope->isShadowRoot()) {
        // DocumentFragment nodes should never be inDocument,
        // <style> should not be a child of Document, PI or some such.
        ASSERT_NOT_REACHED();
        return;
    }
    scope->registerScopedHTMLStyleChild();
    if (scope->isShadowRoot())
        scope->shadowHost()->setNeedsStyleRecalc();
    else
        scope->setNeedsStyleRecalc();
    if (inDocument() && !document().parsing() && document().hasLivingRenderTree())
        document().styleResolverChanged(DeferRecalcStyle);

    m_scopedStyleRegistrationState = scoped ? RegisteredAsScoped : RegisteredInShadowRoot;
}

void HTMLStyleElement::unregisterWithScopingNode(ContainerNode* scope)
{
    ASSERT(m_scopedStyleRegistrationState != NotRegistered || !RuntimeEnabledFeatures::styleScopedEnabled());
    if (!isRegisteredAsScoped())
        return;

    ASSERT(scope);
    if (scope) {
        ASSERT(scope->hasScopedHTMLStyleChild());
        scope->unregisterScopedHTMLStyleChild();
        scope->setNeedsStyleRecalc();
    }
    if (inDocument() && !document().parsing() && document().hasLivingRenderTree())
        document().styleResolverChanged(DeferRecalcStyle);

    m_scopedStyleRegistrationState = NotRegistered;
}

bool HTMLStyleElement::scoped() const
{
    return RuntimeEnabledFeatures::styleScopedEnabled() && fastHasAttribute(scopedAttr);
}

void HTMLStyleElement::setScoped(bool scopedValue)
{
    setBooleanAttribute(scopedAttr, scopedValue);
}

Element* HTMLStyleElement::scopingElement() const
{
    if (!scoped())
        return 0;

    // FIXME: This probably needs to be refined for scoped stylesheets within shadow DOM.
    // As written, such a stylesheet could style the host element, as well as children of the host.
    // OTOH, this paves the way for a :bound-element implementation.
    ContainerNode* parentOrShadowHost = parentOrShadowHostNode();
    if (!parentOrShadowHost || !parentOrShadowHost->isElementNode())
        return 0;

    return toElement(parentOrShadowHost);
}
#endif // ENABLE(STYLE_SCOPED)

Node::InsertionNotificationRequest HTMLStyleElement::insertedInto(ContainerNode* insertionPoint)
{
    HTMLElement::insertedInto(insertionPoint);
    if (insertionPoint->inDocument()) {
        m_styleSheetOwner.insertedIntoDocument(&document(), this);
#if ENABLE(STYLE_SCOPED)
        if (m_scopedStyleRegistrationState == NotRegistered && (scoped() || isInShadowTree()))
            registerWithScopingNode(scoped());
#endif
    }

    return InsertionDone;
}

void HTMLStyleElement::removedFrom(ContainerNode* insertionPoint)
{
    HTMLElement::removedFrom(insertionPoint);

#if ENABLE(STYLE_SCOPED)
    // In the current implementation, <style scoped> is only registered if the node is in the document.
    // That is, because willRemove() is also called if an ancestor is removed from the document.
    // Now, if we want to register <style scoped> even if it's not inDocument,
    // we'd need to find a way to discern whether that is the case, or whether <style scoped> itself is about to be removed.
    if (m_scopedStyleRegistrationState != NotRegistered) {
        ContainerNode* scope;
        if (m_scopedStyleRegistrationState == RegisteredInShadowRoot) {
            scope = containingShadowRoot();
            if (!scope)
                scope = insertionPoint->containingShadowRoot();
        } else
            scope = parentNode() ? parentNode() : insertionPoint;
        unregisterWithScopingNode(scope);
    }
#endif

    if (insertionPoint->inDocument())
        m_styleSheetOwner.removedFromDocument(&document(), this);
}

void HTMLStyleElement::childrenChanged(const ChildChange& change)
{
    HTMLElement::childrenChanged(change);
    m_styleSheetOwner.childrenChanged(this);
}

void HTMLStyleElement::dispatchPendingLoadEvents()
{
    styleLoadEventSender().dispatchPendingEvents();
}

void HTMLStyleElement::dispatchPendingEvent(StyleEventSender* eventSender)
{
    ASSERT_UNUSED(eventSender, eventSender == &styleLoadEventSender());
    if (m_loadedSheet)
        dispatchEvent(Event::create(eventNames().loadEvent, false, false));
    else
        dispatchEvent(Event::create(eventNames().errorEvent, false, false));
}

void HTMLStyleElement::notifyLoadedSheetAndAllCriticalSubresources(bool errorOccurred)
{
    if (m_firedLoad)
        return;
    m_loadedSheet = !errorOccurred;
    styleLoadEventSender().dispatchEventSoon(this);
    m_firedLoad = true;
}

void HTMLStyleElement::addSubresourceAttributeURLs(ListHashSet<KURL>& urls) const
{    
    HTMLElement::addSubresourceAttributeURLs(urls);

    if (CSSStyleSheet* styleSheet = const_cast<HTMLStyleElement*>(this)->sheet())
        styleSheet->contents()->addSubresourceStyleURLs(urls);
}

bool HTMLStyleElement::disabled() const
{
    if (!sheet())
        return false;

    return sheet()->disabled();
}

void HTMLStyleElement::setDisabled(bool setDisabled)
{
    if (CSSStyleSheet* styleSheet = sheet())
        styleSheet->setDisabled(setDisabled);
}

}
