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

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setIconSize(StyleUtils::ToolBarIconSize());

    auto t0 = new QToolButton;
    t0->setIcon(QIcon(":/icons/toolbar16dark_newitem.svg"));
    t0->setText("Add material");
    addWidget(t0);

    auto t1 = new QToolButton;
    t1->setIcon(QIcon(":/icons/toolbar16dark_newitem.svg"));
    t1->setText("Add material");
    addWidget(t1);

    auto t2 = new QToolButton;
    t2->setIcon(QIcon(":/icons/toolbar16dark_newitem.svg"));
    t2->setText("Add material");
    addWidget(t2);

    auto t3 = new QAction;
    t3->setIcon(QIcon(":/icons/toolbar16dark_newitem.svg"));
    t3->setText("Add material");
    addAction(t3);

}
