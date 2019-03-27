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
#include "obsoletesessionitemtags.h"
#include "sessionmodel.h"
#include "modelmapper.h"
#include "sessionitemtags.h"
#include <cassert>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace
{
const std::string default_tag_name = "defaultTag";
int appearance(const ModelView::SessionItem& item)
{
    auto value = item.data(ModelView::ItemDataRole::APPEARANCE);
    return value.isValid() ? value.toInt() : ModelView::Appearance::EDITABLE | ModelView::Appearance::ENABLED;
}
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

//    auto container = children();
//    for (auto item : container)
//        delete item;
////    m_children.clear();

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

std::string SessionItem::identifier() const
{
    return data(ItemDataRole::IDENTIFIER).value<std::string>();
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
    auto container = children();
    return static_cast<int>(container.size());
}

//! Returns child at given index of children array. No tags involved.

SessionItem* SessionItem::childAt(int index) const
{
    auto container = children();
    return index >= 0 && index < container.size() ? container[static_cast<size_t>(index)] : nullptr;
}

//! Insert item into given tag into given row.

bool SessionItem::insertItem(SessionItem* item, int row, const std::string& tag)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

//    auto tagName = ensure(tag, item->modelType());

//    int index = m_obsolete_tags->insertIndexFromTagRow(tagName, row);
//    if (index < 0) {
//        std::ostringstream ostr;
//        ostr << "SessionItem::insertItem() -> Invalid row, maximum reached. "
//             << "tagName:'"<<tagName<<"', row: " << row << "\n"
//             << m_obsolete_tags->tagInfo(tagName).toString();
//        throw std::runtime_error(ostr.str());
//    }

//    item->setParent(this);
//    item->setModel(model());
//    m_children.insert(std::next(m_children.begin(), index), item);
//    m_obsolete_tags->addChild(tagName);

//    if(m_model)
//        m_model->mapper()->callOnRowInserted(this, index);

    auto result = m_tags->insertItem(item, row, tag);
    if (result) {
        item->setParent(this);
        item->setModel(model());

        if(m_model)
            m_model->mapper()->callOnRowInserted(this, indexOfChild(item));
    }

    return result;
}

//! Removes item from given row from given tag, returns it to the caller.

SessionItem* SessionItem::takeItem(int row, const std::string& tag)
{
    SessionItem* result(nullptr);
//    auto tagName = ensure(tag);
//    int index = m_obsolete_tags->indexFromTagRow(tagName, row);

//    result = childAt(index);
//    m_children.erase(m_children.begin() + index);
//    m_obsolete_tags->removeChild(tagName);
//    if (result) {
//        result->setParent(nullptr);
//        result->setModel(nullptr);
//    }

//    if (m_model) {
//        // FIXME remove one of methods
//        m_model->mapper()->callOnRowRemoved(this, index);
//        m_model->mapper()->callOnRowRemoved2(this, index, result->identifier());
//    }

    result = m_tags->takeItem(row, tag);
    if (result) {
        result->setParent(nullptr);
        result->setModel(nullptr);
    }

    if (m_model) {
        // FIXME remove one of methods
        m_model->mapper()->callOnRowRemoved(this, indexOfChild(result));
        m_model->mapper()->callOnRowRemoved2(this, indexOfChild(result), result->identifier());
    }

    return result;
}

std::vector<SessionItem*> SessionItem::children() const
{
    return m_tags->allitems();
//    return m_children;
}

//! Returns index in children array corresponding to given child. No tags involved.

int SessionItem::indexOfChild(SessionItem* child) const
{
    auto container = children();
    auto pos = find(container.begin(), container.end(), child);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}

std::vector<int> SessionItem::roles() const
{
    return m_data->roles();
}

std::string SessionItem::defaultTag() const
{
    return m_tags->defaultTag();
//    return data(ItemDataRole::DEFAULT_TAG).value<std::string>();
}

void SessionItem::setDefaultTag(const std::string& tag)
{
    setDataIntern(QVariant::fromValue(tag), ItemDataRole::DEFAULT_TAG);
    m_tags->setDefaultTag(tag);
}

void SessionItem::registerTag(const TagInfo& tagInfo, bool set_as_default)
{
    m_tags->registerTag(tagInfo, set_as_default);

//    m_obsolete_tags->registerTag(tagInfo);
//    if (set_as_default)
//        setDefaultTag(tagInfo.name());
}

bool SessionItem::isTag(const std::string& name)
{
    return m_tags->isTag(name);
//    return m_obsolete_tags->isValid(name);
}

