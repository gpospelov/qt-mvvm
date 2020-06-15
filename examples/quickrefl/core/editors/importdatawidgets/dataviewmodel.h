// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATAVIEWMODEL_H
#define DATAVIEWMODEL_H

#include <mvvm/viewmodel/topitemsviewmodel.h>

namespace ModelView
{
class SessionModel;
}

class RealDataModel;

//! This is the implementation of drag and drop support for the data editor

class DataViewModel : public ModelView::TopItemsViewModel
{
public:
    DataViewModel(RealDataModel* model, QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QMimeData* mimeData(const QModelIndexList& index_list) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                         const QModelIndex& parent) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) override;
};

#endif // DATAVIEWMODEL_H
