// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditortoolbar.h"
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

    auto action = new QAction;
    action->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    action->setText("Add material");
    action->setToolTip("Adds new material at the bottom of the list");
    addAction(action);

    action = new QAction;
    action->setIcon(QIcon(":/icons/plus-circle-multiple-outline.svg"));
    action->setText("Clone");
    action->setToolTip("Clones selected material");
    addAction(action);

    action = new QAction;
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setText("Remove");
    action->setToolTip("Removes selected material");
    addAction(action);

    addSeparator();

    action = new QAction;
    action->setIcon(QIcon(":/icons/arrow-up-circle-outline.svg"));
    action->setText("Up");
    action->setToolTip("Move selected material up");
    addAction(action);

    action = new QAction;
    action->setIcon(QIcon(":/icons/arrow-down-circle-outline.svg"));
    action->setText("Down");
    action->setToolTip("Move selected material down");
    addAction(action);

    addSeparator();

    action = new QAction;
    action->setIcon(QIcon(":/icons/import.svg"));
    action->setText("Import");
    action->setToolTip("Imports materials from file");
    addAction(action);

    action = new QAction;
    action->setIcon(QIcon(":/icons/export.svg"));
    action->setText("Export");
    action->setToolTip("Exports materials to file");
    addAction(action);

}
