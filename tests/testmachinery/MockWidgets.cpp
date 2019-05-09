#include "MockWidgets.h"
#include "itemmapper.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"

// ----------------------------------------------------------------------------

MockWidgetForItem::MockWidgetForItem(ModelView::SessionItem* item) : m_item(nullptr)
{
    setItem(item);
}

MockWidgetForItem::~MockWidgetForItem()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void MockWidgetForItem::setItem(ModelView::SessionItem* item)
{
    m_item = item;

    if (m_item == nullptr)
        return;

    auto itemDestroy = [this](ModelView::SessionItem* item) {
        m_item = nullptr;
        onItemDestroy(item);
    };
    m_item->mapper()->setOnItemDestroy(itemDestroy, this);

    auto dataChange = [this](ModelView::SessionItem* item, int role) { onDataChange(item, role); };
    m_item->mapper()->setOnDataChange(dataChange, this);

    auto propertyChange = [this](ModelView::SessionItem* item, std::string name) {
        onPropertyChange(item, name);
    };
    m_item->mapper()->setOnPropertyChange(propertyChange, this);
}

// ----------------------------------------------------------------------------

MockWidgetForModel::MockWidgetForModel(ModelView::SessionModel* model) : m_model(nullptr)
{
    setModel(model);
}

MockWidgetForModel::~MockWidgetForModel()
{
    if (m_model)
        m_model->mapper()->unsubscribe(this);
}

void MockWidgetForModel::setModel(ModelView::SessionModel* model)
{
    m_model = model;

    if (m_model == nullptr)
        return;

    auto dataChange = [this](ModelView::SessionItem* item, int role) { onDataChange(item, role); };
    m_model->mapper()->setOnDataChange(dataChange, this);

    auto rowInserted = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onRowInserted(item, tag, row);
    };
    m_model->mapper()->setOnRowInserted(rowInserted, this);

    auto rowRemoved = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onRowRemoved(item, tag, row);
    };
    m_model->mapper()->setOnRowRemoved(rowRemoved, this);

    auto modelDestroyed = [this](ModelView::SessionModel* model) {
        m_model = nullptr;
        onModelDestroyed(model);
    };
    m_model->mapper()->setOnModelDestroyed(modelDestroyed, this);

    auto modelReset = [this](ModelView::SessionModel* model) { onModelReset(model); };
    m_model->mapper()->setOnModelReset(modelReset, this);
}
