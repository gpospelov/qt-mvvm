// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "MockWidgets.h"
#include <mvvm/signals/itemmapper.h>
#include <mvvm/signals/modelmapper.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>

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

    auto on_item_destroy = [this](ModelView::SessionItem* item) {
        m_item = nullptr;
        onItemDestroy(item);
    };
    m_item->mapper()->setOnItemDestroy(on_item_destroy, this);

    auto on_data_change = [this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    };
    m_item->mapper()->setOnDataChange(on_data_change, this);

    auto on_property_change = [this](ModelView::SessionItem* item, std::string name) {
        onPropertyChange(item, name);
    };
    m_item->mapper()->setOnPropertyChange(on_property_change, this);

    auto on_child_property_change = [this](ModelView::SessionItem* item, std::string name) {
        onChildPropertyChange(item, name);
    };
    m_item->mapper()->setOnChildPropertyChange(on_child_property_change, this);

    auto on_row_inserted = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onRowInserted(item, tag, row);
    };
    m_item->mapper()->setOnRowInserted(on_row_inserted, this);

    auto on_row_about_removed = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onRowAboutToBeRemoved(item, tag, row);
    };
    m_item->mapper()->setOnRowAboutToBeRemoved(on_row_about_removed, this);
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

    auto on_data_change = [this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    };
    m_model->mapper()->setOnDataChange(on_data_change, this);

    auto on_item_inserted = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onItemInserted(item, tagrow);
    };
    m_model->mapper()->setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onItemRemoved(item, tagrow);
    };
    m_model->mapper()->setOnItemRemoved(on_item_removed, this);

    auto on_item_about_removed = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onItemAboutToBeRemoved(item, tagrow);
    };
    m_model->mapper()->setOnItemAboutToBeRemoved(on_item_about_removed, this);

    auto on_model_destroyed = [this](ModelView::SessionModel* model) {
        m_model = nullptr;
        onModelDestroyed(model);
    };
    m_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);

    auto on_model_reset = [this](ModelView::SessionModel* model) { onModelReset(model); };
    m_model->mapper()->setOnModelReset(on_model_reset, this);
}
