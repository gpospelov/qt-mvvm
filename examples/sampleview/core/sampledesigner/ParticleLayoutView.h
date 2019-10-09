// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTVIEW_H
#define PARTICLELAYOUTVIEW_H

#include "ConnectableView.h"

class ParticleLayoutView : public ConnectableView
{
public:
    ParticleLayoutView(QGraphicsItem *parent = nullptr);
    void addView(IView *childView) override; // to add Particle
};

#endif // PARTICLELAYOUTVIEW_H
