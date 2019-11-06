// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTABLEVIEWMODEL_H
#define LAYERTABLEVIEWMODEL_H

#include <mvvm/viewmodel/abstractviewmodel.h>

namespace ModelView
{
class SessionModel;
} // namespace ModelView

/*!
@class LayerTableViewModel
@brief View model to display content of MultiLayerItem in table like views.
*/

class LayerTableViewModel : public ModelView::AbstractViewModel
{
public:
    LayerTableViewModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
    ~LayerTableViewModel() override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QMimeData* mimeData(const QModelIndexList& index_list) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                         const QModelIndex& parent) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) override;

private:
    //! Determines if item is dropped directly on parent and handles this case.
    //! Returns false otherwise.
    bool processDirectDrop(ModelView::SessionItem* to_drop, int row, int column,
                           const QModelIndex& parent);

    int findInsertionRow(ModelView::SessionItem* to_drop, ModelView::SessionItem* new_parent,
                         int row_candidate);
};

#endif //  LAYERTABLEVIEWMODEL_H
