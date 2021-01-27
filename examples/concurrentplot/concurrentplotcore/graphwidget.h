// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CONCURRENTPLOTCORE_GRAPHWIDGET_H
#define CONCURRENTPLOTCORE_GRAPHWIDGET_H

#include <QWidget>

class GraphModel;
class GraphPropertyWidget;
class GraphWidgetToolBar;
class JobManager;

namespace ModelView {
class GraphCanvas;
} // namespace ModelView

//! Shows canvas with plots on the left and property editor on the right.
//! Provides connections between toolbar on JobManager.

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(GraphModel* model);

public slots:
    void onSimulationCompleted();

private:
    void init_toolbar_connections();
    void init_jobmanager_connections();

    GraphWidgetToolBar* m_toolbar{nullptr};
    ModelView::GraphCanvas* m_graphCanvas{nullptr};
    GraphPropertyWidget* m_propertyWidget{nullptr};
    GraphModel* m_model{nullptr};
    JobManager* m_jobManager{nullptr};
};

#endif // CONCURRENTPLOTCORE_GRAPHWIDGET_H
