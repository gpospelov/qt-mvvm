// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class QSplitter;

namespace NodeEditor {

class SampleModel;
class GraphicsView;
class GraphicsScene;
class PropertyWidget;
class GraphicsSceneController;

//! Main widget for model editing. Contains a graphics scene with node editor on the left,
//! and property panel on the right. Belongs to MainWindow.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    ~ModelEditorWidget() override;

private:
    void initConnections();

    PropertyWidget* m_propertyWidget{nullptr};
    GraphicsScene* m_graphicsScene{nullptr};
    GraphicsView* m_graphicsView{nullptr};
    std::unique_ptr<GraphicsSceneController> m_sceneContoller;
    QSplitter* m_splitter{nullptr};
};

} // namespace NodeEditor

#endif // MODELEDITORWIDGET_H
