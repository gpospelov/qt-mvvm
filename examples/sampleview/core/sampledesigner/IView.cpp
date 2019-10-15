// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "IView.h"
#include "LocatedItem.h"
#include "itemmapper.h"
#include <QString>

using namespace ModelView;

IView::IView(QGraphicsItem *parent, int view_type)
    : QGraphicsObject(parent)
    , m_item(nullptr)
    , m_view_type(view_type)
{
    connect(this, &IView::xChanged, this, &IView::onChangedX);
    connect(this, &IView::yChanged, this, &IView::onChangedY);
}

IView::~IView()
{
    unsubscribe();
}

void IView::subscribe(SessionItem *item)
{
    if (m_item)
        unsubscribe();
    if (!item)
        return;

    m_item = item;

    if(toolTip().isEmpty())
        setToolTip(QString::fromStdString(item->displayName()));

    setX(m_item->property(LocatedItem::P_X_POS).toReal());
    setY(m_item->property(LocatedItem::P_Y_POS).toReal());

    auto on_property_change = [this](SessionItem*, std::string property) {
        onPropertyChange(property);
    };
    m_item->mapper()->setOnPropertyChange(on_property_change, this);
    m_item->mapper()->setOnItemDestroy([this](SessionItem*) { m_item = nullptr; }, this);

    update_appearance();
}

void IView::unsubscribe()
{
    if (!m_item)
        return;

    m_item->mapper()->unsubscribe(this);
    m_item = nullptr;
}

void IView::onChangedX()
{
    if(!m_item)
        return;
    m_item->setProperty(LocatedItem::P_X_POS, x());
}

void IView::onChangedY()
{
    if(!m_item)
        return;
    m_item->setProperty(LocatedItem::P_Y_POS, y());
}

//! updates visual appearance of the item (color, icons, size etc)
void IView::update_appearance()
{
    update();
}

void IView::onPropertyChange(const std::string& propertyName)
{
    Q_ASSERT(m_item);
    if (propertyName == LocatedItem::P_X_POS)
        setX(m_item->property(LocatedItem::P_X_POS).toReal());
    else if (propertyName == LocatedItem::P_Y_POS)
        setY(m_item->property(LocatedItem::P_Y_POS).toReal());
}
