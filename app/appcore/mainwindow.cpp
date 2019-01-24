// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include "testwidget1.h"
#include <QTabWidget>

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget)
{    
    m_tabWidget->addTab(new TestWidget1, "Model basics");

    setCentralWidget(m_tabWidget);
    resize(800, 600);
}
