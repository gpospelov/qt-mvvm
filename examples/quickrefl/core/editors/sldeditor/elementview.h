// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef ELEMENTVIEW_H
#define ELEMENTVIEW_H

#include "graphicsscene.h"

#include <QGraphicsObject>

//! The interface of any QGraphicsViewItem on GraphicsScene to the Sceneadapter
class ElementView : public QGraphicsObject
{
    Q_OBJECT

public:
    ElementView();
    ~ElementView();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

    ModelView::SceneAdapterInterface* sceneAdapter() const;

    void setCenterBased(bool choice);
    void adaptX(bool choice);
    void adaptY(bool choice);
    void adaptW(bool choice);
    void adaptH(bool choice);
    void stretchLeft(bool choice);
    void stretchRight(bool choice);

protected:
    QRectF displayRect(const QRectF& real_rect) const;
    QPainterPath displayPath(QPainterPath real_path) const;
    QPointF scenePos(QPointF pixel_pos) const;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF displayRectCenterBased(const QRectF& real_rect) const;
    QRectF displayRectEdgeBased(const QRectF& real_rect) const;
    QRectF stretchRectLeft(const QRectF& real_rect) const;
    QRectF stretchRectRight(const QRectF& real_rect) const;

private:
    bool m_center_based = true;
    bool m_adapt_x = true;
    bool m_adapt_y = true;
    bool m_adapt_width = true;
    bool m_adapt_height = true;
    bool m_stretch_left = false;
    bool m_stretch_right = false;
};

#endif // ELEMENTVIEW_H
