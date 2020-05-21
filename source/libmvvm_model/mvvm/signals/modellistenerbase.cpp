// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modellistenerbase.h"
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

ModelListenerBase::ModelListenerBase(SessionModel* model) : m_model(model)
{
    auto on_model_destroy = [this](SessionModel*) { m_model = nullptr; };
    m_model->mapper()->setOnModelDestroyed(on_model_destroy, this);
}

ModelListenerBase::~ModelListenerBase()
{
    if (m_model)
        m_model->mapper()->unsubscribe(this);
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ModelListenerBase::setOnDataChange(ModelView::Callbacks::item_int_t f)
{
    m_model->mapper()->setOnDataChange(f, this);
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, tagrow), where tagrow corresponds
//! to the position of inserted child.

void ModelListenerBase::setOnItemInserted(ModelView::Callbacks::item_tagrow_t f)
{
    m_model->mapper()->setOnItemInserted(f, this);
}

//! Sets callback to be notified on removed item.
//! Callback will be called with (SessionItem* parent, tagrow), where tagrow corresponds
//! to position of the removed child.

void ModelListenerBase::setOnItemRemoved(ModelView::Callbacks::item_tagrow_t f)
{
    m_model->mapper()->setOnItemRemoved(f, this);
}

//! Sets callback to be notified when item is about to be removed.
//! Callback will be called with (SessionItem* parent, tagrow), where tagrow corresponds
//! to the position of a child which going to be removed.

void ModelListenerBase::setOnAboutToRemoveItem(ModelView::Callbacks::item_tagrow_t f)
{
    m_model->mapper()->setOnAboutToRemoveItem(f, this);
}

//! Sets the callback to be notified before model's full reset (root item recreated).

void ModelListenerBase::setOnModelAboutToBeReset(Callbacks::model_t f)
{
    m_model->mapper()->setOnModelAboutToBeReset(f, this);
}

//! Sets the callback to be notified after model was fully reset (root item recreated).

void ModelListenerBase::setOnModelReset(ModelView::Callbacks::model_t f)
{
    m_model->mapper()->setOnModelReset(f, this);
}
