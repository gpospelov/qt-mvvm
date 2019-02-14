// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelutils.h"
#include <QStandardItemModel>

void ModelView::iterate_model(const QStandardItemModel* model, const QModelIndex& parent, std::function<void(const QStandardItem*)> fun)
{
    if (!model)
        return;

    for(int row = 0; row<model->rowCount(parent); ++row) {
        for(int col = 0; col<model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            auto item = model->itemFromIndex(index);
            if (item)
                fun(item);
        }
        for(int col = 0; col<model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            ModelView::iterate_model(model, index, fun);
        }

    }


}
