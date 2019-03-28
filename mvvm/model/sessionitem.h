// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include "global.h"
#include "model_types.h"
#include <QVariant>
#include <memory>
#include <vector>

namespace ModelView
{

class SessionModel;
class ItemPool;
class SessionItemData;
class TagInfo;
class ItemMapper;
class SessionItemTags;
class SessionItemPrivate;

class CORE_EXPORT SessionItem
{
    friend class SessionModel;
    friend class JsonModel;
    friend class JsonItem;

public:
    SessionItem(model_type modelType = Constants::BaseType);
    virtual ~SessionItem();

    model_type modelType() const;

    virtual std::string displayName() const;
    void setDisplayName(const std::string& name);

    std::string identifier() const;

    bool setData(const QVariant& variant, int role);
    bool setDataIntern(const QVariant& variant, int role);

    QVariant data(int role) const;

    SessionModel* model() const;

    SessionItem* parent() const;

    int childrenCount() const;

    SessionItem* childAt(int index) const;

    // FIXME revise return type usage
    bool insertItem(SessionItem* item, int row, const std::string& tag = {});

    SessionItem* takeItem(int row, const std::string& tag = {});

    std::vector<SessionItem*> children() const;

    int indexOfChild(SessionItem* child) const;

    std::vector<int> roles() const;

    // tags
    std::string defaultTag() const;
    void setDefaultTag(const std::string& tag);

    void registerTag(const TagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name);

    // access tagged items
    SessionItem* getItem(const std::string& tag = {}, int row = 0) const;
    std::vector<SessionItem*> getItems(const std::string& tag = {}) const;
    std::string tagFromItem(const SessionItem* item) const;
    std::pair<int, std::string> tagRowFromItem(const SessionItem* item) const;

    ItemMapper* mapper();

    virtual void activate();

    bool isEditable() const;
    void setEditable(bool value);

    bool isEnabled() const;
    void setEnabled(bool value);

private:
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void childDeleted(SessionItem* child);
    void setAppearanceFlag(int flag, bool value);

    std::unique_ptr<ItemMapper> m_mapper;
    std::unique_ptr<SessionItemData> m_data;
    std::unique_ptr<SessionItemTags> m_tags;
    model_type m_modelType;
    std::unique_ptr<SessionItemPrivate> m_p;
};

} // namespace ModelView

#endif
