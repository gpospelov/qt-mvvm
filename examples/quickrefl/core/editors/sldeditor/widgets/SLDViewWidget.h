// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDragMoveEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QWheelEvent>

class GraphicsScene;
class SLDController;

class SLDViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    SLDViewWidget(SLDController* sld_model, QWidget* parent = nullptr);
    GraphicsScene* getScene() const;

protected:
    void resizeEvent(QResizeEvent* event);
};
