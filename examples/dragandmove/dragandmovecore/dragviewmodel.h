// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGVIEWMODEL_H
#define DRAGVIEWMODEL_H

#include <mvvm/viewmodel/propertytableviewmodel.h>

namespace ModelView
{
class SessionModel;
}

namespace DragAndView
{

//! View model with drag-and-drop support. Relies on PropertyTableViewModel to show
//! properties of DemoItem in table-like views.

class DragViewModel : public ModelView::PropertyTableViewModel
{
    Q_OBJECT

public:
    DragViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QMimeData* mimeData(const QModelIndexList& index_list) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                         const QModelIndex&) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) override;
};

} // namespace DragAndView

#endif // DRAGVIEWMODEL_H
