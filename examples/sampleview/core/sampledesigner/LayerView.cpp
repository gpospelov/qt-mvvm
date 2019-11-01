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
#include "ParticleLayoutView.h"
#include "externalproperty.h"
#include "item_constants.h"
#include "mvvm_types.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
constexpr qreal basic_layer_width = IView::basic_width;
constexpr qreal basic_layer_height = IView::basic_height;
constexpr qreal max_layer_height = 500.0;

constexpr QRectF defaultShape();
// linear conversion of layer's thickness in nanometers to screen size to have reasonable
// graphics representation
qreal thicknessToHeight(double nm);
}

using namespace ModelView;

LayerView::LayerView(QGraphicsItem *parent)
    : ILayerView(parent, DesignerHelper::LAYER)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(defaultShape());
    setAcceptDrops(false);
    addPort(QString(), NodeEditorPort::INPUT, NodeEditorPort::PARTICLE_LAYOUT);
}

void LayerView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}

void LayerView::addView(IView* view)
{
    ParticleLayoutView* layout = dynamic_cast<ParticleLayoutView*>(view);
    if (!layout)
        return;
    connectInputPort(layout, 0);
    scene()->addItem(view);
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

    const double thickness = getItem()->property(LayerItem::P_THICKNESS).value<double>();
    const qreal height = thicknessToHeight(thickness);
    m_rect.setTop(-height / 2.0);
    m_rect.setHeight(height);
    setPortCoordinates();
    update();
    emit heightChanged();
}

void LayerView::updateColor()
{
    if(getItem()->isTag(LayerItem::P_MATERIAL)) {
        QVariant v = getItem()->getItem(LayerItem::P_MATERIAL)->data();
        if (v.isValid()) {
            auto mp = v.value<ExternalProperty>();
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
constexpr QRectF defaultShape()
{
    return QRectF(-basic_layer_width / 2.0, -basic_layer_height / 2.0, basic_layer_width,
                  basic_layer_height);
}

qreal thicknessToHeight(double nm)
{
    return nm > 0 ? std::min(basic_layer_height + nm, max_layer_height) : basic_layer_height;
}
}
