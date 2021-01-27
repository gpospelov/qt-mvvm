// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTGRAPHSCORE_GRAPHPROPERTYWIDGET_H
#define PLOTGRAPHSCORE_GRAPHPROPERTYWIDGET_H

#include <QWidget>

class QBoxLayout;

namespace ModelView {
class ItemsTreeView;
} // namespace ModelView

namespace PlotGraphs {

class GraphModel;

//! Shows model content in standard tree view.

class GraphPropertyWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphPropertyWidget(GraphModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(GraphModel* model);

private:
    QBoxLayout* create_button_layout();

    ModelView::ItemsTreeView* m_treeView{nullptr};
    GraphModel* m_model{nullptr};
};

} // namespace PlotGraphs

#endif // PLOTGRAPHSCORE_GRAPHPROPERTYWIDGET_H
