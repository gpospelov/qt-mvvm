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
#include "styleutils.h"
#include <QVBoxLayout>

//! The constructor
SLDEditor::SLDEditor(ApplicationModels* apps_models, QWidget* parent) 
    : QWidget(parent), p_view_widget(new SLDViewWidget(apps_models,this))
{
    setWindowTitle("SLD editor");

    auto layout = new QVBoxLayout;
    // layout->addWidget(toolbar);
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

