// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodeport.h"
#include "mvvm/widgets/widgetutils.h"
#include <QPen>

namespace NodeEditor {

NodePort::NodePort(QGraphicsItem* parent) : QGraphicsPathItem(parent)
{
    const double radius = ModelView::Utils::WidthOfLetterM() * 0.4;
    const QColor color(Qt::red);

    QPainterPath p;
    p.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    setPath(p);

    setPen(QPen(color.darker(180)));
    setBrush(color);
}

// ----------------------------------------------------------------------------

bool NodeInputPort::isInput()
{
    return true;
}

bool NodeInputPort::isOutput()
{
    return false;
}

// ----------------------------------------------------------------------------

bool NodeOutputPort::isInput()
{
    return false;
}

bool NodeOutputPort::isOutput()
{
    return true;
}

} // namespace NodeEditor
