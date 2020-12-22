// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mockwidgets.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/tagrow.h"
#include "mvvm/signals/itemmapper.h"
#include "mvvm/signals/modelmapper.h"

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
    if (m_item == item)
        return;

    if (m_item)
        m_item->mapper()->unsubscribe(this);

    m_item = item;

    if (!m_item)
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

    auto on_item_inserted = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onItemInserted(item, tagrow);
    };
    m_item->mapper()->setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onItemRemoved(item, tagrow);
    };
    m_item->mapper()->setOnItemRemoved(on_item_removed, this);

    auto on_about_to_remove_item = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onAboutToRemoveItem(item, tagrow);
    };
    m_item->mapper()->setOnAboutToRemoveItem(on_about_to_remove_item, this);
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
    if (m_model == model)
        return;

    if (m_model)
        m_model->mapper()->unsubscribe(this);

    m_model = model;

    if (!m_model)
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

    auto on_about_to_remove_item = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        onAboutToRemoveItem(item, tagrow);
    };
    m_model->mapper()->setOnAboutToRemoveItem(on_about_to_remove_item, this);

    auto on_model_destroyed = [this](ModelView::SessionModel* model) {
        m_model = nullptr;
        onModelDestroyed(model);
    };
    m_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);

    auto on_model_about_reset = [this](ModelView::SessionModel* model) {
        onModelAboutToBeReset(model);
    };
    m_model->mapper()->setOnModelAboutToBeReset(on_model_about_reset, this);

    auto on_model_reset = [this](ModelView::SessionModel* model) { onModelReset(model); };
    m_model->mapper()->setOnModelReset(on_model_reset, this);
}
