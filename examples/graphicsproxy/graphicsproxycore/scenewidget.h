// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_SCENEWIDGET_H
#define GRAPHICSPROXYCORE_SCENEWIDGET_H

#include <QWidget>

class QBoxLayout;
class QToolBar;
class QAction;

namespace ModelView {
class ColorMapCanvas;
} // namespace ModelView

namespace GraphicsProxy {

class ScenePropertyWidget;
class SceneModel;
class GraphicsScene;
class GraphicsView;

//! Shows canvas with plots on the left and property editor on the right.

class SceneWidget : public QWidget {
    Q_OBJECT

public:
    explicit SceneWidget(SceneModel* model = nullptr, QWidget* parent = nullptr);

private:
    void initActions();
    QBoxLayout* createLeftLayout();
    QBoxLayout* createRightLayout();

    QToolBar* m_toolBar{nullptr};
    QAction* m_resetViewportAction{nullptr};
    QAction* m_setViewportToRoiAction{nullptr};

    ScenePropertyWidget* m_propertyWidget{nullptr};
    ModelView::ColorMapCanvas* m_colorMapCanvas{nullptr};
    GraphicsScene* m_graphicsScene{nullptr};
    GraphicsView* m_graphicsView{nullptr};
    SceneModel* m_model{nullptr};
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_SCENEWIDGET_H
