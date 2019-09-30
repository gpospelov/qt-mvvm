// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SESSIONITEM_H
#define MVVM_SESSIONITEM_H

#include "mvvm_export.h"
#include "mvvm_types.h"
#include <QVariant>
#include <memory>
#include <vector>

namespace ModelView
{

class SessionModel;
class SessionItemPrivate;
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
    void setDisplayName(const std::string& name);

    std::string identifier() const;

    bool setData(const QVariant& variant, int role = ItemDataRole::DATA);
    bool setDataIntern(const QVariant& variant, int role);

    QVariant data(int role = ItemDataRole::DATA) const;

    SessionModel* model() const;

    SessionItem* parent() const;

    int childrenCount() const;

    bool insertItem(SessionItem* item, const std::string& tag = {}, int row = -1);

    SessionItem* takeItem(const std::string& tag, int row);

    std::vector<SessionItem*> children() const;

    std::vector<int> roles() const;

    // tags
    std::string defaultTag() const;
    void setDefaultTag(const std::string& tag);

    void registerTag(const TagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name);

    // access tagged items
    int itemCount(const std::string& tag = {}) const;
    SessionItem* getItem(const std::string& tag = {}, int row = 0) const;
    std::vector<SessionItem*> getItems(const std::string& tag = {}) const;
    template <typename T> T& item(const std::string& tag) const;
    template <typename T> std::vector<T*> items(const std::string& tag) const;
    std::string tagFromItem(const SessionItem* item) const;
    std::pair<std::string, int> tagRowOfItem(const SessionItem* item) const;

    ItemMapper* mapper();

    bool isEditable() const;
    void setEditable(bool value);

    bool isEnabled() const;
    void setEnabled(bool value);

    bool isSinglePropertyTag(const std::string& tag) const;

    QVariant property(const std::string& tag) const;

    void setProperty(const std::string& tag, const QVariant& variant);

private:
    friend class SessionModel;
    friend class JsonItemConverter;
    virtual void activate(){}
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void setAppearanceFlag(int flag, bool value);

    std::unique_ptr<SessionItemPrivate> p_impl;
};

//! Returns first item under given tag casted to specified type.

template <typename T> T& SessionItem::item(const std::string& tag) const
{
    T* tag_item = dynamic_cast<T*>(getItem(tag));
    if (!tag_item)
        throw std::runtime_error("Can't cast an item to given type");

    return *tag_item;
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

#endif // MVVM_SESSIONITEM_H

