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

NodePort::NodePort(QGraphicsItem* parent, const QString& portType)
    : QGraphicsPathItem(parent), m_portType(portType)
{
    const double radius = ModelView::Utils::WidthOfLetterM() * 0.4;
    const QColor color(Qt::red);

    QPainterPath p;
    p.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    setPath(p);

    setPen(QPen(color.darker(180)));
    setBrush(color);
}

//! Returns port type. Input and output ports of the same type are compatible.

QString NodePort::portType() const
{
    return m_portType;
}

bool NodePort::isOutput() const
{
    return !isInput();
}

// ----------------------------------------------------------------------------

bool NodeInputPort::isInput() const
{
    return true;
}

// ----------------------------------------------------------------------------

bool NodeOutputPort::isInput() const
{
    return false;
}

} // namespace NodeEditor
