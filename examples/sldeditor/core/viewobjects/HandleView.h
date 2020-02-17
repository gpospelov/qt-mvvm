// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef HANDLEVIEW_H
#define HANDLEVIEW_H

#include "ViewObject.h"

#include <QGraphicsItem>

class HandleItem;

/*!
@class Handle
@brief The visual handle element
*/
class HandleView : public ViewObject
{
    Q_OBJECT

public:
    HandleView(HandleItem* item);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF getSceneRect() const;
    HandleItem* handleItem() const;

signals:
    void moved();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    HandleItem* handle_item;
    QColor color;
};

#endif // HANDLEVIEW_H
