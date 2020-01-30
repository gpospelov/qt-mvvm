// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditortoolbar.h"
#include "layereditoractions.h"
#include "styleutils.h"
#include "resources.h"
#include <QToolButton>
#include <QAction>


LayerEditorToolBar::LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent)
    : QToolBar(parent)
{
    InitIconResources();

    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    auto action = new QAction("Add");
    action->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    action->setToolTip("Adds a new layer after selected one.");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onAddLayer);
    addAction(action);

    action = new QAction("Clone");
    action->setIcon(QIcon(":/icons/plus-circle-multiple-outline.svg"));
    action->setToolTip("Clones selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onClone);
    addAction(action);

    action = new QAction("Remove");
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Removes selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onRemove);
    addAction(action);

    addSeparator();

    action = new QAction("Up");
    action->setIcon(QIcon(":/icons/arrow-up-circle-outline.svg"));
    action->setToolTip("Moves selected layer up");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveUp);
    addAction(action);

    action = new QAction("Down");
    action->setIcon(QIcon(":/icons/arrow-down-circle-outline.svg"));
    action->setToolTip("Moves selected layer down");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveDown);
    addAction(action);
}
