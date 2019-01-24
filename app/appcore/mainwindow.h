// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include <QMainWindow>

class QTreeView;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    QTreeView* m_treeView;
    QStandardItemModel* m_model;
};

#endif //  MAINWINDOW_H
