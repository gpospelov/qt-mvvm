// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/sessionitem.h"
#include "mvvm/core/uniqueidgenerator.h"
#include "mvvm/model/sessionitemdata.h"
#include "mvvm/model/sessionitemtags.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/signals/itemmapper.h"
#include "mvvm/signals/modelmapper.h"
#include <stdexcept>

using namespace ModelView;

namespace {
int appearance(const ModelView::SessionItem& item)
{
    const int default_appearance = Appearance::EDITABLE | Appearance::ENABLED | Appearance::VISIBLE;
    return item.hasData(ItemDataRole::APPEARANCE) ? item.data<int>(ItemDataRole::APPEARANCE)
                                                  : default_appearance;
}
} // namespace

struct SessionItem::SessionItemImpl {
    SessionItem* m_self{nullptr};
    SessionItem* m_parent{nullptr};
    SessionModel* m_model{nullptr};
    std::unique_ptr<ItemMapper> m_mapper;
    std::unique_ptr<SessionItemData> m_data;
    std::unique_ptr<SessionItemTags> m_tags;
    model_type m_modelType;

    SessionItemImpl(SessionItem* this_item)
        : m_self(this_item)
        , m_data(std::make_unique<SessionItemData>())
        , m_tags(std::make_unique<SessionItemTags>())
    {
    }

    bool do_setData(const Variant& variant, int role)
    {
        bool result = m_data->setData(variant, role);
        if (result && m_model)
            m_model->mapper()->callOnDataChange(m_self, role);
        return result;
    }
};

SessionItem::SessionItem(model_type modelType) : p_impl(std::make_unique<SessionItemImpl>(this))
{
    p_impl->m_modelType = std::move(modelType);
    setData(UniqueIdGenerator::generate(), ItemDataRole::IDENTIFIER);
    setData(p_impl->m_modelType, ItemDataRole::DISPLAY);
}

SessionItem::~SessionItem()
{
    if (p_impl->m_mapper)
        p_impl->m_mapper->callOnItemDestroy();

    if (p_impl->m_model)
        p_impl->m_model->unregisterFromPool(this);
}

//! Returns item's model type.

model_type SessionItem::modelType() const
{
    return p_impl->m_modelType;
}

//! Returns unique identifier.

std::string SessionItem::identifier() const
{
    return data<std::string>(ItemDataRole::IDENTIFIER);
}

//! Returns display name.

std::string SessionItem::displayName() const
{
    return data<std::string>(ItemDataRole::DISPLAY);
}

//! Sets display name (fluent interface).

SessionItem* SessionItem::setDisplayName(const std::string& name)
{
    setData(name, ItemDataRole::DISPLAY);
    return this;
}

//! Returns the model to which given item belongs to. Will return nullptr if item doesn't have a
//! model.

SessionModel* SessionItem::model() const
{
    return p_impl->m_model;
}

//! Returns parent item. Will return nullptr if item doesn't have a parent.

SessionItem* SessionItem::parent() const
{
    return p_impl->m_parent;
}

//! Returns TagRow of this item under which it is accessible through its parent.

TagRow SessionItem::tagRow() const
{
    return parent() ? parent()->tagRowOfItem(this) : TagRow();
}

//! Returns true if item has data on board with given role.

bool SessionItem::hasData(int role) const
{
    return p_impl->m_data->hasData(role);
}

//! Returns pointer to item's data container (const version).

const SessionItemData* SessionItem::itemData() const
{
    return p_impl->m_data.get();
}

//! Returns pointer to item's data container (non-const version).

SessionItemData* SessionItem::itemData()
{
    return const_cast<SessionItemData*>(static_cast<const SessionItem*>(this)->itemData());
}

//! Returns total number of children in all tags.

int SessionItem::childrenCount() const
{
    return static_cast<int>(children().size());
}

//! Returns vector of children formed from all chidlren from all tags.

std::vector<SessionItem*> SessionItem::children() const
{
    return p_impl->m_tags->allitems();
}

//! Returns number of items in given tag.

int SessionItem::itemCount(const std::string& tag) const
{
    return p_impl->m_tags->itemCount(tag);
}

//! Returns item at given row of given tag.

SessionItem* SessionItem::getItem(const std::string& tag, int row) const
{
    return p_impl->m_tags->getItem({tag, row});
}

//! Returns all children stored at given tag.

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
    return p_impl->m_tags->getItems(tag);
}

//! Returns pair of tag and row corresponding to given item.
//! Returns {"", -1} if given item doesn't belong to children.

TagRow SessionItem::tagRowOfItem(const SessionItem* item) const
{
    return p_impl->m_tags->tagRowOfItem(item);
}

//! Returns pointer to internal collection of tag-registered items (const version).

const SessionItemTags* SessionItem::itemTags() const
{
    return p_impl->m_tags.get();
}

//! Registers tag to hold items under given name.

void SessionItem::registerTag(const TagInfo& tagInfo, bool set_as_default)
{
    p_impl->m_tags->registerTag(tagInfo, set_as_default);
}

//! Returns pointer to internal collection of tag-registered items (non-const version).

SessionItemTags* SessionItem::itemTags()
{
    return const_cast<SessionItemTags*>(static_cast<const SessionItem*>(this)->itemTags());
}

//! Inserts the item into the given tag under the given row.
//! Returns 'true' in the case of success, take ownership over the item.
//! If an item can't be inserted for a given TagRow (i.e. when the container is full, or not
//! intended for items of a given type) will return false and will not take ownership.

bool SessionItem::insertItem(SessionItem* item, const TagRow& tagrow)
{
    if (!p_impl->m_tags->canInsertItem(item, tagrow))
        return false;
    return insertItem(std::unique_ptr<SessionItem>(item), tagrow) != nullptr;
}

