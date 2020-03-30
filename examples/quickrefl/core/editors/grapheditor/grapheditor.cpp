// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "grapheditor.h"
#include "grapheditortoolbar.h"
#include <QHBoxLayout>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

GraphEditor::GraphEditor(QWidget* parent)
    : QWidget(parent), toolbar(new GraphEditorToolBar), graph_canvas(new ModelView::GraphCanvas)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(graph_canvas);
    layout->addWidget(toolbar);
}

void GraphEditor::setItem(ModelView::GraphViewportItem* viewport_item)
{
    graph_canvas->setItem(viewport_item);
}
