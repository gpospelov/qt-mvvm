// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CHILDRENSTRATEGIES_H
#define MVVM_CHILDRENSTRATEGIES_H

#include "childrenstrategyinterface.h"

/*!
@file childrenstrategies.h
Collection of strategies to find children, actual of fictional, of given SessionItem.
Used for ViewModel generation when underlying SessionModel changes its layout.
*/

namespace ModelView {

class SessionItem;

//! Strategy to find children of given item: gives all actual children back.

class CORE_EXPORT AllChildrenStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class CORE_EXPORT TopItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

//! Strategy to find children of given item: only property item will be given,
//! all top level items will be filtered out.

class CORE_EXPORT PropertyItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<SessionItem*> children(const SessionItem* item) const override;
};

}  // namespace ModelView

#endif // MVVM_CHILDRENSTRATEGIES_H
