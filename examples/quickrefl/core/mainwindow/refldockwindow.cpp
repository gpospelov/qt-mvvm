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
#include <QLabel>

ReflDockWindow::ReflDockWindow(QWidget* parent)
    : QMainWindow(parent), docks_controller(new DocksController(this)),
      models(std::make_unique<ApplicationModels>())
{
    setCentralWidget(new QLabel("Reflectometry docks"));

    docks_controller->addWidget(0, new MaterialEditor(models->materialModel()),
                                Qt::TopDockWidgetArea);
    docks_controller->addWidget(1, new LayerEditor(models.get()), Qt::TopDockWidgetArea);
    docks_controller->addWidget(2, new LayerCanvas, Qt::LeftDockWidgetArea);
    docks_controller->addWidget(3, new SLDViewWidget(models->sldController(), parent),
                                Qt::RightDockWidgetArea);
    docks_controller->addWidget(4, new ReflPlotWidget, Qt::BottomDockWidgetArea);
    docks_controller->addWidget(5, new InstrumentEditor, Qt::BottomDockWidgetArea);
}

ReflDockWindow::~ReflDockWindow() = default;
