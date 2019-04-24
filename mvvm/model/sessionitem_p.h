// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SESSIONITEM_P_H
#define MVVM_SESSIONITEM_P_H

#include "model_types.h"
#include <memory>

namespace ModelView
{

class SessionItem;
class SessionModel;
class ItemMapper;
class SessionItemData;
class SessionItemTags;

//! Pimpl parts of SessionItem.

class SessionItemPrivate
{
public:
    SessionItemPrivate();
    ~SessionItemPrivate();

    SessionItem* m_parent;
    SessionModel* m_model;
    std::unique_ptr<ItemMapper> m_mapper;
    std::unique_ptr<SessionItemData> m_data;
    std::unique_ptr<SessionItemTags> m_tags;
    model_type m_modelType;
};

} // namespace ModelView

#endif // MVVM_SESSIONITEM_P_H
