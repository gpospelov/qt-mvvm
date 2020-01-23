// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditoractions.h"
#include <QDebug>

struct MaterialEditorActions::MaterialEditorActionsImpl {
};

MaterialEditorActions::MaterialEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<MaterialEditorActionsImpl>())
{
}

void MaterialEditorActions::onAddMaterial()
{
    qDebug() << "MaterialEditorActions::onAddMaterial()";
}

void MaterialEditorActions::onCloneMaterial()
{
    qDebug() << "MaterialEditorActions::onCloneMaterial()";
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

MaterialEditorActions::~MaterialEditorActions() = default;
