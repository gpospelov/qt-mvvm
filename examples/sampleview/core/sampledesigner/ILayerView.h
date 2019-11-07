// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
    //! Determines the action to undertake as the result of mouse event
    auto determineAction(const MultiLayerView* new_parent, int row) const;

    void onNoChange();
    void onRelease(const QPointF& pos);
    void onChangeOwner(const ILayerView* requested_parent, int requested_row);

    //! Computes the insertion row for undelying session item.
    int insertionRow(const ILayerView* new_parent, int insertion_row) const;

    QPointF m_drag_start_position;
};


#endif // ILAYERVIEW_H
