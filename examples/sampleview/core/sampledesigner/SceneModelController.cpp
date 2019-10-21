// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SceneModelController.h"
#include "ConnectableView.h"
#include "DesignerScene.h"
#include "NodeEditorConnection.h"
#include "SampleModel.h"
#include "SampleViewFactory.h"
#include "modelmapper.h"
#include "modelutils.h"
#include "sessionitem.h"
#include <set>

using namespace ModelView;

namespace {
//! Guard to block controller-model connection
class BlockGuard
{
public:
    BlockGuard(bool& block) : m_block(block)
    {
        if (block)
            throw std::runtime_error("Error in BlockMutex: already blocked.");
        m_block = true;
    }

    ~BlockGuard() { m_block = false; }

private:
    bool& m_block;
};

//! Wrapper for execution of an external command to the model.
class ModelCommandExecutor
{
public:
    ModelCommandExecutor(SceneModelController::ModelCommand& command, SessionModel* model)
        : m_command(command)
        , m_model(model)
    {}

    ~ModelCommandExecutor() { m_command = SceneModelController::ModelCommand(); }

    //! Returns true if the command was executed, false otherwise
    [[nodiscard]] bool execute() {
        if (!m_model || !m_command)
            return false;
        m_command(*m_model);
        return true;
    }

private:
    DesignerScene::ModelCommand& m_command;
    SessionModel* m_model;
};

// utilities for SceneModelController::onCopy

//! Returns the items haveing no parents among the items corresponding to the given view list.
std::set<const SessionItem*> topItems(const QList<QGraphicsItem*>& views);
//! Returns the old - new item correspondence table with children added.
std::map<const SessionItem*, SessionItem*>
addChildItems(const std::map<const SessionItem*, SessionItem*>& tab);
//! Finds and returns the items from look-up table having no correspondence in the given view list.
std::list<const SessionItem*> findUnselectedItems(const std::set<QGraphicsItem*>& views,
                                                  std::list<const SessionItem*> keys);

// utilities for SceneModelController::onDelete

//! Returns the set of passed views with their child IView instances appended
std::set<QGraphicsItem*> extendWithChildren(QList<QGraphicsItem*> views);
//! Finds all the views connected to the passed set
std::set<IView*> connectedViews(const std::set<QGraphicsItem*>& views, const DesignerScene& scene);
//! Finds all the views with no ancestor in the passed set
std::set<IView*> topViews(const QList<QGraphicsItem *> &views);

//! Small utility to retrieve keys from a map
template<class T, class U>
std::list<T> keys(const std::map<T, U> input);
}

SceneModelController::SceneModelController(DesignerScene& scene, SampleModel* model)
    : m_scene(scene)
    , m_model(model)
    , m_block(false)
{
    if (!m_model)
        throw std::runtime_error("Error in GraphicsObjectController: passed model is null.");

    m_model->mapper()->setOnModelReset([this](SessionModel*) { onModelChange(); }, this);
    m_model->mapper()->setOnModelDestroyed([this](SessionModel*) { onModelDestroyed(); }, this);
    m_model->mapper()->setOnRowInserted([this](SessionItem*, std::string, int) { onModelChange(); },
                                        this);
    m_model->mapper()->setOnRowRemoved([this](SessionItem*, std::string, int) { onModelChange(); },
                                       this);

    m_temp_model.clear();
}

SceneModelController::~SceneModelController()
{
    m_model->mapper()->unsubscribe(this);
}

void SceneModelController::copy(const QList<QGraphicsItem*>& views)
{
    if (!m_model)
        return;
    m_temp_model.clear();

    const std::set<const SessionItem*> top_items = topItems(views);

    std::map<const SessionItem*, SessionItem*> lookup_table;
    for (const SessionItem* item: top_items)
        lookup_table[item] = m_temp_model.copyItem(item, m_temp_model.rootItem());

    lookup_table = addChildItems(lookup_table);
    auto remove_keys = findUnselectedItems(extendWithChildren(views), keys(lookup_table));

    // first move all children of unselected items to root
    for (auto item: remove_keys)
        for (SessionItem* child: lookup_table[item]->children())
            if (SampleViewFactory::isValidType(child->modelType()))
                m_temp_model.moveItem(child, m_temp_model.rootItem(), {}, -1);

    // removing unselected items
    for (auto item: remove_keys)
        Utils::DeleteItemFromModel(lookup_table[item]);
}

void SceneModelController::paste()
{
    if (!m_model)
        return;
    BlockGuard signal_guard(m_block);

    const auto to_copy = Utils::TopItems(&m_temp_model);
    for (SessionItem* item: to_copy)
        m_model->copyItem(item, m_model->rootItem());

    m_scene.onModelChanged();
}

void SceneModelController::remove(const QList<QGraphicsItem *>& views)
{
    if (!m_model)
        return;
    BlockGuard signal_guard(m_block);

    // Append children of the selected views (e.g. layers of a multilayer)
    // It is required for proper disconnection
    const auto all_views = extendWithChildren(views);

    // Disconnect dependent items
    const auto connected_views = connectedViews(all_views, m_scene);
    for (auto view: connected_views)
        m_model->moveItem(view->getItem(), m_model->rootItem(), {}, -1);

    // find top-level items. Children will be deleted automatically
    const auto top_views = topViews(views);
    for (auto view: top_views)
        Utils::DeleteItemFromModel(view->getItem());

    m_scene.onModelChanged();
}

