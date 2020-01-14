// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTVIEW_H
#define PARTICLELAYOUTVIEW_H

#include "ConnectableView.h"

class ParticleLayoutView : public ConnectableView
{
public:
    ParticleLayoutView(QGraphicsItem* parent = nullptr);
    void addView(IView* childView) override; // to add Particle
};

#endif // PARTICLELAYOUTVIEW_H
