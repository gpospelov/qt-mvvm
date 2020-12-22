// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/signals/modellistenerbase.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/signals/modelmapper.h"
#include <stdexcept>

using namespace ModelView;

ModelListenerBase::ModelListenerBase(SessionModel* model) : m_model(model)
{
    if (!m_model)
        throw std::runtime_error("Error in ModelListenerBase: no model defined");
    setOnModelDestroyed([this](SessionModel*) { m_model = nullptr; });
}

ModelListenerBase::~ModelListenerBase()
{
    unsubscribe();
}

//! Sets callback to be notified on item's data change. The callback will be called
//! with (SessionItem*, data_role).

void ModelListenerBase::setOnDataChange(ModelView::Callbacks::item_int_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnDataChange(f, this);
}

//! Sets callback to be notified on item insert. The callback will be called with
//! (SessionItem* parent, tagrow), where 'tagrow' denotes inserted child position.

void ModelListenerBase::setOnItemInserted(ModelView::Callbacks::item_tagrow_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnItemInserted(f, this);
}

//! Sets callback to be notified on item remove. The callback will be called with
//! (SessionItem* parent, tagrow), where 'tagrow' denotes child position before the removal.

void ModelListenerBase::setOnItemRemoved(ModelView::Callbacks::item_tagrow_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnItemRemoved(f, this);
}

//! Sets callback to be notified when the item is about to be removed. The callback will be called
//! with (SessionItem* parent, tagrow), where 'tagrow' denotes child position being removed.

void ModelListenerBase::setOnAboutToRemoveItem(ModelView::Callbacks::item_tagrow_t f,
                                               Callbacks::slot_t)
{
    m_model->mapper()->setOnAboutToRemoveItem(f, this);
}

//! Sets the callback for notifications on model destruction.

void ModelListenerBase::setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelDestroyed(f, this);
}

//! Sets the callback to be notified before model's full reset (root item recreated).

void ModelListenerBase::setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelAboutToBeReset(f, this);
}

//! Sets the callback to be notified after model was fully reset (root item recreated).

void ModelListenerBase::setOnModelReset(ModelView::Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelReset(f, this);
}

void ModelListenerBase::unsubscribe(Callbacks::slot_t)
{
    if (m_model)
        m_model->mapper()->unsubscribe(this);
}
