// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "grapheditortoolbar.h"
#include "styleutils.h"

GraphEditorToolBar::GraphEditorToolBar(QWidget* parent) : QToolBar(parent)
{
    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonIconOnly);
}
