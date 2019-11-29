// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
#define MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H

/*!
@file childrenstrategies.h
@brief Collection of strategies to find children, actual of fictional, of given SessionItem.

Used for ViewModel generation when underlying SessionModel changes its layout.
*/

#include <mvvm/viewmodel/childrenstrategyinterface.h>

namespace ModelView
{

class SessionItem;

/*!
@class AllChildrenStrategy
@brief Strategy to find children of given item: gives all actual children back.
*/

class CORE_EXPORT AllChildrenStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

/*!
@class TopItemsStrategy
@brief Strategy to find children of given item: only top level items will be given, all
property items will be filtered out.
*/

class CORE_EXPORT TopItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

/*!
@class PropertyItemsStrategy
@brief Strategy to find children of given item: only property item will be given,
all top level items will be filtered out, all inactive children of GroupItem will
be filtered out.

For example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
        Height
        Radius
*/

class CORE_EXPORT PropertyItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

/*!
@class PropertyItemsFlatStrategy
@brief Strategy to find children of given item.

Acts as PropertyItemStrategy, with the difference that active subproperties of
GroupItem are moved to the same parent, as GroupItem itself.

For example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
    Height
    Radius
*/

class CORE_EXPORT PropertyItemsFlatStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
