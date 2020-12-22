// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H
#define MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H

#include "mvvm/interfaces/celldecoratorinterface.h"
#include <optional>

namespace ModelView {

//! Generates default cell decorations for Qt trees and tables.

class MVVM_VIEWMODEL_EXPORT DefaultCellDecorator : public CellDecoratorInterface {
public:
    bool hasCustomDecoration(const QModelIndex& index) const override;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) override;

protected:
    virtual std::optional<std::string> cellText(const QModelIndex& index) const;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H
