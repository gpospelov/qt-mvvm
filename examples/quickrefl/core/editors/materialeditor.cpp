// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditor.h"
#include "materialeditoractions.h"
#include "materialeditortoolbar.h"
#include "materialmodel.h"
#include "materialtablewidget.h"
#include <QVBoxLayout>

MaterialEditor::MaterialEditor(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      actions(new MaterialEditorActions(material_model, this)),
      toolbar(new MaterialEditorToolBar(actions)),
      table_widget(new MaterialTableWidget(material_model))
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(table_widget);
    setLayout(layout);
}

MaterialEditor::~MaterialEditor() = default;
