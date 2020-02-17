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

class ViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ViewWidget(QWidget* parent = nullptr);
    GraphicsScene* getScene() const;

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QPointF init_mouse_pos;
    QPointF scale_factor;
};
