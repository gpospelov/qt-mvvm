// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_MODELEDITORWIDGET_H
#define NODEEDITORCORE_MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QSplitter;
class QToolBar;
class QLayout;

namespace NodeEditor {

class SampleModel;
class GraphicsView;
class GraphicsScene;
class PropertyWidget;
class GraphicsSceneController;
class PiecesList;

//! Main widget for model editing. Contains a toolbar on top, and few widgets beneath:
//! a graphics scene representing a node editor, a toolbox with items to drag-and-drop on the
//! scene, property editor, and sample tree view. Belongs to MainWindow.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    ~ModelEditorWidget() override;

private:
    void setupSaveLoadActions();
    void setupUndoRedoActions();
    void setupConnections();
    QLayout* createBottomLayout();

    QToolBar* m_toolBar{nullptr};
    PiecesList* m_piecesList{nullptr};
    PropertyWidget* m_propertyWidget{nullptr};
    GraphicsScene* m_graphicsScene{nullptr};
    GraphicsView* m_graphicsView{nullptr};
    std::unique_ptr<GraphicsSceneController> m_sceneContoller;
    QSplitter* m_splitter{nullptr};
    SampleModel* m_model{nullptr};
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_MODELEDITORWIDGET_H
