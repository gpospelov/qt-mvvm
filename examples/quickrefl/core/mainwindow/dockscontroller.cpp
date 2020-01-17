// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dockscontroller.h"
#include <QMainWindow>

struct DocksController::DocksControllerImpl {
    QMainWindow* main_window{nullptr};

    DocksControllerImpl(QMainWindow* main_window) : main_window(main_window) {}
};

DocksController::DocksController(QMainWindow* main_window)
    : p_impl(std::make_unique<DocksControllerImpl>(main_window))
{
}

DocksController::~DocksController() = default;
