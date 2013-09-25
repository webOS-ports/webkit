/*
 * Copyright (C) 2004, 2005, 2006, 2007 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2006 Rob Buis <buis@kde.org>
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

#ifndef SVGFilterPrimitiveStandardAttributes_h
#define SVGFilterPrimitiveStandardAttributes_h

#if ENABLE(SVG) && ENABLE(FILTERS)
#include "RenderSVGResourceFilter.h"
#include "RenderSVGResourceFilterPrimitive.h"
#include "SVGAnimatedLength.h"
#include "SVGAnimatedString.h"
#include "SVGElement.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>

namespace WebCore {

class Filter;
class FilterEffect;
class SVGFilterBuilder;

class SVGFilterPrimitiveStandardAttributes : public SVGElement {
public:
    void setStandardAttributes(FilterEffect*) const;

    virtual PassRefPtr<FilterEffect> build(SVGFilterBuilder*, Filter* filter) = 0;
    // Returns true, if the new value is different from the old one.
    virtual bool setFilterEffectAttribute(FilterEffect*, const QualifiedName&);

protected:
    SVGFilterPrimitiveStandardAttributes(const QualifiedName&, Document&);

    bool isSupportedAttribute(const QualifiedName&);
    virtual void parseAttribute(const QualifiedName&, const AtomicString&) OVERRIDE;
    virtual void svgAttributeChanged(const QualifiedName&);
    virtual void childrenChanged(const ChildChange&) OVERRIDE;

    inline void invalidate()
    {
        if (RenderObject* primitiveRenderer = renderer())
            RenderSVGResource::markForLayoutAndParentResourceInvalidation(primitiveRenderer);
    }

    inline void primitiveAttributeChanged(const QualifiedName& attribute)
    {
        if (RenderObject* primitiveRenderer = renderer())
            static_cast<RenderSVGResourceFilterPrimitive*>(primitiveRenderer)->primitiveAttributeChanged(attribute);
    }

private:
    virtual bool isFilterEffect() const { return true; }

    virtual RenderElement* createRenderer(RenderArena&, RenderStyle&) OVERRIDE;
    virtual bool rendererIsNeeded(const RenderStyle&) OVERRIDE;
    virtual bool childShouldCreateRenderer(const Node*) const OVERRIDE { return false; }

    BEGIN_DECLARE_ANIMATED_PROPERTIES(SVGFilterPrimitiveStandardAttributes)
        DECLARE_ANIMATED_LENGTH(X, x)
        DECLARE_ANIMATED_LENGTH(Y, y)
        DECLARE_ANIMATED_LENGTH(Width, width)
        DECLARE_ANIMATED_LENGTH(Height, height)
        DECLARE_ANIMATED_STRING(Result, result)
    END_DECLARE_ANIMATED_PROPERTIES
};

void invalidateFilterPrimitiveParent(SVGElement*);

inline bool isSVGFilterPrimitiveStandardAttributes(const Node* node)
{
    return node->isSVGElement() && toSVGElement(node)->isFilterEffect();
}

template <> inline bool isElementOfType<SVGFilterPrimitiveStandardAttributes>(const Element* element) { return isSVGFilterPrimitiveStandardAttributes(element); }


} // namespace WebCore

#endif // ENABLE(SVG)
#endif