void SceneModelController::onConnect(NodeEditorConnection *connection)
{
    if (!m_model)
        return;
    BlockGuard signal_guard(m_block);

    ConnectableView* parentView = connection->getParentView();
    ConnectableView* childView = connection->getChildView();

    m_model->moveItem(childView->getItem(), parentView->getItem(), {}, -1);
    m_scene.onModelChanged();
}

void SceneModelController::setDelayedCommand(SceneModelController::ModelCommand command)
{
    if (m_command)
        throw std::runtime_error(
            "Error in GraphicsObjectController::setDelayedCommand: command was already set.");

    m_command = command;
}

void SceneModelController::executeDelayedCommand()
{
    ModelCommandExecutor executor(m_command, m_model);
    if (executor.execute())
        m_scene.onModelChanged();
}

void SceneModelController::onModelChange()
{
    if (!m_block)
        m_scene.onModelChanged();
}

void SceneModelController::onModelDestroyed()
{
    m_model = nullptr;
    m_scene.onModelDestroyed();
}

namespace {
std::set<const SessionItem*> topItems(const QList<QGraphicsItem*>& views)
{
    std::vector<const SessionItem*> items;
    for (auto view: views)
        if (auto iview = dynamic_cast<IView*>(view); iview && iview->getItem())
            items.push_back(iview->getItem());

    std::set<const SessionItem*> result;
    for (const SessionItem* item: items) {
        auto parent = item->parent();
        bool has_parent = false;
        while (parent != nullptr) {
            has_parent = std::find(items.begin(), items.end(), parent) != items.end();
            if (has_parent)
                break;
            parent = parent->parent();
        }
        if (!has_parent)
            result.insert(item);
    }

    return result;
}

std::map<const SessionItem*, SessionItem*>
addChildItems(const std::map<const SessionItem*, SessionItem*>& tab)
{
    auto result = tab;
    auto items = keys(tab);
    while(!items.empty()) {
        auto item = items.front();
        const auto in_children = item->children();
        const auto out_children = result[item]->children();
        for(size_t i = 0, size = in_children.size(); i < size; ++i) {
            const auto child = in_children[i];
            if (!SampleViewFactory::isValidType(child->modelType()))
                continue;
            result.insert({child, out_children[i]});
            items.push_back(child);
        }
        items.pop_front();
    }

    return result;
}

std::list<const SessionItem*> findUnselectedItems(const std::set<QGraphicsItem*>& views,
                                                  std::list<const SessionItem*> keys)
{
    std::set<const SessionItem*> selected;
    for (auto view: views)
        if (auto iview = dynamic_cast<IView*>(view); iview && iview->getItem())
            selected.insert(iview->getItem());

    for (auto item: selected)
        keys.erase(std::find(keys.begin(), keys.end(), item));

    return keys;
}

std::set<QGraphicsItem*> extendWithChildren(QList<QGraphicsItem*> views)
{
    std::set<QGraphicsItem*> result(views.begin(), views.end());
    while (!views.empty()) {
        auto iview = dynamic_cast<IView*>(views.front());
        views.pop_front();
        if (!iview)
            continue;
        result.insert(iview);
        const auto children = iview->childItems();
        views.append(iview->childItems());
    }
    return result;
}

std::set<IView*> connectedViews(const std::set<QGraphicsItem*>& views, const DesignerScene& scene)
{
    std::set<IView*> connected_views;

    // first add child views from the input ports of the selected connections
    for (auto view : views)
        if (auto connection = dynamic_cast<NodeEditorConnection*>(view))
            connected_views.insert(connection->getChildView());

    // now add the views of child session items
    for (auto view : views) {
        auto iview = dynamic_cast<IView*>(view);
        if (!iview || !iview->getItem())
            continue;
        SessionItem* item = iview->getItem();
        for (auto child : item->children()) {
            auto child_view = scene.getViewForItem(child);
            if (child_view && child_view->parentObject() != iview)
                connected_views.insert(child_view);
        }
    }

    return connected_views;
}

std::set<IView*> topViews(const QList<QGraphicsItem*>& views)
{
    std::set<IView *> result;
    for (QGraphicsItem* view: views) {
        auto iview = dynamic_cast<IView*>(view);
        if (!iview || !iview->getItem())
            continue;
        const bool has_ancestors =
            std::accumulate(views.begin(), views.end(), false,
                            [view](bool result, QGraphicsItem* pview) {
                                return result || pview->isAncestorOf(view);
                            });
        if (!has_ancestors)
            result.insert(iview);
    }
    return result;
}

template<class T, class U>
std::list<T> keys(const std::map<T, U> input)
{
    std::list<T> result;
    std::transform(input.begin(), input.end(), std::back_inserter(result),
                   [](const auto& key_value) { return key_value.first; });
    return result;
}
}
