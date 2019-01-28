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
#include <vector>
#include <memory>

namespace ModelView {

class SessionModel;
class ItemPool;
class SessionItemData;
class SessionItemTags;
class TagInfo;

class CORE_EXPORT SessionItem {
    friend class SessionModel;
    friend class JsonModel;
    friend class JsonItem;
public:
    SessionItem(model_type modelType = {});
    virtual ~SessionItem();

    model_type modelType() const;

    std::string displayName() const;
    void setDisplayName(const std::string& name);

    bool setData(const QVariant& variant, int role);
    bool setDataIntern(const QVariant& variant, int role);

    QVariant data(int role) const;

    SessionModel* model() const;

    SessionItem* parent() const;

    int childrenCount() const;

    bool insertItem(int row, SessionItem* item, const std::string& tag = {});

    SessionItem* takeItem(int row, const std::string& tag = {});

    std::vector<SessionItem*> children() const;

    SessionItem* childAt(int row) const;

    int rowOfChild(SessionItem* child) const;

    std::vector<int> roles() const;

    // tags
    std::string defaultTag() const;
    void setDefaultTag(const std::string& tag);

    void registerTag(const TagInfo& tagInfo, bool set_as_default=false);

    bool isTag(const std::string& name);

    // access tagged items
    SessionItem* getItem(const std::string& tag = {}, int row = 0) const;
    std::vector<SessionItem*> getItems(const std::string& tag = {}) const;
    std::string tagFromItem(const SessionItem* item) const;

private:
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void childDeleted(SessionItem* child);
    std::string ensure(const std::string& tag, const std::string& model_type={}) const;

    SessionItem* m_parent;
    SessionModel* m_model;
    std::vector<SessionItem*> m_children;
    std::unique_ptr<SessionItemData> m_data;
    std::unique_ptr<SessionItemTags> m_tags;
    model_type m_modelType;
};

}  // namespace ModelView

#endif
