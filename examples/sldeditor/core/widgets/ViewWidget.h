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
    ViewWidget(QWidget* parent = nullptr);
    QRectF visibleRect() const;
    AxisViewWidget* getAxisView() const;

protected:
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    AxisViewWidget* _axis;
};
