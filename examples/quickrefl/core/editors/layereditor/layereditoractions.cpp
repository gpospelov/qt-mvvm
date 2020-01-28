// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditoractions.h"
#include "samplemodel.h"
#include "layerselectionmodel.h"
#include <mvvm/model/modelutils.h>
#include <QDebug>

struct LayerEditorActions::LayerEditorActionsImpl {
    SampleModel* model{nullptr};
    LayerSelectionModel* selection_model{nullptr};
    LayerEditorActionsImpl(SampleModel* model) : model(model) {}
};

LayerEditorActions::LayerEditorActions(SampleModel* model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<LayerEditorActionsImpl>(model))
{
}

void LayerEditorActions::onAdd()
{
    qDebug() << "LayerEditorActions::onAdd()";
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

void LayerEditorActions::onExport()
{
    qDebug() << "LayerEditorActions::onExport()";
}

void LayerEditorActions::onImport()
{
    qDebug() << "LayerEditorActions::onImport()";
}

void LayerEditorActions::setSelectionModel(LayerSelectionModel* selection_model)
{
    p_impl->selection_model = selection_model;
}

LayerEditorActions::~LayerEditorActions() = default;
