// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/LayerView.h
//! @brief     Defines class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ILayerView.h"

//! Class that represents view of Layer
class LayerView : public ILayerView
{
    Q_OBJECT
public:
    LayerView(QGraphicsItem *parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void addView(IView* childView) override; // to add ParticleLayout

    void onPropertyChange(const std::string& propertyName) override;

private:
    void update_appearance() override;
    void updateColor();
    void updateHeight();
    void updateLabel();
};

#endif // LAYERVIEW_H
