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

#include "GraphicsScene.h"

#include <QGraphicsObject>

class ElementView : public QGraphicsObject
{
    Q_OBJECT

public:
    ElementView();
    ~ElementView();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

    ModelView::SceneAdapterInterface* getSceneAdapter() const;

    void setCenterBased(bool choice);
    void adaptX(bool choice);
    void adaptY(bool choice);
    void adaptW(bool choice);
    void adaptH(bool choice);

protected:
    QRectF displayRect(QRectF real_rect) const;
    QPainterPath displayPath(QPainterPath real_path) const;
    QPointF scenePos(QPointF pixel_pos) const;

private:
    bool m_center_based = true;
    bool m_adapt_x = true;
    bool m_adapt_y = true;
    bool m_adapt_width = true;
    bool m_adapt_height = true;
};

#endif // ELEMENTVIEW_H
