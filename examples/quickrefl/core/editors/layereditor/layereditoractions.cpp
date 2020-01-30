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
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <QDebug>
#include <mvvm/model/modelutils.h>

struct LayerEditorActions::LayerEditorActionsImpl {
    SampleModel* model{nullptr};
    LayerSelectionModel* selection_model{nullptr};
    LayerEditorActionsImpl(SampleModel* model) : model(model) {}

    ModelView::SessionItem* insertSampleElement(const std::string& model_type)
    {
        auto items = selection_model->selectedItems();
        auto selected_item = items.empty() ? nullptr : items.back();
        auto parent = selected_item ? selected_item->parent() : root_item();
        auto tagrow = selected_item ? parent->tagRowOfItem(selected_item) : ModelView::TagRow{};
        return model->insertNewItem(model_type, parent, {tagrow.tag, tagrow.row + 1});
    }

    ModelView::SessionItem* root_item() {
        auto model = dynamic_cast<ModelView::AbstractViewModel *>(selection_model->model());
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
    auto new_item = p_impl->insertSampleElement(::Constants::LayerItemType);
    p_impl->selection_model->selectItem(new_item);
}

void LayerEditorActions::onClone()
{
    qDebug() << "LayerEditorActions::onClone()";
}

void LayerEditorActions::onRemove()
{
    qDebug() << "LayerEditorActions::onRemove()";
}

void LayerEditorActions::onMoveUp()
{
    qDebug() << "LayerEditorActions::onMoveUp()";
}

void LayerEditorActions::onMoveDown()
{
    qDebug() << "LayerEditorActions::onMoveDown()";
}

void LayerEditorActions::setSelectionModel(LayerSelectionModel* selection_model)
{
    p_impl->selection_model = selection_model;
}

LayerEditorActions::~LayerEditorActions() = default;
