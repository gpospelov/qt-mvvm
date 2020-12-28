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
#include <map>

namespace NodeEditor {

class SampleModel;
class ConnectableView;
class ConnectableItem;
class SessionItem;

//! Custom graphics scene for node editor.

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(SampleModel* model, QObject* parent);
    ~GraphicsScene() override;

private:
    void updateScene();
    void processItem(ConnectableItem* item);

    SampleModel* m_model{nullptr};
    std::map<SessionItem*, ConnectableView> m_itemToView;
};

} // namespace NodeEditor

#endif //  NODEEDITORCORE_GRAPHICSSCENE_H
