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

IView::IView(QGraphicsItem *parent) : QGraphicsObject(parent), m_item(nullptr)
{
    connect(this, &IView::xChanged, this, &IView::onChangedX);
    connect(this, &IView::yChanged, this, &IView::onChangedY);
}

IView::~IView()
{
    if(m_item)
        m_item->mapper()->unsubscribe(this);
}

void IView::setParameterizedItem(SessionItem *item)
{
    Q_ASSERT(item);
    Q_ASSERT(m_item == nullptr);

    if(toolTip().isEmpty())
        setToolTip(QString::fromStdString(item->displayName()));

    m_item = item;
    setX(m_item->property(LocatedItem::P_X_POS).toReal());
    setY(m_item->property(LocatedItem::P_Y_POS).toReal());

    auto on_property_change = [this](SessionItem*, std::string property) {
        onPropertyChange(property);
    };
    m_item->mapper()->setOnPropertyChange(on_property_change, this);

    m_item->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_item = nullptr;
    }, this);


    update_appearance();
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
