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
class GraphWidgetToolBar;
class JobManager;

namespace ModelView
{
class ItemsTreeView;
class GraphCanvas;
} // namespace ModelView

/*!
@class GraphWidget
@brief Shows canvas with plots on the left and property editor on the right.
*/

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);
    ~GraphWidget();

    void setModel(GraphModel* model);

private:
    void init_connections();

    GraphWidgetToolBar* toolbar{nullptr};
    ModelView::GraphCanvas* m_graphCanvas{nullptr};
    GraphPropertyWidget* m_propertyWidget{nullptr};
    GraphModel* m_model{nullptr};
    std::unique_ptr<JobManager> job_manager;
};

#endif // GRAPHWIDGET_H
