// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMUTILS_H
#define ITEMUTILS_H

#include <functional>

class SessionItem;

namespace Utils
{

//! Iterates through item and all its children.
void iterate(const SessionItem* item, const std::function<void(const SessionItem*)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
void iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun);
}

#endif
