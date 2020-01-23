// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditoractions.h"
#include "materialmodel.h"
#include "materialitems.h"
#include "materialselectionmodel.h"
#include <mvvm/model/modelutils.h>
#include <QDebug>

struct MaterialEditorActions::MaterialEditorActionsImpl {
    MaterialModel* material_model{nullptr};
    MaterialSelectionModel* selection_model{nullptr};
    MaterialEditorActionsImpl(MaterialModel* material_model) : material_model(material_model) {}    
};

MaterialEditorActions::MaterialEditorActions(MaterialModel* material_model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<MaterialEditorActionsImpl>(material_model))
{
}

void MaterialEditorActions::onAddMaterial()
{
    p_impl->material_model->addDefaultMaterial();
}

//! Processes request to clone selected materials.

void MaterialEditorActions::onCloneMaterial()
{
    for (const auto item : p_impl->selection_model->selectedMaterials())
        p_impl->material_model->cloneMaterial(item);
}

void MaterialEditorActions::onRemoveMaterial()
{
    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::DeleteItemFromModel(item);
}

void MaterialEditorActions::onMoveUp()
{
    for (auto item : p_impl->selection_model->selectedMaterials()) {
        auto tagrow = item->parent()->tagRowOfItem(item);

        // item already at the top
        if (tagrow.row == 0)
            return;

        p_impl->material_model->moveItem(item, item->parent(), {tagrow.tag, tagrow.row - 1});
    }
}

void MaterialEditorActions::onMoveDown()
{
    auto items = p_impl->selection_model->selectedMaterials();
    std::reverse(items.begin(), items.end()); // to correctly move multiple selections

    for (auto item : items) {
        auto tagrow = item->parent()->tagRowOfItem(item);

        // item already at the buttom
        if (tagrow.row == item->parent()->childrenCount() - 1)
            return;

        p_impl->material_model->moveItem(item, item->parent(), {tagrow.tag, tagrow.row + 1});
    }
}

void MaterialEditorActions::onExport()
{
    qDebug() << "MaterialEditorActions::onExport()";
}

void MaterialEditorActions::onImport()
{
    qDebug() << "MaterialEditorActions::onImport()";
}

void MaterialEditorActions::setMaterialSelectionModel(MaterialSelectionModel* selection_model)
{
    p_impl->selection_model = selection_model;
}

MaterialEditorActions::~MaterialEditorActions() = default;
