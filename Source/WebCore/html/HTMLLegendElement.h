/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2004, 2005, 2006, 2010 Apple Inc. All rights reserved.
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
 *
 */

#ifndef HTMLLegendElement_h
#define HTMLLegendElement_h

#include "HTMLElement.h"

namespace WebCore {

class HTMLFormControlElement;

class HTMLLegendElement FINAL : public HTMLElement {
public:
    static PassRefPtr<HTMLLegendElement> create(const QualifiedName&, Document*);

private:
    HTMLLegendElement(const QualifiedName&, Document*);

    // Control in the legend's fieldset that gets focus and access key.
    HTMLFormControlElement* associatedControl();

    virtual void accessKeyAction(bool sendMouseEvents);
    virtual void focus(bool restorePreviousSelection, FocusDirection) OVERRIDE;
    virtual HTMLFormElement* virtualForm() const OVERRIDE;
};

inline bool isHTMLLegendElement(const Node* node)
{
    return node->hasTagName(HTMLNames::legendTag);
}

inline bool isHTMLLegendElement(const Element* element)
{
    return element->hasTagName(HTMLNames::legendTag);
}

template <> inline bool isElementOfType<HTMLLegendElement>(const Element* element) { return isHTMLLegendElement(element); }

} //namespace

#endif
