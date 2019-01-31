// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitem.h"
#include "customvariants.h"
#include "itemmanager.h"
#include "itemmapper.h"
#include "itempool.h"
#include "itemutils.h"
#include "sessionitemdata.h"
#include "sessionitemtags.h"
#include "sessionmodel.h"
#include "modelmapper.h"
#include <cassert>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace
{
const std::string default_tag_name = "defaultTag";
}

using namespace ModelView;

SessionItem::SessionItem(model_type modelType)
    : m_parent(nullptr), m_model(nullptr), m_data(new SessionItemData), m_tags(new SessionItemTags),
      m_modelType(std::move(modelType))
{
    setDataIntern(QVariant::fromValue(ItemPool::generate_key()), ItemDataRole::IDENTIFIER);
}

SessionItem::~SessionItem()
{
    if (m_mapper)
        m_mapper->callOnItemDestroy();

    for (auto item : m_children)
        delete item;
    m_children.clear();

    if (m_parent)
        m_parent->childDeleted(this);

    if (m_model)
        m_model->make_registered(this, false);
}

model_type SessionItem::modelType() const
{
    return m_modelType;
}

std::string SessionItem::displayName() const
{
    return data(ItemDataRole::DISPLAY).value<std::string>();
}

void SessionItem::setDisplayName(const std::string& name)
{
    setData(QVariant::fromValue(name), ItemDataRole::DISPLAY);
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

    if(m_model)
        m_model->mapper()->callOnRowInserted(this, index);

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

//! Returns child at given index of children array. No tags involved.

SessionItem* SessionItem::childAt(int index) const
{
    return index >= 0 && index < childrenCount() ? m_children[static_cast<size_t>(index)] : nullptr;
}

//! Returns index in children array corresponding to given child. No tags involved.

int SessionItem::indexOfChild(SessionItem* child) const
{
    auto pos = find(m_children.begin(), m_children.end(), child);
    return pos == m_children.end() ? -1 : static_cast<int>(std::distance(m_children.begin(), pos));
}

std::vector<int> SessionItem::roles() const
{
    return m_data->roles();
}

std::string SessionItem::defaultTag() const
{
    return data(ItemDataRole::DEFAULT_TAG).value<std::string>();
}

void SessionItem::setDefaultTag(const std::string& tag)
{
    setDataIntern(QVariant::fromValue(tag), ItemDataRole::DEFAULT_TAG);
}

void SessionItem::registerTag(const TagInfo& tagInfo, bool set_as_default)
{
    m_tags->registerTag(tagInfo);
    if (set_as_default)
        setDefaultTag(tagInfo.name());
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
    std::copy(m_children.begin() + startIndex, m_children.begin() + endIndex,
              std::back_inserter(result));
    return result;
}

std::string SessionItem::tagFromItem(const SessionItem* item) const
{
    auto it = std::find(m_children.begin(), m_children.end(), item);
    if (it != m_children.end()) {
        int index = static_cast<int>(std::distance(m_children.begin(), it));
        return m_tags->tagFromIndex(index);
    }

    return {};
}

ItemMapper* SessionItem::mapper()
{
    if (!m_mapper)
        m_mapper = std::make_unique<ItemMapper>(this);
    return m_mapper.get();
}

void SessionItem::setParent(SessionItem* parent)
{
    m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    if (m_model) {
        m_model->make_registered(this, false);
    }

    m_model = model;

    if (m_model) {
        m_model->make_registered(this, true);
    }

    for (auto child : m_children)
        child->setModel(model);
}

void SessionItem::childDeleted(SessionItem* child)
{
    auto index = indexOfChild(child);
    assert(index != -1);
    m_children[static_cast<size_t>(index)] = nullptr;
}

//! Check if tag name is registered and returns it back. If tag is empty, returns defaultTag.

std::string SessionItem::ensure(const std::string& tag, const std::string& model_type) const
{
    const std::string result = tag.empty() ? defaultTag() : tag;

    if (!m_tags->isValid(result, model_type)) {
        std::ostringstream ostr;
        ostr << "SessionItem::ensure() -> Invalid tag '" << tag
             << "' for model '" << model_type << "', "
             << "defaultTag:'"<< defaultTag() << "', available tags:\n";
        for(const auto& tag : *m_tags)
            ostr << tag.toString() << "\n";

        throw std::runtime_error(ostr.str());
    }

    return result;
}

bool SessionItem::setDataIntern(const QVariant& variant, int role)
{
    // FIXME remove temporary check
    if (variant.typeName() == QStringLiteral("QString"))
        throw std::runtime_error("Attempt to set QString based variant");

    if (!Utils::CompatibleVariantTypes(data(role), variant)) {
        std::ostringstream ostr;
        ostr << "SessionItem::setDataIntern() -> Error. Variant types mismatch. "
             << "Old variant type '" << data(role).typeName() << "' "
             << "new variant type '" << variant.typeName() << "\n";
        throw std::runtime_error(ostr.str());
    }

    bool result = m_data->setData(variant, role);
    if (result && m_mapper)
        m_mapper->callOnDataChange(role);

    if(result && m_model)
        m_model->mapper()->callOnDataChange(this, role);

    return result;
}
