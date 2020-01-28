// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditor.h"
#include "layereditoractions.h"
#include "layereditortoolbar.h"
#include "samplemodel.h"
#include "layereditorwidget.h"
#include <QVBoxLayout>

LayerEditor::LayerEditor(SampleModel* model, QWidget* parent)
    : QWidget(parent), sample_model(model),
      actions(new LayerEditorActions(model, this)),
      toolbar(new LayerEditorToolBar(actions)),
      editor_widget(new LayerEditorWidget(model))
{
    setWindowTitle("Layer editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(editor_widget);
    setLayout(layout);

    actions->setSelectionModel(editor_widget->selectionModel());
}

LayerEditor::~LayerEditor() = default;
