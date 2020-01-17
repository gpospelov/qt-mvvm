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

class QTabWidget;

//! Main reflectometry window with all components for quick sample editing and simulations.

class ReflDockWindow : public QMainWindow
{
    Q_OBJECT
public:
    ReflDockWindow(QWidget* parent = nullptr);
};

#endif //  REFLDOCKWINDOW_H
