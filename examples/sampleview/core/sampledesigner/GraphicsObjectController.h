// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHICSOBJECTCONTROLLER_H
#define GRAPHICSOBJECTCONTROLLER_H

#include <QList>
#include <set>

namespace ModelView {
class SessionModel;
}

class DesignerScene;
class IView;
class NodeEditorConnection;
class QGraphicsItem;
class SampleModel;

//! Manages scene-model communication.
class GraphicsObjectController
{
public:
    using ModelCommand = std::function<void (ModelView::SessionModel& model)>;

    explicit GraphicsObjectController(DesignerScene& scene, SampleModel* model);
    ~GraphicsObjectController();

    //! Propagates deletion of views on the scene to the model
    void onDelete(QList<QGraphicsItem*> views);
    //! Propagates view connection to the model
    void onConnect(NodeEditorConnection* connection);

    const SampleModel* model() const { return m_model; }

    //! Sets a command to model for later execution
    void setDelayedCommand(ModelCommand command);
    void executeDelayedCommand();

private:
    void onModelChange();
    void onModelDestroyed();

    //! Finds all the views connected to the passed list
    std::set<IView*> findConnectedViews(QList<QGraphicsItem*> views) const;
    //! Finds all the views with no ancestor in the passed list
    std::set<IView*> findTopViews(QList<QGraphicsItem*> views) const;

    DesignerScene& m_scene;
    SampleModel* m_model;
    bool m_block;
    ModelCommand m_command;
};

#endif // GRAPHICSOBJECTCONTROLLER_H