//! Returns item in given row of given tag.

SessionItem* SessionItem::getItem(const std::string& tag, int row) const
{
//    int index = m_obsolete_tags->indexFromTagRow(ensure(tag), row);
//    auto container = children();
//    return container[static_cast<size_t>(index)];
    return m_tags->getItem(tag, row);
}

std::vector<SessionItem*> SessionItem::getItems(const std::string& tag) const
{
//    auto tagName = ensure(tag);
//    int startIndex = m_obsolete_tags->tagStartIndex(tagName);
//    int endIndex = startIndex + m_obsolete_tags->childCount(tagName);
//    std::vector<SessionItem*> result;
//    auto container = children();
//    std::copy(container.begin() + startIndex, container.begin() + endIndex,
//              std::back_inserter(result));
//    return result;
    return m_tags->getItems(tag);
}

std::string SessionItem::tagFromItem(const SessionItem* item) const
{
//    auto container = children();
//    auto it = std::find(container.begin(), container.end(), item);
//    if (it != container.end()) {
//        int index = static_cast<int>(std::distance(container.begin(), it));
//        return m_obsolete_tags->tagFromIndex(index);
//    }
//    return {};
    return m_tags->tagIndexOfItem(item).first;
}

//! Returns item's row in its tag.

std::pair<int, std::string> SessionItem::tagRowFromItem(const SessionItem* item) const
{
//    auto container = children();

//    auto it = std::find(container.begin(), container.end(), item);
//    if (it != container.end()) {
//        int index = static_cast<int>(std::distance(container.begin(), it));
//        auto tag = m_obsolete_tags->tagFromIndex(index);
//        return std::make_pair(index - m_obsolete_tags->tagStartIndex(tag), tag);
//    }
//    return {-1, ""};
    auto temp = m_tags->tagIndexOfItem(item);
    return std::make_pair(temp.second, temp.first);
}

ItemMapper* SessionItem::mapper()
{
    if (!m_mapper)
        m_mapper = std::make_unique<ItemMapper>(this);
    return m_mapper.get();
}


//! Activates all buisiness logic of given item. Should be called after item constructions.
//! Intended for overload in child classes.

void SessionItem::activate() {}

bool SessionItem::isEditable() const
{
    return appearance(*this) & Appearance::EDITABLE;
}

void SessionItem::setEditable(bool value)
{
    setAppearanceFlag(Appearance::EDITABLE, value);
}

bool SessionItem::isEnabled() const
{
    return appearance(*this) & Appearance::ENABLED;
}

void SessionItem::setEnabled(bool value)
{
    setAppearanceFlag(Appearance::ENABLED, value);
}

void SessionItem::setParent(SessionItem* parent)
{
    m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    if (m_model) {
        // FIXME throw here if it is the case
        m_model->make_registered(this, false);
    }

    m_model = model;

    if (m_model) {
        m_model->make_registered(this, true);
    }

    // FIXME find better place for activate logic. ItemMapper ? make_registered ?
    if (m_model)
       activate(); // activate buisiness logic

    auto container = children();
    for (auto child : container)
        child->setModel(model);
}

void SessionItem::childDeleted(SessionItem* child)
{
    m_tags->itemDeleted(child);
//    auto index = indexOfChild(child);
//    assert(index != -1);
//    m_children[static_cast<size_t>(index)] = nullptr;
}

//! Check if tag name is registered and returns it back. If tag is empty, returns defaultTag.

//std::string SessionItem::ensure(const std::string& tag, const std::string& model_type) const
//{
//    const std::string result = tag.empty() ? defaultTag() : tag;

//    if (!m_obsolete_tags->isValid(result, model_type)) {
//        std::ostringstream ostr;
//        ostr << "SessionItem::ensure() -> Invalid tag '" << tag
//             << "' for model '" << model_type << "', "
//             << "defaultTag:'"<< defaultTag() << "', available tags:\n";
//        for(const auto& tag : *m_obsolete_tags)
//            ostr << tag.toString() << "\n";

//        throw std::runtime_error(ostr.str());
//    }

//    return result;
//}

void SessionItem::setAppearanceFlag(int flag, bool value)
{
    int flags = appearance(*this);
    if (value)
        flags |= flag;
    else
        flags &= ~flag;

    setDataIntern(flags, ItemDataRole::APPEARANCE);
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
    if(result && m_model)
        m_model->mapper()->callOnDataChange(this, role);

    return result;
}
