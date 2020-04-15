// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldeditortoolbar.h"
#include "sldeditoractions.h"
#include "resources.h"
#include "styleutils.h"

#include <QAction>
#include <QToolButton>

SLDEditorToolBar::SLDEditorToolBar(SLDEditorActions* actions, QWidget* parent)
    : QToolBar(parent)
{
    InitIconResources();

    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

}
