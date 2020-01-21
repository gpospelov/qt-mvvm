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
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>

MaterialEditor::MaterialEditor(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model), actions(new MaterialEditorActions(this)),
      toolbar(new MaterialEditorToolBar(actions))
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;

    auto table = new QTableView;

    layout->addWidget(table);
    layout->addWidget(toolbar);

    setLayout(layout);
}

MaterialEditor::~MaterialEditor() = default;
