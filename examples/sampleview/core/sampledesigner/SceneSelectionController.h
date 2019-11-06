// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SCENESELECTIONCONTROLLER_H
#define SCENESELECTIONCONTROLLER_H

#include <QObject>

class DesignerScene;
class QItemSelectionModel;

//! Controls the communication between DesignerScene instance and an external selection model
class SceneSelectionController : public QObject
{
    Q_OBJECT
public:
    SceneSelectionController(DesignerScene* scene, QItemSelectionModel* model);

    void onSceneSelectionChanged() {}
    void onModelSelectionChanged() {}

private:
    DesignerScene* m_scene;
    QItemSelectionModel* m_model;
};

#endif // SCENESELECTIONCONTROLLER_H
