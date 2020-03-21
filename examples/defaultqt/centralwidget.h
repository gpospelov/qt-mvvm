// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QStandardItemModel;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget* parent = nullptr);

private:
    void init_model();
    void init_factory();
    QStandardItemModel* model{nullptr};
};

#endif // CENTRALWIDGET_H
