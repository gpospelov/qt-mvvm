// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsview.h"
#include "graphicsscene.h"
#include <QKeyEvent>

namespace NodeEditor {

GraphicsView::GraphicsView(GraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setRenderHint(QPainter::Antialiasing);
}

void GraphicsView::keyPressEvent(QKeyEvent* event)
{
    const bool delete_key = event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace;
    if (delete_key)
        deleteSelectedRequest();
    else
        QGraphicsView::keyPressEvent(event);
}

} // namespace NodeEditor
