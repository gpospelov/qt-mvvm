// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_SCENEWIDGET_H
#define GRAPHICSPROXY_SCENEWIDGET_H

#include <QWidget>

class QBoxLayout;
class ScenePropertyWidget;
class QToolBar;
class QAction;
class SceneModel;
class GraphicsScene;
class GraphicsView;

namespace ModelView
{
class ColorMapCanvas;
} // namespace ModelView

//! Shows canvas with plots on the left and property editor on the right.

class SceneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneWidget(SceneModel* model = nullptr, QWidget* parent = nullptr);

private:
    void init_actions();

    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QToolBar* m_toolBar{nullptr};
    QAction* m_resetViewportAction{nullptr};
    QAction* m_setViewportToRoiAction{nullptr};

    ScenePropertyWidget* m_propertyWidget{nullptr};
    ModelView::ColorMapCanvas* m_colorMapCanvas{nullptr};
    GraphicsScene* graphics_scene{nullptr};
    GraphicsView* graphics_view{nullptr};
    SceneModel* m_model{nullptr};
};

#endif // GRAPHICSPROXY_SCENEWIDGET_H
