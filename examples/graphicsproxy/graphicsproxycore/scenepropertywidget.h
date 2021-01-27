// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_SCENEPROPERTYWIDGET_H
#define GRAPHICSPROXYCORE_SCENEPROPERTYWIDGET_H

#include <QWidget>

class QBoxLayout;
class QBoxLayout;
class QSlider;

namespace ModelView {
class ItemsTreeView;
} // namespace ModelView

namespace GraphicsProxy {

class SceneModel;

//! Shows model content in standard tree view.

class ScenePropertyWidget : public QWidget {
    Q_OBJECT

public:
    explicit ScenePropertyWidget(SceneModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(SceneModel* model);

private:
    void setupSlider();
    QBoxLayout* createButtonLayout();

    QSlider* m_slider{nullptr};
    ModelView::ItemsTreeView* m_treeView{nullptr};
    SceneModel* m_model{nullptr};
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_SCENEPROPERTYWIDGET_H
