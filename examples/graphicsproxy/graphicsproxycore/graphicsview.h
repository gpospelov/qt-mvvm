// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_GRAPHICSVIEW_H
#define GRAPHICSPROXY_GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsScene;

//! Custom graphics view to show QCustomPlot with additional elements on top.

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(GraphicsScene* scene, QWidget* parent);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    GraphicsScene* scene{nullptr};
};

#endif //  GRAPHICSPROXY_GRAPHICSVIEW_H
