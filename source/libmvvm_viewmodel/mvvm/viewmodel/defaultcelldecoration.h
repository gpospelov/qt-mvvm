// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTCELLDECORATION_H
#define MVVM_DEFAULTCELLDECORATION_H

#include <mvvm/viewmodel/celldecorationinterface.h>

class QModelIndex;

namespace ModelView
{

//! Generates default cell decorations for Qt trees and tables.

class CORE_EXPORT DefaultCellDecoration : public CellDecorationInterface
{
public:
    bool hasCustomDecoration(const QModelIndex& index) const;
    std::string cellText(const QModelIndex& index) const;
};

} // namespace ModelView

#endif // MVVM_DEFAULTCELLDECORATION_H
