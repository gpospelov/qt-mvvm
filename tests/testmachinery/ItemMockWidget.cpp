#include "ItemMockWidget.h"
#include "sessionitem.h"
#include "itemmapper.h"


MockWidget::MockWidget(ModelView::SessionItem* item)
    : m_item(nullptr)
{
    setItem(item);
}

MockWidget::~MockWidget()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void MockWidget::setItem(ModelView::SessionItem* item)
{
    m_item = item;

    m_item->mapper()->setOnItemDestroy([this](ModelView::SessionItem* item) {
        m_item = nullptr;
        onItemDestroy(item);
    }, this);

    m_item->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    }, this);
}

