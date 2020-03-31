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
#include <QToolButton>
#include <QLayout>

GraphEditorToolBar::GraphEditorToolBar(QWidget* parent) : QToolBar(parent)
{
    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setOrientation(Qt::Vertical);
    setStyleSheet("QToolBar{spacing:0px;}");

    auto reset_view = new QToolButton;
    reset_view->setToolTip("Set axes to default range.");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    addWidget(reset_view);
    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}
