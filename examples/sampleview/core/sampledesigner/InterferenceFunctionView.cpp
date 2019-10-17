// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "InterferenceFunctionView.h"
#include "DesignerHelper.h"
#include "item_constants.h"

InterferenceFunction1DLatticeView::InterferenceFunction1DLatticeView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction1DLatticeType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DLatticeView::InterferenceFunction2DLatticeView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DLatticeType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DParaCrystalType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionFinite2DLatticeView::InterferenceFunctionFinite2DLatticeView(
    QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunctionFinite2DLatticeType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionHardDiskView::InterferenceFunctionHardDiskView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunctionHardDiskType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionRadialParaCrystalView::InterferenceFunctionRadialParaCrystalView(
    QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunctionRadialParaCrystalType);
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getDefaultBoundingRect(getName()));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}
