#include "ItemMockWidget.h"
#include "sessionitem.h"
#include "itemmapper.h"
#include "sessionmodel.h"
#include "modelmapper.h"


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

    if (m_item == nullptr)
        return;

    m_item->mapper()->setOnItemDestroy([this](ModelView::SessionItem* item) {
        m_item = nullptr;
        onItemDestroy(item);
    }, this);

    m_item->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    }, this);
}

// ----------------------------------------------------------------------------

MockWidgetForModel::MockWidgetForModel(ModelView::SessionModel* model)
    : m_model(nullptr)
{
    setModel(model);
}

void MockWidgetForModel::setModel(ModelView::SessionModel* model)
{
    m_model = model;

    if (m_model == nullptr)
        return;

    m_model->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    }, this);
}

