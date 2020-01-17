// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "refldockwindow.h"
#include <QLabel>

ReflDockWindow::ReflDockWindow(QWidget* parent) : QMainWindow(parent)
{
    setCentralWidget(new QLabel("Reflectometry docks"));
}
