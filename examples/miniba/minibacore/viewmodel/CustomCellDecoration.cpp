// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "CustomCellDecoration.h"


bool CustomCellDecoration::hasCustomDecoration(const QModelIndex& index) const
{
    return DefaultCellDecoration::hasCustomDecoration(index);
}

std::string CustomCellDecoration::cellText(const QModelIndex& index) const
{
    return DefaultCellDecoration::cellText(index);
}
