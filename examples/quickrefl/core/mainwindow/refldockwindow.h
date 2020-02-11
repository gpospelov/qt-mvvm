// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef REFLDOCKWINDOW_H
#define REFLDOCKWINDOW_H

#include <QMainWindow>
#include <memory>

class DocksController;
class ApplicationModels;

//! Main reflectometry window with all components for quick sample editing and simulations.

class ReflDockWindow : public QMainWindow
{
    Q_OBJECT
public:
    ReflDockWindow(QWidget* parent = nullptr);
    ~ReflDockWindow();

private:
    DocksController* docks_controller{nullptr};
    std::unique_ptr<ApplicationModels> models;
};

#endif //  REFLDOCKWINDOW_H
