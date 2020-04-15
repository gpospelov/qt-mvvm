// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldeditor.h"

#include "sldviewwidget.h"
#include "sldeditortoolbar.h"
#include "sldeditoractions.h"
#include "applicationmodels.h"

#include "styleutils.h"
#include <QVBoxLayout>

//! The constructor
SLDEditor::SLDEditor(ApplicationModels* apps_models, QWidget* parent) 
    : QWidget(parent), p_view_widget(new SLDViewWidget(apps_models,this)),
    p_editor_actions(new SLDEditorActions(apps_models->sldViewModel(),this)),p_editor_tollbar(new SLDEditorToolBar(p_editor_actions))
{
    setWindowTitle("SLD editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(p_editor_tollbar);
    layout->addWidget(p_view_widget);
    setLayout(layout);
}

//! The destructor
SLDEditor::~SLDEditor() = default;

QSize SLDEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

