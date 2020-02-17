// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ViewObject.h"
#include "ViewWidget.h"

//! The constructor
ViewObject::ViewObject() : QGraphicsObject() {}

//! Get the conversion axes
AxisObject* ViewObject::getAxes() const
{
    ViewWidget* main_view = dynamic_cast<ViewWidget*>(scene()->views().last());
    if (!main_view)
        return nullptr;

    return main_view->getAxisView()->getAxisObject();
}
