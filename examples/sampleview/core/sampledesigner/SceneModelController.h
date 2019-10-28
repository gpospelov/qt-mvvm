// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SCENEMODELCONTROLLER_H
#define SCENEMODELCONTROLLER_H

#include "SampleModel.h"
#include <functional>

class DesignerScene;
class IView;
class NodeEditorConnection;
class QGraphicsItem;
template <class T> class QList;

//! Manages scene-model communication.
class SceneModelController
{
public:
    using ModelCommand = std::function<void (ModelView::SessionModel& model)>;

    SceneModelController(DesignerScene& scene, SampleModel* model);
    ~SceneModelController();

    //! Propagates copying of the views from the scene to the model
    void copy(const QList<QGraphicsItem*>& views);
    //! Propagates view pasting from the scene to the model
    void paste();
    //! Propagates deletion of views on the scene to the model
    void remove(const QList<QGraphicsItem*>& views);
    //! Propagates view connection to the model
    void onConnect(NodeEditorConnection* connection);

    const SampleModel* model() const { return m_model; }

    //! Sets a command to model for later execution
    void setDelayedCommand(ModelCommand command);
    void executeDelayedCommand();

private:
    void onModelChange();
    void onModelDestroyed();

    //! Removes given items from model with preliminary moving their visible children to the model
    //! root. The items shall belong to the passed sample model.
    void selectivelyRemove(const QSet<ModelView::SessionItem*>& items, SampleModel* m_model);

    DesignerScene& m_scene;
    SampleModel* m_model;
    bool m_block;
    ModelCommand m_command;

    SampleModel m_temp_model; //!< Temporary model to store copied items
};

#endif // SCENEMODELCONTROLLER_H
