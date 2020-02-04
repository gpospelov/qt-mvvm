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
#include <mvvm/viewmodel/abstractviewmodel.h>

struct LayerEditorActions::LayerEditorActionsImpl {
    SampleModel* model{nullptr};
    LayerSelectionModel* selection_model{nullptr};
    LayerEditorActionsImpl(SampleModel* model) : model(model) {}

    ModelView::SessionItem* insertSampleElement(const std::string& model_type)
    {
        auto items = selection_model->selectedItems();
        if (items.empty()) {
            auto parent = root_item();
            return model->insertNewItem(model_type, parent);
        } else {
            auto selected_item = items.back();
            auto parent = selected_item->parent();
            auto tagrow = parent->tagRowOfItem(selected_item);
            return model->insertNewItem(model_type, parent, {tagrow.tag, tagrow.row + 1});
        }
    }

    ModelView::SessionItem* root_item()
    {
        auto model = dynamic_cast<ModelView::AbstractViewModel*>(selection_model->model());
        return model->sessionItemFromIndex(QModelIndex());
    }
};

LayerEditorActions::LayerEditorActions(SampleModel* model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<LayerEditorActionsImpl>(model))
{
}

//! Adds layer after selected item. If more than one item is selected, adds after the last one.

void LayerEditorActions::onAddLayer()
{
    auto layer_type = Constants::LayerItemType;

    if (auto action = qobject_cast<QAction*>(sender()); action)
        if (action->data().canConvert(QVariant::String))
            layer_type = action->data().toString().toStdString();

    auto new_item = p_impl->insertSampleElement(layer_type);
    p_impl->selection_model->selectItem(new_item);
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
            p_impl->model->copyItem(to_clone, parent, {tagrow.tag, tagrow.row + 1}));
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
