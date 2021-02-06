// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/propertytableviewmodel.h"
#include "mvvm/viewmodel/standardviewmodelcontrollers.h"
#include "mvvm/viewmodel/viewitem.h"

using namespace ModelView;

PropertyTableViewModel::PropertyTableViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyTableViewModelController>(model, this), parent)
{
}

void PropertyTableViewModel::insertRow(ViewItem* parent, int row,
                                       std::vector<std::unique_ptr<ViewItem>> items)
{
    // The code below is used to inform QTableView about layout change if the number
    // of columns before the insertion doesn't coincide with the length of `items` vector to insert.
    // This happens when PropertyTableViewModel is looking on empty SessionModel.
    int prevColumnCount = parent->columnCount();
    ViewModel::insertRow(parent, row, std::move(items));
    if (parent->columnCount() != prevColumnCount)
        emit layoutChanged();
}
