// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef AXISVIEWWIDGET_H
#define AXISVIEWWIDGET_H

#include <QGraphicsView>

class AxisItem;
class AxisObject;

/*!
@class Axis
@brief This instance will manage all the axis
*/
class AxisViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    AxisViewWidget();
    void resize(const QSize size);
    AxisObject* getAxisObject() const;

private:
    AxisObject* _axis_object;

};

#endif // AXISVIEWWIDGET_H
