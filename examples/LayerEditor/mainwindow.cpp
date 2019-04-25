// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include "initiallayereditor.h"
#include "option1.h"
#include "repetitivelayereditor.h"
#include "splitlayereditor.h"
#include "treelayereditor.h"
#include <QTabWidget>
#include <QCoreApplication>
#include <QSettings>

namespace {
    const QString main_window_group = "MainWindow";
    const QString size_key = "size";
    const QString pos_key = "pos";
}

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget)
{
    m_tabWidget->addTab(new InitialLayerEditor, "Initial layer editor");
    m_tabWidget->addTab(new SplitLayerEditor, "Split layer editor");
    m_tabWidget->addTab(new TreeLayerEditor, "Tree layer editor");
    m_tabWidget->addTab(new Option1Widget, "Cascade layer editor");
    m_tabWidget->addTab(new RepetitiveLayerEditor, "Repetitive layer editor");

    m_tabWidget->setCurrentIndex(0);
    setCentralWidget(m_tabWidget);

    init_application();
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("layer-editor");
    QCoreApplication::setApplicationVersion("0.0");
    QCoreApplication::setOrganizationName("qt-mvvm");
    resize(2600, 1600);
}
