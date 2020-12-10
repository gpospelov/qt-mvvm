// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/core/uniqueidgenerator.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/signals/modelmapper.h>
#include <stdexcept>

using namespace ModelView;

namespace
{
int appearance(const ModelView::SessionItem& item)
{
    const int default_appearance = Appearance::EDITABLE | Appearance::ENABLED;
    return item.hasData(ItemDataRole::APPEARANCE) ? item.data<int>(ItemDataRole::APPEARANCE)
                                                  : default_appearance;
}
} // namespace

struct SessionItem::SessionItemImpl {
    SessionItem* m_this_item{nullptr};
    SessionItem* m_parent{nullptr};
    SessionModel* m_model{nullptr};
    std::unique_ptr<ItemMapper> m_mapper;
    std::unique_ptr<SessionItemData> m_data;
    std::unique_ptr<SessionItemTags> m_tags;
    model_type m_modelType;

    SessionItemImpl(SessionItem* this_item)
        : m_this_item(this_item)
        , m_data(std::make_unique<SessionItemData>())
        , m_tags(std::make_unique<SessionItemTags>())
    {
    }

    //! Sets the data for given role, notifies the model.
    bool setData(const Variant& variant, int role)
    {
        bool result = m_data->setData(variant, role);
        if (result && m_model)
            m_model->mapper()->callOnDataChange(m_this_item, role);
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
        p_impl->m_model->unregister_item(this);
}

model_type SessionItem::modelType() const
{
    return p_impl->m_modelType;
}

std::string SessionItem::displayName() const
{
    return data<std::string>(ItemDataRole::DISPLAY);
}

SessionItem* SessionItem::setDisplayName(const std::string& name)
{
    setData(name, ItemDataRole::DISPLAY);
    return this;
}

std::string SessionItem::identifier() const
{
    return data<std::string>(ItemDataRole::IDENTIFIER);
}

//! Returns true if item has data on board with given role.

bool SessionItem::hasData(int role) const
{
    return p_impl->m_data->hasData(role);
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

//! Insert item into given tag under the given row.

bool SessionItem::insertItem(SessionItem* item, const TagRow& tagrow)
{
    // think of passing unique_ptr directly

    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    if (item->model())
        throw std::runtime_error("SessionItem::insertItem() -> Existing model.");

    auto result = p_impl->m_tags->insertItem(item, tagrow);
    if (result) {
        item->setParent(this);
        item->setModel(model());

        if (p_impl->m_model) {
            // FIXME think of actual_tagrow removal if input tag,row will be always valid
            auto actual_tagrow = tagRowOfItem(item);
            p_impl->m_model->mapper()->callOnItemInserted(this, actual_tagrow);
        }
    }

    return result;
}

//! Removes item from given row from given tag, returns it to the caller.

SessionItem* SessionItem::takeItem(const TagRow& tagrow)
{
    if (!p_impl->m_tags->canTakeItem(tagrow))
        return nullptr;

    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemAboutToBeRemoved(this, tagrow);

    auto result = p_impl->m_tags->takeItem(tagrow);
    result->setParent(nullptr);
    result->setModel(nullptr);
    // FIXME remaining problem is that ItemMapper still looking to the model
    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemRemoved(this, tagrow);

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

bool SessionItem::isTag(const std::string& name) const
{
    return p_impl->m_tags->isTag(name);
}

//! Returns tag of this item under which it is accessible for its parent.

std::string SessionItem::tag() const
{
    return tagRow().tag;
}

//! Returns TagRow of this item under which it is accessible for its parent.

TagRow SessionItem::tagRow() const
{
    return parent() ? parent()->tagRowOfItem(this) : TagRow();
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

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
    return p_impl->m_tags->getItems(tag);
}

//! Returns tag corresponding to given item.
//! Returns "" if item doesn't belong to children.

std::string SessionItem::tagOfItem(const SessionItem* item) const
{
    return tagRowOfItem(item).tag;
}

//! Returns pair of tag and row corresponding to given item.
//! Returns {"", -1} if item doesn't belong to children.

TagRow SessionItem::tagRowOfItem(const SessionItem* item) const
{
    return p_impl->m_tags->tagRowOfItem(item);
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

SessionItem* SessionItem::setEditable(bool value)
{
    setAppearanceFlag(Appearance::EDITABLE, value);
    return this;
}

bool SessionItem::isEnabled() const
{
    return appearance(*this) & Appearance::ENABLED;
}

SessionItem* SessionItem::setEnabled(bool value)
{
    setAppearanceFlag(Appearance::ENABLED, value);
    return this;
}

//! Returns item's tooltip.

std::string SessionItem::toolTip() const
{
    return hasData(ItemDataRole::TOOLTIP) ? data<std::string>(ItemDataRole::TOOLTIP)
                                          : std::string();
}

//! Sets item tooltip.

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

//! Sets editor type. Allows creating custom editors in the cells of Qt trees and tables.

SessionItem* SessionItem::setEditorType(const std::string& editor_type)
{
    setData(editor_type, ItemDataRole::EDITORTYPE);
    return this;
}

//! Returns true if given tag is related to single property tags.

bool SessionItem::isSinglePropertyTag(const std::string& tag) const
{
    return p_impl->m_tags->isSinglePropertyTag(tag);
}

//! Sets the data for given role.
//! Method invented to hide implementaiton details.

bool SessionItem::set_data_internal(Variant value, int role)
{
    return model() ? model()->setData(this, value, role) : setDataIntern(value, role);
}

//! Returns data for given role. Method invented to hide implementaiton details.

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

    // By setting data with internal method we are bypassing the model, and so undo/redo.
    // So current convention is to not invoke undo when changing appearance properties.
    // Shall we change it?
    setDataIntern(flags, ItemDataRole::APPEARANCE);
}

const SessionItemData* SessionItem::itemData() const
{
    return p_impl->m_data.get();
}

SessionItemData* SessionItem::itemData()
{
    return p_impl->m_data.get();
}

SessionItemTags* SessionItem::itemTags() const
{
    return p_impl->m_tags.get();
}

void SessionItem::setDataAndTags(std::unique_ptr<SessionItemData> data,
                                 std::unique_ptr<SessionItemTags> tags)
{
    p_impl->m_data = std::move(data);
    p_impl->m_tags = std::move(tags);
}

bool SessionItem::setDataIntern(const Variant& variant, int role)
{
    return p_impl->setData(variant, role);
}
