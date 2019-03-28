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
#include <iterator>
#include <stdexcept>

namespace
{
const std::string default_tag_name = "defaultTag";
int appearance(const ModelView::SessionItem& item)
{
    auto value = item.data(ModelView::ItemDataRole::APPEARANCE);
    return value.isValid() ? value.toInt()
                           : ModelView::Appearance::EDITABLE | ModelView::Appearance::ENABLED;
}
} // namespace

using namespace ModelView;

SessionItem::SessionItem(model_type modelType)
    : pimpl(std::make_unique<SessionItemPrivate>())
{
    pimpl->m_modelType = modelType;
    setDataIntern(QVariant::fromValue(ItemPool::generate_key()), ItemDataRole::IDENTIFIER);
}

SessionItem::~SessionItem()
{
    if (pimpl->m_mapper)
        pimpl->m_mapper->callOnItemDestroy();

    if (pimpl->m_parent)
        pimpl->m_parent->pimpl->childDeleted(this);

    if (pimpl->m_model)
        pimpl->m_model->make_registered(this, false);
}

model_type SessionItem::modelType() const
{
    return pimpl->m_modelType;
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
    if (pimpl->m_model)
        return pimpl->m_model->setData(this, variant, role); // to use undo/redo
    else
        return setDataIntern(variant, role);
}

QVariant SessionItem::data(int role) const
{
    return pimpl->m_data->data(role);
}

SessionModel* SessionItem::model() const
{
    return pimpl->m_model;
}

SessionItem* SessionItem::parent() const
{
    return pimpl->m_parent;
}

int SessionItem::childrenCount() const
{
    return static_cast<int>(children().size());
}

//! Returns child at given index of children array. No tags involved.

SessionItem* SessionItem::childAt(int index) const
{
    auto container = children();
    return index >= 0 && index < container.size() ? container[static_cast<size_t>(index)] : nullptr;
}

//! Insert item into given tag into given row.

bool SessionItem::insertItem(SessionItem* item, int row, const std::string& tag)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    auto result = pimpl->m_tags->insertItem(item, row, tag);
    if (result) {
        item->setParent(this);
        item->setModel(model());

        if (pimpl->m_model)
            pimpl->m_model->mapper()->callOnRowInserted(this, indexOfChild(item));
    }

    return result;
}

//! Removes item from given row from given tag, returns it to the caller.

SessionItem* SessionItem::takeItem(int row, const std::string& tag)
{
    // FIXME remove hack
    auto tmp = pimpl->m_tags->getItem(tag, row);
    int tmp_index = indexOfChild(tmp);

    auto result = pimpl->m_tags->takeItem(row, tag);
    if (result) {
        result->setParent(nullptr);
        result->setModel(nullptr);
        if (pimpl->m_model) {
            // FIXME remove one of methods
            pimpl->m_model->mapper()->callOnRowRemoved(this, tmp_index);
            pimpl->m_model->mapper()->callOnRowRemoved2(this, tmp_index, result->identifier());
        }
    }

    return result;
}

std::vector<SessionItem*> SessionItem::children() const
{
    return pimpl->m_tags->allitems();
}

//! Returns index in children array corresponding to given child. No tags involved.

int SessionItem::indexOfChild(SessionItem* child) const
{
    auto container = children();
    auto pos = find(container.begin(), container.end(), child);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}

std::vector<int> SessionItem::roles() const
{
    return pimpl->m_data->roles();
}

std::string SessionItem::defaultTag() const
{
    return pimpl->m_tags->defaultTag();
}

void SessionItem::setDefaultTag(const std::string& tag)
{
    setDataIntern(QVariant::fromValue(tag), ItemDataRole::DEFAULT_TAG);
    pimpl->m_tags->setDefaultTag(tag);
}

void SessionItem::registerTag(const TagInfo& tagInfo, bool set_as_default)
{
    pimpl->m_tags->registerTag(tagInfo, set_as_default);
}

bool SessionItem::isTag(const std::string& name)
{
    return pimpl->m_tags->isTag(name);
}

//! Returns item in given row of given tag.

SessionItem* SessionItem::getItem(const std::string& tag, int row) const
{
    return pimpl->m_tags->getItem(tag, row);
}

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
    return pimpl->m_tags->getItems(tag);
}

std::string SessionItem::tagFromItem(const SessionItem* item) const
{
    return pimpl->m_tags->tagIndexOfItem(item).first;
}

//! Returns item's row in its tag.

std::pair<std::string, int> SessionItem::tagIndexOfItem(const SessionItem* item) const
{
    return pimpl->m_tags->tagIndexOfItem(item);
}

ItemMapper* SessionItem::mapper()
{
    if (!pimpl->m_mapper)
        pimpl->m_mapper = std::make_unique<ItemMapper>(this);
    return pimpl->m_mapper.get();
}

//! Activates all buisiness logic of given item. Should be called after item constructions.
//! Intended for overload in child classes.

void SessionItem::activate() {}

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
    pimpl->m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    if (pimpl->m_model) {
        // FIXME throw here if it is the case
        pimpl->m_model->make_registered(this, false);
    }

    pimpl->m_model = model;

    if (pimpl->m_model) {
        pimpl->m_model->make_registered(this, true);
    }

    // FIXME find better place for activate logic. ItemMapper ? make_registered ?
    if (pimpl->m_model)
        activate(); // activate buisiness logic

    auto container = children();
    for (auto child : container)
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
    bool result = pimpl->m_data->setData(variant, role);
    if (result && pimpl->m_model)
        pimpl->m_model->mapper()->callOnDataChange(this, role);
    return result;
}
