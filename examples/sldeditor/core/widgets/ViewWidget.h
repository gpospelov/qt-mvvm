// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "AxisViewWidget.h"

#include <QDragMoveEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QWheelEvent>

class ViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    //! The constructor
    ViewWidget(QWidget* parent = nullptr);
    //! Get the visible region
    QRectF visibleRect() const;
    //! Get the axis
    AxisViewWidget* getAxisView() const;

protected:
    //! Manage wheelevent
    void wheelEvent(QWheelEvent* event);
    //! Manage the drag event
    void drageMoveEvent(QDragMoveEvent* event);
    //! The resize event that needs to propagate to axes
    void resizeEvent(QResizeEvent* event);

private:
    //! The axis items
    AxisViewWidget* _axis;
};
