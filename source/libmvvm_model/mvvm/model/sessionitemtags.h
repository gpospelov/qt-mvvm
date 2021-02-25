// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONITEMTAGS_H
#define MVVM_MODEL_SESSIONITEMTAGS_H

#include "mvvm/model/tagrow.h"
#include "mvvm/model_export.h"
#include <string>
#include <vector>

namespace ModelView {

class SessionItemContainer;
class TagInfo;
class SessionItem;

//! Collection of SessionItem's containers according to their tags.

class MVVM_MODEL_EXPORT SessionItemTags {
public:
    using container_t = std::vector<SessionItemContainer*>;
    using const_iterator = container_t::const_iterator;

    SessionItemTags();
    ~SessionItemTags();
    SessionItemTags(const SessionItemTags&) = delete;
    SessionItemTags& operator=(const SessionItemTags&) = delete;

    // tag

    void registerTag(const TagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string defaultTag() const;

    void setDefaultTag(const std::string& name);

    int itemCount(const std::string& tag_name) const;

    // adding and removal

    bool canInsertItem(const SessionItem *item, const TagRow& tagrow) const;

    bool insertItem(SessionItem* item, const TagRow& tagrow);

    bool canTakeItem(const TagRow& tagrow) const;

    SessionItem* takeItem(const TagRow& tagrow);

    // item access
    SessionItem* getItem(const TagRow& tagrow) const;

    std::vector<SessionItem*> getItems(const std::string& tag = {}) const;

    std::vector<SessionItem*> allitems() const;

    TagRow tagRowOfItem(const SessionItem* item) const;

    const_iterator begin() const;
    const_iterator end() const;

    bool isSinglePropertyTag(const std::string& tag) const;

    int tagsCount() const;

    SessionItemContainer& at(int index);

private:
    SessionItemContainer* container(const std::string& tag_name) const;
    SessionItemContainer* find_container(const std::string& tag_name) const;
    std::vector<SessionItemContainer*> m_containers;
    std::string m_default_tag;
};

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEMTAGS_H
