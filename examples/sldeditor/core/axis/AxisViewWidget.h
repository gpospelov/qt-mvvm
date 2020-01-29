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

#include "AxisItem.h"
#include "AxisObject.h"

#include <QGraphicsView>

/*!
@class Axis
@brief This instance will manage all the axis
*/

class AxisViewWidget : public QGraphicsView
{
    Q_OBJECT
public:
    //! The constructor
    AxisViewWidget();
    //! Resize widget and redraw items
    void resize(const QSize size);
    //! Get the axis object
    AxisObject* getAxisObject() const;

private:
    AxisObject* _axis_object;

};

#endif // AXISVIEWWIDGET_H
