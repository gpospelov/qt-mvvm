// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef VIEWOBJECT_H
#define VIEWOBJECT_H

#include "AxisObject.h"

#include <QGraphicsObject>

class ViewObject : public QGraphicsObject
{
    Q_OBJECT
public:
    //! The constructor
    ViewObject();
    //! Get the conversion axes
    AxisObject* getAxes() const;

};

#endif // VIEWOBJECT_H
