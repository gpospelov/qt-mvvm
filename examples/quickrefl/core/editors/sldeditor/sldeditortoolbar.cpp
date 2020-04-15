// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldeditortoolbar.h"
#include "resources.h"
#include "sldeditoractions.h"
#include "styleutils.h"

#include <QAction>
#include <QToolButton>

SLDEditorToolBar::SLDEditorToolBar(SLDEditorActions* actions, QWidget* parent) : QToolBar(parent)
{
    InitIconResources();

    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    auto reset_view = new QToolButton;
    reset_view->setToolTip("Set axes to default range.");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    addWidget(reset_view);
    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}
