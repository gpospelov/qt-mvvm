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

#include <QVariant>
#include <memory>
#include <mvvm/core/export.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/tagrow.h>
#include <type_traits>
#include <vector>

namespace ModelView
{

class SessionModel;
class TagInfo;
class ItemMapper;

class CORE_EXPORT SessionItem
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

    bool setData(const QVariant& variant, int role = ItemDataRole::DATA);
    bool setDataIntern(const QVariant& variant, int role);

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

    // access tagged items
    int itemCount(const std::string& tag) const;
    SessionItem* getItem(const std::string& tag, int row = 0) const; // FIXME TagRow?
    std::vector<SessionItem*> getItems(const std::string& tag) const;
    template <typename T> T* item(const std::string& tag) const;
    template <typename T> std::vector<T*> items(const std::string& tag) const;
    std::string tagOfItem(const SessionItem* item) const;
    TagRow tagRowOfItem(const SessionItem* item) const;

    ItemMapper* mapper();

    bool isEditable() const;
    void setEditable(bool value);

    bool isEnabled() const;
    void setEnabled(bool value);

    bool isSinglePropertyTag(const std::string& tag) const;

    template <typename T> T property(const std::string& tag) const;

    template <typename T> void setProperty(const std::string& tag, const T& value);

    void setProperty(const std::string& tag, const char* value);

private:
    friend class SessionModel;
    friend class JsonItemConverter;
    virtual void activate() {}
    QVariant data_internal(int role) const;
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void setAppearanceFlag(int flag, bool value);

    // FIXME refactor converter access to item internals
    class SessionItemData* itemData() const;
    class SessionItemTags* itemTags() const;
    void setDataAndTags(std::unique_ptr<SessionItemData> data,
                        std::unique_ptr<SessionItemTags> tags);

    struct SessionItemImpl;
    std::unique_ptr<SessionItemImpl> p_impl;
};

//! Returns data of given type T for given role.

template <typename T> inline T SessionItem::data(int role) const
{
    if constexpr (std::is_same<T, QVariant>::value)
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
    getItem(tag)->setData(QVariant::fromValue(value));
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

template <typename T = SessionItem> std::vector<T*> SessionItem::items(const std::string& tag) const
{
    std::vector<T*> result;
    for (auto item : getItems(tag))
        if (auto casted = dynamic_cast<T*>(item); casted)
            result.push_back(casted);

    return result;
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEM_H
