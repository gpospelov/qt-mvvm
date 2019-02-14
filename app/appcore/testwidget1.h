// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TESTWIDGET1_H
#define TESTWIDGET1_H

#include <QWidget>

class QTreeView;
class QStandardItemModel;

//! Playground to test basics of QStandardItemModel.

class TestWidget1 : public QWidget
{
    Q_OBJECT
public:
    TestWidget1(QWidget* parent = nullptr);

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    QTreeView* m_treeView;
    QStandardItemModel* m_model;
};

#endif // TESTWIDGET1_H
