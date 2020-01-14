// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELMAPPERINTERFACE_H
#define MVVM_SIGNALS_MODELMAPPERINTERFACE_H

#include <mvvm/core/export.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/signals/callback_types.h>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Provides notifications on various SessionModel changes.

class CORE_EXPORT ModelMapperInterface
{
    friend class SessionModel;
    friend class SessionItem;

public:
    virtual ~ModelMapperInterface() = default;

    virtual void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client) = 0;
    virtual void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client) = 0;

private:
    virtual void callOnDataChange(SessionItem* item, int role) = 0;
    virtual void callOnItemInserted(SessionItem* parent, TagRow tagrow) = 0;
    virtual void callOnItemRemoved(SessionItem* parent, TagRow tagrow) = 0;
    virtual void callOnAboutToRemoveItem(SessionItem* parent, TagRow tagrow) = 0;
    virtual void callOnModelDestroyed() = 0;
    virtual void callOnModelReset() = 0;
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELMAPPERINTERFACE_H
