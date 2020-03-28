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
#include "materialeditorwidget.h"
#include "materialmodel.h"
#include "styleutils.h"
#include <QVBoxLayout>

MaterialEditor::MaterialEditor(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      actions(new MaterialEditorActions(material_model, this)),
      toolbar(new MaterialEditorToolBar(actions)),
      editor_widget(new MaterialEditorWidget(material_model))
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(editor_widget);
    setLayout(layout);

    actions->setMaterialSelectionModel(editor_widget->selectionModel());
}

QSize MaterialEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize MaterialEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

MaterialEditor::~MaterialEditor() = default;
