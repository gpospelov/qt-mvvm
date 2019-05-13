// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "CustomCellDecoration.h"
#include <QModelIndex>

bool CustomCellDecoration::hasCustomDecoration(const QModelIndex& index) const
{
    if (index.column() == 1) {
        return true;
    } else {
        return DefaultCellDecoration::hasCustomDecoration(index);
    }
}

std::string CustomCellDecoration::cellText(const QModelIndex& index) const
{
    if (index.column() == 1) {
        return "";
    } else {
        return DefaultCellDecoration::cellText(index);
    }
}
