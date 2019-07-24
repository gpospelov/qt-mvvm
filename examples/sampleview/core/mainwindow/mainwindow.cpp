// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include "ApplicationModels.h"
#include "DesignerView.h"
#include "LayerTableWidget.h"
#include "MaterialTableWidget.h"
#include <QAction>
#include <QCoreApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QGraphicsView>
#include <QMenuBar>
#include <QSettings>
#include <QTreeView>

namespace {
    const QString main_window_group = "MainWindow";
    const QString size_key = "size";
    const QString pos_key = "pos";
}

MainWindow::MainWindow()
    : m_models(std::make_unique<ApplicationModels>())
    , m_scene_controller(m_models.get())
    , m_material_editor(new QDockWidget(this))
    , m_sample_editor(new QDockWidget(this))
{
    setCentralWidget(m_scene_controller.createDesignerView());
    init_material_editor();
    init_sample_editor();
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
    QCoreApplication::setApplicationName("Layer editor prototype");
    QCoreApplication::setApplicationVersion("0.0");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::init_material_editor()
{
    m_material_editor->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea
                                       | Qt::RightDockWidgetArea);
    m_material_editor->setWindowTitle(tr("Material editor"));
    auto material_view = new MaterialTableWidget(m_models->materialModel(), m_material_editor);
    m_material_editor->setWidget(material_view);
    addDockWidget(Qt::RightDockWidgetArea, m_material_editor);
}

void MainWindow::init_sample_editor()
{
    m_sample_editor->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea
                                     | Qt::RightDockWidgetArea);
    m_sample_editor->setWindowTitle(tr("Layer editor"));
    auto layer_editor = new LayerTableWidget(m_models.get(), m_sample_editor);
    m_sample_editor->setWidget(layer_editor);
    addDockWidget(Qt::RightDockWidgetArea, m_sample_editor);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
