// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_TOPITEMSSTRATEGY_H
#define MVVM_TOPITEMSSTRATEGY_H

#include "childrenstrategyinterface.h"

//! @file childrenstrategies.h
//! Collection of strategies to find children, actual of fictional, of given item.

namespace ModelView {

class SessionItem;

//! Strategy to find children of given item. Gives all actual children back.

class CORE_EXPORT AllChildrenStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item. Only top level items will be given, all
//! property items will be filtered out.

class CORE_EXPORT TopItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item. Only property item will be given,
//! all top level items will be filtered out.

class CORE_EXPORT PropertyItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

}  // namespace ModelView

#endif // MVVM_TOPITEMSSTRATEGY_H
