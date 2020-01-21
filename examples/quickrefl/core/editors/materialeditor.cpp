// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditor.h"
#include "materialeditortoolbar.h"
#include "materialeditoractions.h"
#include <QToolBar>
#include <QTableView>
#include <QVBoxLayout>


MaterialEditor::MaterialEditor(QWidget* parent)
    : QWidget(parent), actions(new MaterialEditorActions(this)), toolbar(new MaterialEditorToolBar(actions))
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;

    auto table = new QTableView;

    layout->addWidget(table);
    layout->addWidget(toolbar);

    setLayout(layout);
}

MaterialEditor::~MaterialEditor() = default;
