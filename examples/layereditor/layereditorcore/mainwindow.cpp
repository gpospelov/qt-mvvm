// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <layereditorcore/applicationmodels.h>
#include <layereditorcore/mainwindow.h>
#include <layereditorcore/samplewidget.h>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : m_tabWidget(new QTabWidget), m_models(std::make_unique<ApplicationModels>())
{
    m_tabWidget->addTab(new SampleWidget(m_models.get()), "Materials and Layers");

    setCentralWidget(m_tabWidget);

    create_menus();
    init_application();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    write_settings();
    QMainWindow::closeEvent(event);
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("layereditor");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}

//! Creates application file menu.

void MainWindow::create_menus()
{
    auto fileMenu = menuBar()->addMenu("&File");

    // open file
    auto openAction = new QAction("&Open...", this);
    fileMenu->addAction(openAction);
    auto onOpenAction = [&]() {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            m_models->readFromFile(fileName);
    };
    connect(openAction, &QAction::triggered, onOpenAction);

    // save file
    auto saveAction = new QAction("&Save As...", this);
    fileMenu->addAction(saveAction);

    auto onSaveAction = [&]() {
        QString fileName = QFileDialog::getSaveFileName(this);
        if (!fileName.isEmpty())
            m_models->writeToFile(fileName);
    };
    connect(saveAction, &QAction::triggered, onSaveAction);
}
