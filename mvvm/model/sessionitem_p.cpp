// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitem_p.h"
#include "sessionitemtags.h"
#include "sessionitemdata.h"
#include "itemmapper.h"

using namespace ModelView;

SessionItemPrivate::SessionItemPrivate()
    : m_parent(nullptr), m_model(nullptr), m_data(std::make_unique<SessionItemData>()), m_tags(std::make_unique<SessionItemTags>())
{

}

SessionItemPrivate::~SessionItemPrivate() = default;

void SessionItemPrivate::setParent(SessionItem* parent)
{
    m_parent = parent;
}

void SessionItemPrivate::childDeleted(SessionItem* child)
{
    m_tags->itemDeleted(child);
}
