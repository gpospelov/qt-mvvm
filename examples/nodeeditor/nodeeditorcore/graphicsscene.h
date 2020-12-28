// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_GRAPHICSSCENE_H
#define NODEEDITORCORE_GRAPHICSSCENE_H

#include <QGraphicsScene>

namespace NodeEditor {

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent);
    ~GraphicsScene() override;
};

} // namespace NodeEditor

#endif //  NODEEDITORCORE_GRAPHICSSCENE_H
