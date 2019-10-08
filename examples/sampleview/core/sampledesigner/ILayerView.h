// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ILAYERVIEW_H
#define ILAYERVIEW_H

#include "ConnectableView.h"

class MultiLayerView;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class ILayerView : public ConnectableView
{
    Q_OBJECT

public:
    ILayerView(QGraphicsItem* parent, int view_type);
    ~ILayerView() override ;

    QString getLabel() const override { return QString(); }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    auto determineAction(const MultiLayerView* new_parent, int row);
    QPointF m_drag_start_position;
};


#endif // ILAYERVIEW_H
