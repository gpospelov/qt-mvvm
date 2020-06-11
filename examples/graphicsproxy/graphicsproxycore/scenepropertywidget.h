// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_SCENEPROPERTYWIDGET_H
#define GRAPHICSPROXY_SCENEPROPERTYWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class SceneModel;
class QBoxLayout;
class QSlider;

namespace ModelView
{
class ItemsTreeView;
} // namespace ModelView

/*!
@class ColorMapPropertyWidget
@brief Shows model content in standard tree view.
*/

class ScenePropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScenePropertyWidget(SceneModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(SceneModel* model);

private:
    void setup_slider();

    QBoxLayout* create_button_layout();
    QSlider* m_slider;
    ModelView::ItemsTreeView* m_treeView;
    SceneModel* m_model;
};

#endif // GRAPHICSPROXY_SCENEPROPERTYWIDGET_H
