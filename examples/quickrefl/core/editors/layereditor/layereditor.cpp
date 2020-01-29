// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditor.h"
#include "applicationmodels.h"
#include "layereditoractions.h"
#include "layereditortoolbar.h"
#include "layereditorwidget.h"
#include <QVBoxLayout>

LayerEditor::LayerEditor(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), actions(new LayerEditorActions(models->sampleModel(), this)),
      toolbar(new LayerEditorToolBar(actions)), editor_widget(new LayerEditorWidget(models))
{
    setWindowTitle("Layer editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(editor_widget);
    setLayout(layout);

    actions->setSelectionModel(editor_widget->selectionModel());
}

LayerEditor::~LayerEditor() = default;
