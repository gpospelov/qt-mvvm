// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "GraphicsObjectController.h"
#include "ConnectableView.h"
#include "DesignerScene.h"
#include "NodeEditorConnection.h"
#include "SampleModel.h"
#include "modelmapper.h"
#include "modelutils.h"
#include "sessionitem.h"

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
    ModelCommandExecutor(GraphicsObjectController::ModelCommand& command, SessionModel* model)
        : m_command(command)
        , m_model(model)
    {}

    ~ModelCommandExecutor() { m_command = GraphicsObjectController::ModelCommand(); }

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
}

GraphicsObjectController::GraphicsObjectController(DesignerScene& scene, SampleModel* model)
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
}

GraphicsObjectController::~GraphicsObjectController()
{
    m_model->mapper()->unsubscribe(this);
}

void GraphicsObjectController::onDelete(QList<QGraphicsItem *> views)
{
    if (!m_model)
        return;
    BlockGuard signal_guard(m_block);

    //! Disconnect dependent items
    const auto connected_views = findConnectedViews(views);
    for (auto view: connected_views)
        m_model->moveItem(view->getItem(), m_model->rootItem(), {}, -1);

    const auto top_views = findTopViews(views);
    for (auto view: top_views)
        Utils::DeleteItemFromModel(view->getItem());

    m_scene.onModelChanged();
}

void GraphicsObjectController::onConnect(NodeEditorConnection *connection)
{
    if (!m_model)
        return;
    BlockGuard signal_guard(m_block);

    ConnectableView* parentView = connection->getParentView();
    ConnectableView* childView = connection->getChildView();

    m_model->moveItem(childView->getItem(), parentView->getItem(), {}, -1);
    m_scene.onModelChanged();
}

void GraphicsObjectController::setDelayedCommand(GraphicsObjectController::ModelCommand command)
{
    if (m_command)
        throw std::runtime_error(
            "Error in GraphicsObjectController::setDelayedCommand: command was already set.");

    m_command = command;
}

void GraphicsObjectController::executeDelayedCommand()
{
    ModelCommandExecutor executor(m_command, m_model);
    if (executor.execute())
        m_scene.onModelChanged();
}

void GraphicsObjectController::onModelChange()
{
    if (!m_block)
        m_scene.onModelChanged();
}

void GraphicsObjectController::onModelDestroyed()
{
    m_model = nullptr;
    m_scene.onModelDestroyed();
}

std::set<IView*>
GraphicsObjectController::findConnectedViews(QList<QGraphicsItem*> views) const
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
            auto child_view = m_scene.getViewForItem(child);
            if (child_view && child_view->parentObject() != iview)
                connected_views.insert(child_view);
        }
    }

    return connected_views;
}

std::set<IView*> GraphicsObjectController::findTopViews(QList<QGraphicsItem*> views) const
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
