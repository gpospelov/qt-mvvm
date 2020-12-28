// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_GRAPHICSVIEW_H
#define NODEEDITORCORE_GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsScene;

//! Graphics view to show QCustomPlot with additional elements on top.

class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    GraphicsView(GraphicsScene* scene, QWidget* parent);
};

#endif //  NODEEDITORCORE_GRAPHICSVIEW_H
