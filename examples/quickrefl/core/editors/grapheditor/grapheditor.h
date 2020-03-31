// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHEDITOR_H
#define GRAPHEDITOR_H

#include <QWidget>

namespace ModelView
{
class GraphCanvas;
class GraphViewportItem;
}

class GraphEditorToolBar;

//! Graph editor with GraphCanvas at the center, and few control buttons on the right.

class GraphEditor : public QWidget
{
    Q_OBJECT
public:
   explicit GraphEditor(QWidget* parent = nullptr);

    void setItem(ModelView::GraphViewportItem* viewport_item);

private:
    GraphEditorToolBar* toolbar{nullptr};
    ModelView::GraphCanvas* graph_canvas{nullptr};
};

#endif // GRAPHEDITOR_H
