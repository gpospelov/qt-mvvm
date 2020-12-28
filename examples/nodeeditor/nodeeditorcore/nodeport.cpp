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

namespace {

double port_radius()
{
    return ModelView::Utils::WidthOfLetterM() * 0.4;
}

QColor port_color()
{
    return QColor(Qt::red);
}

} // namespace

namespace NodeEditor {

NodePort::NodePort(QGraphicsItem* parent) : QGraphicsPathItem(parent)
{
    QPainterPath p;
    p.addEllipse(-port_radius(), -port_radius(), 2 * port_radius(), 2 * port_radius());
    setPath(p);

    setPen(QPen(port_color().darker(180)));
    setBrush(port_color());
}

} // namespace NodeEditor
