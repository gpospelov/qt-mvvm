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
#include "DesignerSceneUtils.h"
#include "NodeEditorConnection.h"
#include "modelmapper.h"
#include "modelutils.h"
#include "sessionitem.h"
#include <QSet>

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

//! Retrieves keys from a map
QSet<SessionItem*> keys(const std::map<SessionItem*, SessionItem*>& input);

//! Converts a view iterable into the list of corresponding SessionItem pointers.
template<class T>
QSet<SessionItem*> viewToItem(const T& views);

//! Filters and returns all NodeEditorConnection instances from the input list.
QList<NodeEditorConnection*> connections(const QList<QGraphicsItem*>& views);

//! Returns all unique child views of the given connection list.
QSet<IView*> childViews(const QList<NodeEditorConnection*>& connections);

//! Maps given items with the lookup_table.
QSet<SessionItem*> map(const std::map<SessionItem*, SessionItem*>& lookup_table,
                       const QSet<SessionItem*>& items);
} // namespace

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

    const QSet<SessionItem*> selected_items = viewToItem(DesignerSceneUtils::appendChildren(views));

    std::map<SessionItem*, SessionItem*> lookup_table;
    for (SessionItem* origin: DesignerSceneUtils::headItems(selected_items)) {
        SessionItem* copy = m_temp_model.copyItem(origin, m_temp_model.rootItem());
        const auto to_merge = DesignerSceneUtils::makeLookupTable(origin, copy);
        lookup_table.insert(to_merge.begin(), to_merge.end());
    }

    auto to_remove =
        map(lookup_table, DesignerSceneUtils::visibleItems(keys(lookup_table) - selected_items));

    selectivelyRemove(to_remove, &m_temp_model);
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

    // Remove directly selected connections
    for (auto item : viewToItem(childViews(connections(views))))
        m_model->moveItem(item, m_model->rootItem(), {}, -1);

    // Remove the items of the selected views
    selectivelyRemove(viewToItem(DesignerSceneUtils::appendChildren(views)), m_model);

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

void SceneModelController::selectivelyRemove(const QSet<ModelView::SessionItem*>& items,
                                             SampleModel* m_model)
{
    for (auto item: items)
        for (SessionItem* child : DesignerSceneUtils::visibleItems(item->children()))
            m_model->moveItem(child, m_model->rootItem(), {}, -1);

    for (auto item : DesignerSceneUtils::headItems(items))
        Utils::DeleteItemFromModel(item);
}

namespace {
QSet<SessionItem*> keys(const std::map<SessionItem*, SessionItem*>& input)
{
    QSet<SessionItem*> result;
    std::for_each(input.begin(), input.end(),
                  [&result](const auto& key_value) { return result.insert(key_value.first); });
    return result;
}

template<class T>
QSet<SessionItem *> viewToItem(const T& views)
{
    QSet<SessionItem*> items;
    for (auto view: views)
        if (auto iview = dynamic_cast<IView*>(view); iview && iview->getItem())
            items.insert(iview->getItem());

    return items;
}

QList<NodeEditorConnection*> connections(const QList<QGraphicsItem*>& views)
{
    QList<NodeEditorConnection*> connections;

    for (auto view : views)
        if (auto connection = dynamic_cast<NodeEditorConnection*>(view))
            connections.push_back(connection);

    return connections;
}

QSet<IView*> childViews(const QList<NodeEditorConnection*>& connections)
{
    QSet<IView*> children;

    for (auto connection : connections)
        if (auto child = connection->getChildView())
            children.insert(child);

    return children;
}

QSet<SessionItem*> map(const std::map<SessionItem*, SessionItem*>& lookup_table,
                       const QSet<SessionItem*>& items)
{
    QSet<SessionItem*> result;
    for (auto item: items)
        result.insert(lookup_table.at(item));
    return result;
}
}
