// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "refldockwindow.h"
#include "SLDViewWidget.h"
#include "applicationmodels.h"
#include "dockscontroller.h"
#include "layereditor.h"
#include "reflwidgets.h"
#include <QToolBar>
#include <QLabel>

ReflDockWindow::ReflDockWindow(QWidget* parent)
    : QMainWindow(parent), toolbar(new QToolBar), docks_controller(new DocksController(this)),
      models(std::make_unique<ApplicationModels>())
{
    setup_toolbar();
    setup_centralwidget();

    docks_controller->addWidget(0, new MaterialEditor(models->materialModel()),
                                Qt::TopDockWidgetArea);
    docks_controller->addWidget(1, new LayerEditor(models.get()), Qt::TopDockWidgetArea);
    docks_controller->addWidget(3, new ReflPlotWidget, Qt::BottomDockWidgetArea);
    docks_controller->addWidget(4, new SLDViewWidget(models->sldController(), parent),
                                Qt::BottomDockWidgetArea);
}

ReflDockWindow::~ReflDockWindow() = default;

void ReflDockWindow::setup_toolbar()
{
    const int toolbar_icon_size = 24;
    toolbar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    addToolBar(toolbar);
    //    setCentralWidget(toolbar);
}

//! Central widget as horizontal thin line.

void ReflDockWindow::setup_centralwidget()
{
    auto central_widget = new QWidget;
    central_widget->setStyleSheet("background-color:red;");
    central_widget->setMinimumHeight(2);
    central_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCentralWidget(central_widget);
}
