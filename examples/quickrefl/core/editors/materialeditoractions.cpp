// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditoractions.h"
#include "materialselectionmodel.h"
#include "materialmodel.h"
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
    qDebug() << "MaterialEditorActions::onAddMaterial()";
}

//! Processes request to clone selected materials.

void MaterialEditorActions::onCloneMaterial()
{
    for (const auto item : p_impl->selection_model->selectedMaterials())
        p_impl->material_model->cloneMaterial(item);
}

void MaterialEditorActions::onRemoveMaterial()
{
    qDebug() << "MaterialEditorActions::onRemoveMaterial()";
}

void MaterialEditorActions::onMoveUp()
{
    qDebug() << "MaterialEditorActions::onMoveUp()";
}

void MaterialEditorActions::onMoveDown()
{
    qDebug() << "MaterialEditorActions::onMoveDown()";
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
