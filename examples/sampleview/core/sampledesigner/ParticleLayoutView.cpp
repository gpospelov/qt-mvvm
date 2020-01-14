// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ParticleLayoutView.h"
#include "DesignerHelper.h"
#include <QGraphicsScene>

namespace
{
constexpr qreal layout_width = IView::basic_width * 1.08;
constexpr qreal layout_height = IView::basic_height * 4.5;
} // namespace

ParticleLayoutView::ParticleLayoutView(QGraphicsItem* parent)
    : ConnectableView(parent, DesignerHelper::PARTICLE_LAYOUT)
{
    setColor(QColor(135, 206, 50));
    setRectangle(QRectF(-layout_width / 2.0, -layout_height / 2.0, layout_width, layout_height));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::PARTICLE_LAYOUT)
        ->setToolTip(QStringLiteral("Connect this port with the layer "
                                    "to populate it with particles"));
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect one or several particles to this port"));
    addPort("interference", NodeEditorPort::INPUT, NodeEditorPort::INTERFERENCE)
        ->setToolTip(QStringLiteral("Connect interference to this port "
                                    "to have coherent scattering"));
    m_roundpar = 3;
}

void ParticleLayoutView::addView(IView* childView)
{
    if (childView->type() == DesignerHelper::PARTICLE) {
        connectInputPort(dynamic_cast<ConnectableView*>(childView), 0);
    } else if (childView->type() == DesignerHelper::INTERFERENCE_FUNCTION) {
        connectInputPort(dynamic_cast<ConnectableView*>(childView), 1);
    } else {
        throw std::runtime_error("ParticleLayoutView::addView() -> Error. Unknown view");
    }
    scene()->addItem(childView);
}
