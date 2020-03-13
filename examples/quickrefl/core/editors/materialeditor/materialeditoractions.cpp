// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditoractions.h"
#include "materialitems.h"
#include "materialmodel.h"
#include "materialselectionmodel.h"
#include <QDebug>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

struct MaterialEditorActions::MaterialEditorActionsImpl {
    MaterialModel* material_model{nullptr};
    MaterialSelectionModel* selection_model{nullptr};
    MaterialEditorActionsImpl(MaterialModel* material_model) : material_model(material_model) {}

    //! Finds parent and tagrow to insert new item

    std::pair<SessionItem*, TagRow> locateInsertPlace()
    {
        auto all_selected = selection_model->selectedMaterials();
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

MaterialEditorActions::MaterialEditorActions(MaterialModel* material_model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<MaterialEditorActionsImpl>(material_model))
{
}

void MaterialEditorActions::onAddMaterial()
{
    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto material = p_impl->material_model->addDefaultMaterial(tagrow);
    p_impl->selection_model->selectItem(material);
}

//! Processes request to clone selected materials.

void MaterialEditorActions::onCloneMaterial()
{
    std::vector<ModelView::SessionItem*> new_selection;
    for (const auto item : p_impl->selection_model->selectedMaterials())
        new_selection.push_back(p_impl->material_model->cloneMaterial(item));
    p_impl->selection_model->selectItems(new_selection);
}

void MaterialEditorActions::onRemoveMaterial()
{
    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::DeleteItemFromModel(item);
}

void MaterialEditorActions::onMoveUp()
{
    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::MoveUp(item);
}

void MaterialEditorActions::onMoveDown()
{
    auto items = p_impl->selection_model->selectedMaterials();
    std::reverse(items.begin(), items.end()); // to correctly move multiple selections
    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::MoveDown(item);
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
