// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditortoolbar.h"
#include "materialeditoractions.h"
#include "styleutils.h"
#include "resources.h"
#include <QToolButton>
#include <QAction>


MaterialEditorToolBar::MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent)
    : QToolBar(parent)
{
    InitIconResources();

    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    auto action = new QAction("Add material");
    action->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    action->setToolTip("Adds new material at the bottom of the list");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onAddMaterial);
    addAction(action);

    action = new QAction("Clone");
    action->setIcon(QIcon(":/icons/plus-circle-multiple-outline.svg"));
    action->setToolTip("Clones selected material");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onCloneMaterial);
    addAction(action);

    action = new QAction("Remove");
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Removes selected material");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onRemoveMaterial);
    addAction(action);

    addSeparator();

    action = new QAction("Up");
    action->setIcon(QIcon(":/icons/arrow-up-circle-outline.svg"));
    action->setToolTip("Move selected material up");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onMoveUp);
    addAction(action);

    action = new QAction("Down");
    action->setIcon(QIcon(":/icons/arrow-down-circle-outline.svg"));
    action->setToolTip("Move selected material down");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onMoveDown);
    addAction(action);

    addSeparator();

    action = new QAction("Import");
    action->setIcon(QIcon(":/icons/import.svg"));
    action->setToolTip("Imports materials from file");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onImport);
    addAction(action);

    action = new QAction("Export");
    action->setIcon(QIcon(":/icons/export.svg"));
    action->setToolTip("Exports materials to file");
    connect(action, &QAction::triggered, actions, &MaterialEditorActions::onExport);
    addAction(action);
}
