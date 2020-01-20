// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "ViewWidget.h"
#include <QGraphicsScene>

ViewWidget::ViewWidget(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(parent = this);
    this->setScene(scene);
}


