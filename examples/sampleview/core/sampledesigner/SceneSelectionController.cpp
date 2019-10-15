#include "SceneSelectionController.h"
#include "DesignerScene.h"
#include <QItemSelectionModel>

SceneSelectionController::SceneSelectionController(DesignerScene* scene, QItemSelectionModel* model)
    : QObject(scene)
    , m_scene(scene)
    , m_model(model)
{
    if (!m_scene)
        throw std::runtime_error("Error in SceneSelectionController: passed scene is null");
    if (!m_model)
        throw std::runtime_error(
            "Error in SceneSelectionController: passed selection model is null");
}
