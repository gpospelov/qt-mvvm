// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitem.h"
#include "itemmanager.h"
#include "itempool.h"
#include "itemutils.h"
#include "itemmapper.h"
#include "modelmapper.h"
#include "sessionitemdata.h"
#include "sessionitemtags.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "customvariants.h"
#include "sessionitem_p.h"
#include <stdexcept>

namespace
{
int appearance(const ModelView::SessionItem& item)
{
    auto value = item.data(ModelView::ItemDataRole::APPEARANCE);
    return value.isValid() ? value.toInt()
                           : ModelView::Appearance::EDITABLE | ModelView::Appearance::ENABLED;
}
} // namespace

using namespace ModelView;

SessionItem::SessionItem(model_type modelType)
    : p_impl(std::make_unique<SessionItemPrivate>())
{
    p_impl->m_modelType = modelType;
    setDataIntern(QVariant::fromValue(ItemPool::generate_key()), ItemDataRole::IDENTIFIER);
    setDataIntern(QVariant::fromValue(modelType), ItemDataRole::DISPLAY);
}

SessionItem::~SessionItem()
{
    if (p_impl->m_mapper)
        p_impl->m_mapper->callOnItemDestroy();

    if (p_impl->m_model)
        p_impl->m_model->unregister_item(this);
}

model_type SessionItem::modelType() const
{
    return p_impl->m_modelType;
}

std::string SessionItem::displayName() const
{
    return data(ItemDataRole::DISPLAY).value<std::string>();
}

void SessionItem::setDisplayName(const std::string& name)
{
    setData(QVariant::fromValue(name), ItemDataRole::DISPLAY);
}

std::string SessionItem::identifier() const
{
    return data(ItemDataRole::IDENTIFIER).value<std::string>();
}

bool SessionItem::setData(const QVariant& variant, int role)
{
    if (p_impl->m_model)
        return p_impl->m_model->setData(this, variant, role); // to use undo/redo
    else
        return setDataIntern(variant, role);
}

QVariant SessionItem::data(int role) const
{
    return p_impl->m_data->data(role);
}

SessionModel* SessionItem::model() const
{
    return p_impl->m_model;
}

SessionItem* SessionItem::parent() const
{
    return p_impl->m_parent;
}

int SessionItem::childrenCount() const
{
    return static_cast<int>(children().size());
}

//! Insert item into given tag under the given index.

bool SessionItem::insertItem(SessionItem* item, const std::string& tag, int index)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    if (item->model())
        throw std::runtime_error("SessionItem::insertItem() -> Existing model.");

    auto result = p_impl->m_tags->insertItem(item, tag, index);
    if (result) {
        item->setParent(this);
        item->setModel(model());

        if (p_impl->m_model)
            p_impl->m_model->mapper()->callOnRowInserted(this, tag, index);
    }

    return result;
}

//! Removes item from given row from given tag, returns it to the caller.

SessionItem* SessionItem::takeItem(const std::string& tag, int index)
{
    auto result = p_impl->m_tags->takeItem(tag, index);
    if (result) {
        result->setParent(nullptr);
        result->setModel(nullptr);
        // FIXME remaining problem is that ItemMapper still looking to the model
        if (p_impl->m_model)
            p_impl->m_model->mapper()->callOnRowRemoved(this, tag, index);
    }

    return result;
}

//! Returns vector of children formed from all chidlren from all tags.

std::vector<SessionItem*> SessionItem::children() const
{
    return p_impl->m_tags->allitems();
}

//! Return vector of data roles which this item currently holds.

std::vector<int> SessionItem::roles() const
{
    return p_impl->m_data->roles();
}

//! Returns the name of the default tag.

std::string SessionItem::defaultTag() const
{
    return p_impl->m_tags->defaultTag();
}

//! Sets the default tag.

void SessionItem::setDefaultTag(const std::string& tag)
{
    p_impl->m_tags->setDefaultTag(tag);
}

//! Registers tag to hold items under given name.

void SessionItem::registerTag(const TagInfo& tagInfo, bool set_as_default)
{
    p_impl->m_tags->registerTag(tagInfo, set_as_default);
}

//! Returns true if tag with given name exists.

bool SessionItem::isTag(const std::string& name)
{
    return p_impl->m_tags->isTag(name);
}

//! Returns item at given index of given tag.

SessionItem* SessionItem::getItem(const std::string& tag, int index) const
{
    return p_impl->m_tags->getItem(tag, index);
}

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
    return p_impl->m_tags->getItems(tag);
}

std::string SessionItem::tagFromItem(const SessionItem* item) const
{
    return p_impl->m_tags->tagIndexOfItem(item).first;
}

//! Returns pair of tag and index corresponding to given item.

std::pair<std::string, int> SessionItem::tagIndexOfItem(const SessionItem* item) const
{
    return p_impl->m_tags->tagIndexOfItem(item);
}

ItemMapper* SessionItem::mapper()
{
    if (!p_impl->m_mapper)
        p_impl->m_mapper = std::make_unique<ItemMapper>(this);
    return p_impl->m_mapper.get();
}

bool SessionItem::isEditable() const
{
    return appearance(*this) & Appearance::EDITABLE;
}

void SessionItem::setEditable(bool value)
{
    setAppearanceFlag(Appearance::EDITABLE, value);
}

bool SessionItem::isEnabled() const
{
    return appearance(*this) & Appearance::ENABLED;
}

void SessionItem::setEnabled(bool value)
{
    setAppearanceFlag(Appearance::ENABLED, value);
}

void SessionItem::setParent(SessionItem* parent)
{
    p_impl->m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    if (p_impl->m_model)
        p_impl->m_model->unregister_item(this);

    p_impl->m_model = model;

    if (p_impl->m_model)
        p_impl->m_model->register_item(this);

    for (auto child : children())
        child->setModel(model);
}

void SessionItem::setAppearanceFlag(int flag, bool value)
{
    int flags = appearance(*this);
    if (value)
        flags |= flag;
    else
        flags &= ~flag;

    setDataIntern(flags, ItemDataRole::APPEARANCE);
}

bool SessionItem::setDataIntern(const QVariant& variant, int role)
{
    bool result = p_impl->m_data->setData(variant, role);
    if (result && p_impl->m_model)
        p_impl->m_model->mapper()->callOnDataChange(this, role);
    return result;
}
