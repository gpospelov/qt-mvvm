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

MainWindow::MainWindow()
    : m_widget1(new TestWidget1)
{    
    setCentralWidget(m_widget1);
    resize(800, 600);
}
