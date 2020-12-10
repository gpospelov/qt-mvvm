// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONITEM_H
#define MVVM_MODEL_SESSIONITEM_H

#include <memory>
#include <mvvm/core/variant.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/model_export.h>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace ModelView
{

class SessionModel;
class TagInfo;
class ItemMapper;
class SessionItemData;

class MVVM_MODEL_EXPORT SessionItem
{
public:
    explicit SessionItem(model_type modelType = Constants::BaseType);
    virtual ~SessionItem();
    SessionItem(const SessionItem&) = delete;
    SessionItem& operator=(const SessionItem&) = delete;

    model_type modelType() const;

    virtual std::string displayName() const;
    virtual SessionItem* setDisplayName(const std::string& name);

    std::string identifier() const;

    template <typename T> bool setData(const T& value, int role = ItemDataRole::DATA);
    bool setDataIntern(const Variant& variant, int role);

    bool hasData(int role = ItemDataRole::DATA) const;

    template <typename T> T data(int role = ItemDataRole::DATA) const;

    SessionModel* model() const;

    SessionItem* parent() const;

    int childrenCount() const;

    bool insertItem(SessionItem* item, const TagRow& tagrow);

    SessionItem* takeItem(const TagRow& tagrow);

    std::vector<SessionItem*> children() const;

    std::vector<int> roles() const;

    // tags
    std::string defaultTag() const;
    void setDefaultTag(const std::string& tag);

    void registerTag(const TagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string tag() const;

    TagRow tagRow() const;

    // access tagged items
    int itemCount(const std::string& tag) const;
    SessionItem* getItem(const std::string& tag, int row = 0) const; // FIXME TagRow?
    std::vector<SessionItem*> getItems(const std::string& tag) const;
    template <typename T> T* item(const std::string& tag) const;
    template <typename T = SessionItem> std::vector<T*> items(const std::string& tag) const;
    std::string tagOfItem(const SessionItem* item) const;
    TagRow tagRowOfItem(const SessionItem* item) const;

    ItemMapper* mapper();

    bool isEditable() const;
    SessionItem* setEditable(bool value);

    bool isEnabled() const;
    SessionItem* setEnabled(bool value);

    std::string toolTip() const;
    SessionItem* setToolTip(const std::string& tooltip);

    std::string editorType() const;
    SessionItem* setEditorType(const std::string& editor_type);

    bool isSinglePropertyTag(const std::string& tag) const;

    template <typename T> T property(const std::string& tag) const;

    template <typename T> void setProperty(const std::string& tag, const T& value);

    void setProperty(const std::string& tag, const char* value);

    // FIXME refactor converter access to item internals
    SessionItemData* itemData();
    const SessionItemData* itemData() const;

private:
    friend class SessionModel;
    friend class JsonItemConverter;
    virtual void activate() {}
    bool set_data_internal(Variant value, int role);
    Variant data_internal(int role) const;
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void setAppearanceFlag(int flag, bool value);

    class SessionItemTags* itemTags() const;
    void setDataAndTags(std::unique_ptr<SessionItemData> data,
                        std::unique_ptr<SessionItemTags> tags);

    struct SessionItemImpl;
    std::unique_ptr<SessionItemImpl> p_impl;
};

//! Sets data for given role.

template <typename T> inline bool SessionItem::setData(const T& value, int role)
{
    if constexpr (std::is_same<T, Variant>::value)
        return set_data_internal(value, role);
    return set_data_internal(Variant::fromValue(value), role);
}

//! Returns data of given type T for given role.

template <typename T> inline T SessionItem::data(int role) const
{
    if constexpr (std::is_same<T, Variant>::value)
        return data_internal(role);
    return data_internal(role).value<T>();
}

//! Returns data stored in property item.
//! Property is single item registered under certain tag via CompoundItem::addProperty method.

template <typename T> inline T SessionItem::property(const std::string& tag) const
{
    return getItem(tag)->data<T>();
}

//! Sets value to property item.
//! Property is single item registered under certain tag via CompoundItem::addProperty method, the
//! value will be assigned to it's data role.

template <typename T> inline void SessionItem::setProperty(const std::string& tag, const T& value)
{
    getItem(tag)->setData(value);
}

//! Sets value to property item (specialized for special "const char *" case).
//! Property is single item registered under certain tag via CompoundItem::addProperty method, the
//! value will be assigned to it's data role.

inline void SessionItem::setProperty(const std::string& tag, const char* value)
{
    setProperty(tag, std::string(value));
}

//! Returns first item under given tag casted to a specified type.
//! Returns nullptr, if item doesn't exist. If item exists but can't be casted will throw.

template <typename T> inline T* SessionItem::item(const std::string& tag) const
{
    if (auto item = getItem(tag); item) {
        T* tag_item = dynamic_cast<T*>(item);
        if (!tag_item)
            throw std::runtime_error("Can't cast an item to given type");
        return tag_item;
    }

    return nullptr;
}

//! Returns all items under given tag casted to specific type.

template <typename T> std::vector<T*> SessionItem::items(const std::string& tag) const
{
    std::vector<T*> result;
    for (auto item : getItems(tag))
        if (auto casted = dynamic_cast<T*>(item); casted)
            result.push_back(casted);

    return result;
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEM_H
