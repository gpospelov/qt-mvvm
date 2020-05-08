// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "welcomeview.h"
#include "projectmanagerinterface.h"
#include "recentprojectwidget.h"
#include "openprojectwidget.h"
#include <QHBoxLayout>


WelcomeView::WelcomeView(QWidget* parent) : QWidget(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QHBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(new RecentProjectWidget);
    layout->addWidget(new OpenProjectWidget);
    layout->addSpacing(50);
}

WelcomeView::~WelcomeView() = default;
