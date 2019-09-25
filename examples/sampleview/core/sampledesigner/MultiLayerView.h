// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/MultiLayerView.h
//! @brief     Defines class MultiLayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERVIEW_H
#define MULTILAYERVIEW_H

#include "ILayerView.h"

class DesignerMimeData;
class QGraphicsSceneDragDropEvent;

//! Class representing view of MultiLayer.
//! Handles drop of other MultiLayer and Layer views on top of it
class MultiLayerView : public ILayerView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::MULTILAYER };

    MultiLayerView(QGraphicsItem* parent = nullptr);
    ~MultiLayerView() override;

    int type() const override { return TYPE; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void addView(IView* childView) override;

    int getDropArea(QPointF pos);
    QRectF getDropAreaRectangle(int row);
    QLineF getInterfaceLine(int row) const;

    // slots:
    void updateGeometry();
    void onLayerAboutToBeDeleted();

protected:
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
    const DesignerMimeData* checkDragEvent(QGraphicsSceneDragDropEvent* event);
    void update_appearance() override;

private:
    void addNewLayer(ILayerView* layer, int row);
    void removeLayer(ILayerView* layer);
    void updateHeight();
    void updateWidth();
    void alignChildren();

    QList<ILayerView*> m_layers;
    QList<QRectF> m_drop_areas;
    QList<QLineF> m_interfaces;
};


#endif // MULTILAYERVIEW_H
