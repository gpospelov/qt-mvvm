// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef HANDLE_H
#define HANDLE_H

#include "ViewObject.h"

#include <QGraphicsItem>

class HandleItem;

/*!
@class Handle
@brief The visual handle element
*/

class Handle : public ViewObject
{
    Q_OBJECT
public:
    //! The constructor
    Handle(HandleItem* item);

    //! The bounding rectangle of the handle
    QRectF boundingRect() const override;
    //! The shape ? 
    QPainterPath shape() const override;
    //! The overriden paint method
    void paint(
        QPainter* painter, const QStyleOptionGraphicsItem* option, 
        QWidget* widget) override;
    //! Return a pointer to the handle item
    HandleItem* handleItem() const {return handle_item;};

signals:
    //! Moved signal
    void moved();

protected:
    //! On move update the model
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    //! The link back to the item 
    HandleItem* handle_item;
    //! The color property
    QColor color;

};

#endif
