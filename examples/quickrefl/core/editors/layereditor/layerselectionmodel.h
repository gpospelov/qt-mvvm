// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERSELECTIONMODEL_H
#define LAYERSELECTIONMODEL_H

#include <QItemSelectionModel>
#include <vector>

namespace ModelView
{
class ViewModel;
class SessionItem;
} // namespace ModelView

class LayerEditorActions;

//! Custom selection model for layer view model (AbstractViewModel).

class LayerSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    LayerSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~LayerSelectionModel() = default;

    void selectItems(std::vector<ModelView::SessionItem*> items);
    void selectItem(ModelView::SessionItem* item);

    std::vector<ModelView::SessionItem*> selectedItems() const;

    const ModelView::ViewModel* viewModel() const;
};

#endif // LAYERSELECTIONMODEL_H
