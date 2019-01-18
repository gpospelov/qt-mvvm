// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitem.h"
#include "sessionmodel.h"
#include "itemmanager.h"
#include "itempool.h"
#include "itemutils.h"
#include "customvariants.h"
#include "sessionitemdata.h"
#include "sessionitemtags.h"
#include <stdexcept>
#include <iterator>
#include <cassert>

namespace {
    const std::string default_tag_name = "defaultTag";
}

using namespace ModelView;

SessionItem::SessionItem(model_type modelType)
    : m_parent(nullptr)
    , m_model(nullptr)
    , m_data(new SessionItemData)
    , m_tags(new SessionItemTags)
    , m_modelType(std::move(modelType))
{
    registerTag(TagInfo::universalTag(default_tag_name));
    setDefaultTag(default_tag_name);
}

SessionItem::~SessionItem()
{
    for (auto item : m_children)
        delete item;
    m_children.clear();

    if (m_parent)
        m_parent->childDeleted(this);

    if (auto pool = m_item_pool.lock())
        pool->deregister_item(this);
}

model_type SessionItem::modelType() const
{
    return m_modelType;
}

bool SessionItem::setData(const QVariant& variant, int role)
{
    if (m_model)
        return m_model->setData(this, variant, role); // to use undo/redo
    else
        return setDataIntern(variant, role);
}

QVariant SessionItem::data(int role) const
{
    return m_data->data(role);
}

SessionModel* SessionItem::model() const
{
    return m_model;
}

SessionItem* SessionItem::parent() const
{
    return m_parent;
}

int SessionItem::childrenCount() const
{
    return static_cast<int>(m_children.size());
}

//! Insert item into given tag into given row.

bool SessionItem::insertItem(int row, SessionItem* item, const std::string& tag)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    auto tagName = ensure(tag, item->modelType());

    int index = m_tags->insertIndexFromTagRow(tagName, row);
    if (index < 0)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid row, maximum reached.");

    item->setParent(this);
    item->setModel(model());
    m_children.insert(std::next(m_children.begin(), index), item);
    m_tags->addChild(tagName);

    return true;
}

//! Remove item from given row from given tag.

SessionItem* SessionItem::takeItem(int row, const std::string& tag)
{
    SessionItem* result(nullptr);
    auto tagName = ensure(tag);
    int index = m_tags->indexFromTagRow(tagName, row);

        result = childAt(index);
        m_children.erase(m_children.begin() + index);
        m_tags->removeChild(tagName);
        if (result) {
            result->setParent(nullptr);
            result->setModel(nullptr);
        }
    return result;
}

std::vector<SessionItem*> SessionItem::children() const
{
    return m_children;
}

SessionItem* SessionItem::childAt(int row) const
{
    return row >= 0 && row < childrenCount() ? m_children[static_cast<size_t>(row)] : nullptr;
}

int SessionItem::rowOfChild(SessionItem* child) const
{
    auto pos = find(m_children.begin(), m_children.end(), child);
    return pos == m_children.end() ? -1 : static_cast<int>(std::distance(m_children.begin(), pos));
}

void SessionItem::register_item(std::shared_ptr<ItemPool> item_pool)
{
    m_item_pool = item_pool;

    if (auto pool = m_item_pool.lock()) {
        auto key = pool->register_item(this);
        setDataIntern(QVariant::fromValue(key), ItemDataRole::IDENTIFIER);
    }
}

std::vector<int> SessionItem::roles() const
{
    return m_data->roles();
}

std::string SessionItem::defaultTag() const
{
    return m_default_tag;
}

void SessionItem::setDefaultTag(const std::string& tag)
{
    m_default_tag = tag;
}

void SessionItem::registerTag(const TagInfo& tagInfo)
{
    m_tags->registerTag(tagInfo);
}

bool SessionItem::isTag(const std::string& name)
{
    return m_tags->isValid(name);
}

//! Returns item in given row of given tag.

SessionItem* SessionItem::getItem(const std::string& tag, int row) const
{
    int index = m_tags->indexFromTagRow(ensure(tag), row);
    return m_children[static_cast<size_t>(index)];
}

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
    auto tagName = ensure(tag);
    int startIndex = m_tags->tagStartIndex(tagName);
    int endIndex = startIndex + m_tags->childCount(tagName);
    std::vector<SessionItem*> result;
    std::copy(m_children.begin()+startIndex, m_children.begin()+endIndex,
               std::back_inserter(result));
    return result;
}

void SessionItem::setParent(SessionItem* parent)
{
    m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    m_model = model;

    for (auto child : m_children)
        child->setModel(model);
}

void SessionItem::childDeleted(SessionItem* child)
{
    auto index = rowOfChild(child);
    assert(index != -1);
    m_children[static_cast<size_t>(index)] = nullptr;
}

//! Check if tag name is registered and returns it back. If tag is empty, returns defaultTag.

std::string SessionItem::ensure(const std::string& tag, const std::string& model_type) const
{
    const std::string result = tag.empty() ? defaultTag() : tag;

    if (!m_tags->isValid(result, model_type))
        throw std::runtime_error("SessionItem::ensure() -> Non existing tag");

    return result;
}

bool SessionItem::setDataIntern(const QVariant& variant, int role)
{
    if (!Utils::CompatibleVariantTypes(data(role), variant))
        throw std::runtime_error("SessionItem::setDataIntern() -> Error. Variant types mismatch");

    return m_data->setData(variant, role);
}
