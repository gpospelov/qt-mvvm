// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/LayerView.cpp
//! @brief     Implements class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "LayerView.h"
#include "LayerItems.h"
#include "item_constants.h"
#include "mvvm_types.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
// non-linear conversion of layer's thickness in nanometers to screen size to have reasonable
// graphics representation
int nanometerToScreen(double nanometer);
}

LayerView::LayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::LayerType));
    setAcceptDrops(false);
    addPort(QString(), NodeEditorPort::INPUT, NodeEditorPort::PARTICLE_LAYOUT);
}


void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}

void LayerView::addView(IView*)
{
    /*ParticleLayoutView *layout = dynamic_cast<ParticleLayoutView *>(childView);
    Q_ASSERT(layout);
    connectInputPort(layout, 0);*/
}

void LayerView::updateHeight()
{
    if (!getItem()->isTag(LayerItem::P_THICKNESS))
        return;

    const double thickness =
        getItem()->getItem(LayerItem::P_THICKNESS)->data(ModelView::ItemDataRole::DATA).toDouble();
    m_rect.setHeight(nanometerToScreen(thickness));
    setPortCoordinates();
    update();
    emit heightChanged();
}

namespace {
int nanometerToScreen(double nanometer)
{
    const int ymin(DesignerHelper::getDefaultLayerHeight());
    const int ymax(500);
    int result(ymin);
    if (nanometer > 0)
        result = qBound(ymin, ymin + (int)std::pow(nanometer, 0.9), ymax);
    return result;
}
}
