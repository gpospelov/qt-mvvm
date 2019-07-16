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
class MultiLayerCandidate;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class ILayerView : public ConnectableView
{
    Q_OBJECT

public:
    ILayerView(QGraphicsItem *parent = nullptr);

    enum { TYPE = DesignerHelper::LAYER };

    int type() const { return TYPE; }

    virtual QString getLabel() const { return QString(); }

    void updateLabel();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void update_appearance();

    // slots:
    void onPropertyChange(const std::string& propertyName) override;

private:
    void updateHeight();
    void updateColor();

    MultiLayerCandidate getMultiLayerCandidate();
    QPointF m_drag_start_position;
};


//! Class to hold MultiLayer candidate for dropping LayerView.
class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0){}
    MultiLayerView *multilayer; //!< pointer to the candidate
    int row; //!< requested row number to drop in
    int distance; //!< distance from given ILayerView and drop area
    bool operator< (const MultiLayerCandidate& cmp) const;
    operator bool() const { return bool(multilayer); }
    //! returns line representing interface of multilayer in scene coordinates
    QLineF getInterfaceToScene();
};


#endif // ILAYERVIEW_H
