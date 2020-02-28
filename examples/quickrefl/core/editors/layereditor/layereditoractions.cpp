// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditoractions.h"
#include "item_constants.h"
#include "layeritems.h"
#include "layerselectionmodel.h"
#include "samplemodel.h"
#include <QAction>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

struct LayerEditorActions::LayerEditorActionsImpl {
    SampleModel* model{nullptr};
    LayerSelectionModel* selection_model{nullptr};
    LayerEditorActionsImpl(SampleModel* model) : model(model) {}

    //! Finds parent and tagrow to insert new item

    std::pair<SessionItem*, TagRow> locateInsertPlace()
    {
        auto all_selected = selection_model->selectedItems();
        auto selected = all_selected.empty() ? nullptr : all_selected.back();
        if (selected)
            return {selected->parent(), selected->parent()->tagRowOfItem(selected).next()};
        return {root_item(), TagRow{}};
    }

    //! Returns a multi layer playing the role of invisible root item.

    ModelView::SessionItem* root_item()
    {
        return selection_model->viewModel()->sessionItemFromIndex(QModelIndex());
    }
};

LayerEditorActions::LayerEditorActions(SampleModel* model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<LayerEditorActionsImpl>(model))
{
}

//! Adds layer after selected item. If more than one item is selected, adds after the last one.

void LayerEditorActions::onAddLayer()
{
    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto new_item = p_impl->model->insertItem<LayerItem>(parent, tagrow);
    p_impl->selection_model->selectItem(new_item);
}

void LayerEditorActions::onAddMultiLayer()
{
    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto multilayer = p_impl->model->insertItem<MultiLayerItem>(parent, tagrow);
    p_impl->model->insertItem<LayerItem>(multilayer);
    p_impl->model->insertItem<LayerItem>(multilayer);
    p_impl->selection_model->selectItem(multilayer);
}

void LayerEditorActions::onClone()
{
    auto items = p_impl->selection_model->selectedItems();
    if (items.empty())
        return;

    std::vector<ModelView::SessionItem*> new_selection;
    for (auto to_clone : items) {
        auto parent = to_clone->parent();
        const auto tagrow = parent->tagRowOfItem(to_clone);
        new_selection.push_back(
            p_impl->model->copyItem(to_clone, parent, tagrow.next()));
    }

    p_impl->selection_model->selectItems(new_selection);
}

void LayerEditorActions::onRemove()
{
    auto items = p_impl->selection_model->selectedItems();
    if (items.empty())
        return;

    auto next_to_select = ModelView::Utils::FindNextItemToSelect(items.back());
    for (auto item : items)
        ModelView::Utils::DeleteItemFromModel(item);

    p_impl->selection_model->selectItem(next_to_select);
}

void LayerEditorActions::onMoveUp()
{
    auto selected = p_impl->selection_model->selectedItems();

    for (auto item : selected)
        ModelView::Utils::MoveUp(item);

    p_impl->selection_model->selectItems(selected);
}

void LayerEditorActions::onMoveDown()
{
    auto selected = p_impl->selection_model->selectedItems();

    for (auto item : selected)
        ModelView::Utils::MoveDown(item);

    p_impl->selection_model->selectItems(selected);
}

void LayerEditorActions::setSelectionModel(LayerSelectionModel* selection_model)
{
    p_impl->selection_model = selection_model;
}

LayerEditorActions::~LayerEditorActions() = default;
