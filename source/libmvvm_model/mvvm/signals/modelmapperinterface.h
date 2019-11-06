// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELMAPPERINTERFACE_H
#define MVVM_SIGNALS_MODELMAPPERINTERFACE_H

#include <mvvm/core/export.h>
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
    virtual void setOnRowInserted(Callbacks::item_str_int_t f, Callbacks::slot_t client) = 0;
    virtual void setOnRowRemoved(Callbacks::item_str_int_t f, Callbacks::slot_t client) = 0;
    virtual void setOnRowAboutToBeRemoved(Callbacks::item_str_int_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client) = 0;

private:
    virtual void callOnDataChange(SessionItem* item, int role) = 0;
    virtual void callOnRowInserted(SessionItem* parent, std::string tag, int row) = 0;
    virtual void callOnRowRemoved(SessionItem* parent, std::string tag, int row) = 0;
    virtual void callOnRowAboutToBeRemoved(SessionItem* parent, std::string tag, int row) = 0;
    virtual void callOnModelDestroyed() = 0;
    virtual void callOnModelReset() = 0;
};

} // namespace ModelView

#endif  // MVVM_SIGNALS_MODELMAPPERINTERFACE_H