//! Insert item into given tag under the given row. Will take ownership of inserted item.
//! Returns back a pointer to the same item for convenience.

SessionItem* SessionItem::insertItem(std::unique_ptr<SessionItem> item, const TagRow& tagrow)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    if (item->model())
        throw std::runtime_error("SessionItem::insertItem() -> Existing model.");

    if (!p_impl->m_tags->canInsertItem(item.get(), tagrow))
        throw std::runtime_error("SessionItem::insertItem() -> Can't insert item.");

    auto result = item.release();
    p_impl->m_tags->insertItem(result, tagrow);
    result->setParent(this);
    result->setModel(model());

    if (p_impl->m_model) {
        // FIXME think of actual_tagrow removal if input tag,row will be always valid
        auto actual_tagrow = tagRowOfItem(result);
        p_impl->m_model->mapper()->callOnItemInserted(this, actual_tagrow);
    }

    return result;
}


//! Removes item from given row from given tag, returns it to the caller.
//! Ownership is granted to the caller.

std::unique_ptr<SessionItem> SessionItem::takeItem(const TagRow& tagrow)
{
    if (!p_impl->m_tags->canTakeItem(tagrow))
        return {};

    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemAboutToBeRemoved(this, tagrow);

    auto result = p_impl->m_tags->takeItem(tagrow);
    result->setParent(nullptr);
    result->setModel(nullptr);
    // FIXME remaining problem is that ItemMapper still looking to the model
    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemRemoved(this, tagrow);

    return std::unique_ptr<SessionItem>(result);
}

//! Returns true if this item has `editable` flag set.
//! The data value of an editable item normally can be changed when it appears in trees and tables.

bool SessionItem::isEditable() const
{
    return appearance(*this) & Appearance::EDITABLE;
}

//! Sets `editable` flag to given value (fluent interface).

SessionItem* SessionItem::setEditable(bool value)
{
    setAppearanceFlag(Appearance::EDITABLE, value);
    return this;
}

//! Returns true if this item has `enabled` flag set.

bool SessionItem::isEnabled() const
{
    return appearance(*this) & Appearance::ENABLED;
}

//! Sets `enabled` flag to given value (fluent interface). Used in Qt-widgets to show that given
//! property is currently enabled. Enabled items appear in normal color, disabled items are grayed
//! out.

SessionItem* SessionItem::setEnabled(bool value)
{
    setAppearanceFlag(Appearance::ENABLED, value);
    return this;
}

//! Returns true if this item has `visible` flag set.

bool SessionItem::isVisible() const
{
    return appearance(*this) & Appearance::VISIBLE;
}

//! Sets `visible` flag to given value (fluent interface). Used in Qt-widgets to hide given
//! property from a view. For example, `PropertyTreeView` will not show PropertyItem with the given
//! flag set to `true` among other properties.

SessionItem* SessionItem::setVisible(bool value)
{
    setAppearanceFlag(Appearance::VISIBLE, value);
    return this;
}

//! Returns item tooltip, if exists.

std::string SessionItem::toolTip() const
{
    return hasData(ItemDataRole::TOOLTIP) ? data<std::string>(ItemDataRole::TOOLTIP)
                                          : std::string();
}

//! Sets item tooltip (fluent interface).

SessionItem* SessionItem::setToolTip(const std::string& tooltip)
{
    setData(tooltip, ItemDataRole::TOOLTIP);
    return this;
}

//! Returns editor type.

std::string SessionItem::editorType() const
{
    return hasData(ItemDataRole::EDITORTYPE) ? data<std::string>(ItemDataRole::EDITORTYPE)
                                             : std::string();
}

//! Sets editor type (fluent interface).
//! Allows creating custom editors in the cells of Qt trees and tables.

SessionItem* SessionItem::setEditorType(const std::string& editor_type)
{
    setData(editor_type, ItemDataRole::EDITORTYPE);
    return this;
}

//! Sets the data for given role. Method invented to hide implementaiton details.

bool SessionItem::set_data_internal(const Variant& value, int role, bool direct)
{
    // If model is present, and undo stack is enabled, will forward request to the model
    // (unless user explicitely asks for direct processing via direct=true flag).
    const bool act_through_model = !direct && model() && model()->undoStack();
    return act_through_model ? model()->setData(this, value, role)
                             : p_impl->do_setData(value, role);
}

//! Returns data for given role. Method invented to hide implementaiton details and avoid
//! placing sessionitemdata.h into 'sessionitem.h' header.

Variant SessionItem::data_internal(int role) const
{
    return p_impl->m_data->data(role);
}

void SessionItem::setParent(SessionItem* parent)
{
    p_impl->m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    if (p_impl->m_model)
        p_impl->m_model->unregisterFromPool(this);

    p_impl->m_model = model;

    if (p_impl->m_model)
        p_impl->m_model->registerInPool(this);

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

    // By setting data with internal method we are bypassing the model, and so undo/redo.
    // So current convention is to not invoke undo when changing appearance properties.
    // Shall we change it?
    p_impl->do_setData(flags, ItemDataRole::APPEARANCE);
}

//! Returns item mapper. Allows subscribing to various events happening to the item.

ItemMapper* SessionItem::mapper()
{
    if (!p_impl->m_mapper)
        p_impl->m_mapper = std::make_unique<ItemMapper>(this);
    return p_impl->m_mapper.get();
}

void SessionItem::setDataAndTags(std::unique_ptr<SessionItemData> data,
                                 std::unique_ptr<SessionItemTags> tags)
{
    p_impl->m_data = std::move(data);
    p_impl->m_tags = std::move(tags);
}
