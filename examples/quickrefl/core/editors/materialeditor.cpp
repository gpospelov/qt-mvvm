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
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>

MaterialEditor::MaterialEditor(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      view_model(ModelView::Utils::CreatePropertyTableViewModel(material_model)),
      actions(new MaterialEditorActions(this)), toolbar(new MaterialEditorToolBar(actions)),
      table_widget(new MaterialTableWidget)
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;

    auto table = new QTableView;
    table->setModel(view_model.get());

    layout->addWidget(toolbar);
    layout->addWidget(table);
    layout->addWidget(table_widget);

    setLayout(layout);
}

MaterialEditor::~MaterialEditor() = default;
