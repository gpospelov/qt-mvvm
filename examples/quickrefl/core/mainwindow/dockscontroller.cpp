// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dockscontroller.h"
#include <QDockWidget>
#include <QMainWindow>
#include <map>

//! Keeps together info about the dock, the area it occupies and widget it holds.

struct DockWidgetInfo {
    QDockWidget* dock{nullptr};
    Qt::DockWidgetArea area{Qt::NoDockWidgetArea};
    QWidget* widget{nullptr};

    DockWidgetInfo() {}
    DockWidgetInfo(QDockWidget* dock, QWidget* widget, Qt::DockWidgetArea area)
        : dock(dock), area(area), widget(widget)
    {
    }
};

//! Implementation of DocksController.

struct DocksController::DocksControllerImpl {
    QMainWindow* main_window{nullptr};
    std::map<int, DockWidgetInfo> docks;

    DocksControllerImpl(QMainWindow* main_window) : main_window(main_window) {}

    void addWidget(int index, QWidget* widget, Qt::DockWidgetArea area)
    {
        if (docks.find(index) != docks.end())
            throw std::runtime_error("Error in DocksController: attempt to add widget id twice");

        auto dock = new QDockWidget;
        dock->setWidget(widget);
        dock->setWindowTitle(widget->windowTitle());

        main_window->addDockWidget(area, dock);
        docks[index] = DockWidgetInfo(dock, widget, area);
    }
};

//! DocksController c-tor.

DocksController::DocksController(QMainWindow* main_window)
    : QObject(main_window), p_impl(std::make_unique<DocksControllerImpl>(main_window))
{
}

void DocksController::addWidget(int index, QWidget* widget, Qt::DockWidgetArea area)
{
    p_impl->addWidget(index, widget, area);
}

DocksController::~DocksController() = default;
