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
#include "externalproperty.h"
#include "item_constants.h"
#include "mvvm_types.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
// non-linear conversion of layer's thickness in nanometers to screen size to have reasonable
// graphics representation
int nanometerToScreen(double nanometer);
}

using namespace ModelView;

LayerView::LayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(DesignerHelper::getDefaultBoundingRect(::Constants::LayerType));
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

void LayerView::onPropertyChange(const std::string& propertyName)
{
    if (propertyName == LayerItem::P_THICKNESS) {
        updateHeight();
    } else if (propertyName == LayerItem::P_MATERIAL) {
        updateColor();
        updateLabel();
    }

    ILayerView::onPropertyChange(propertyName);
}

void LayerView::update_appearance()
{
    updateHeight();
    updateColor();
    updateLabel();
    ILayerView::update_appearance();
}

void LayerView::updateHeight()
{
    if (!getItem()->isTag(LayerItem::P_THICKNESS))
        return;

    const double thickness = getItem()->getItemValue(LayerItem::P_THICKNESS).toDouble();
    m_rect.setHeight(nanometerToScreen(thickness));
    setPortCoordinates();
    update();
    emit heightChanged();
}

void LayerView::updateColor()
{
    if(getItem()->isTag(LayerItem::P_MATERIAL)) {
        QVariant v = getItem()->getItem(LayerItem::P_MATERIAL)->data();
        if (v.isValid()) {
            ExternalProperty mp = v.value<ExternalProperty>();
            setColor(mp.color());
            update();
        } else {
            Q_ASSERT(0);
        }
    }
}

// FIXME: this method has nothing to do with ports. For unknown reason it uses them to set label.
void LayerView::updateLabel()
{
    if(getInputPorts().size() < 1)
        return;

    NodeEditorPort *port = getInputPorts()[0];

    QString material = "" ;
    if(getItem()->isTag(LayerItem::P_MATERIAL)){
        QVariant v = getItem()->getItem(LayerItem::P_MATERIAL)->data();
        if (v.isValid()) {
            ExternalProperty mp = v.value<ExternalProperty>();
            material = QString::fromStdString(mp.text());
        }
    }

    QString infoToDisplay = material;
    port->setLabel(infoToDisplay);
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
