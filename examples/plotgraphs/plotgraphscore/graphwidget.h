// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class GraphModel;
class GraphPropertyWidget;
class QToolBar;
class QAction;

namespace ModelView
{
class ItemsTreeView;
class GraphCanvas;
} // namespace ModelView

//! Shows canvas with plots on the left and property editor on the right.

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);
    ~GraphWidget();

    void setModel(GraphModel* model);

private:
    void init_actions();

    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QToolBar* m_toolBar{nullptr};
    QAction* m_resetViewportAction{nullptr};
    QAction* m_addGraphAction{nullptr};
    QAction* m_removeGraphAction{nullptr};

    ModelView::GraphCanvas* m_graphCanvas{nullptr};
    GraphPropertyWidget* m_propertyWidget{nullptr};
    GraphModel* m_model{nullptr};
};

#endif // GRAPHWIDGET_H
