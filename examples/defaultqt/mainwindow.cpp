// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "centralwidget.h"

MainWindow::MainWindow()
{
    setCentralWidget(new CentralWidget);
    resize(1000, 600);
}
