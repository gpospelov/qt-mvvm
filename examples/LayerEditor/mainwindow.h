// ************************************************************************** //
//
//  Prototype of the layer editor for the BornAgain project
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include <QMainWindow>

class QTabWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    void init_application();
    void write_settings();

    QTabWidget* m_tabWidget;
};

#endif //  MAINWINDOW_H
