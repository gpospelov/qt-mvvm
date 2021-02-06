// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
#define MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H

#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show content of SessionModel in Qt widgets: all item properties as a table row.
//! Intended to show registered properties of items in table-like view.
//! Registered properties will form columns of the table, top level items will form table rows.

class MVVM_VIEWMODEL_EXPORT PropertyTableViewModel : public ViewModel {
    Q_OBJECT

public:
    PropertyTableViewModel(SessionModel* model, QObject* parent = nullptr);

    void insertRow(ViewItem* parent, int row, std::vector<std::unique_ptr<ViewItem>> items) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
