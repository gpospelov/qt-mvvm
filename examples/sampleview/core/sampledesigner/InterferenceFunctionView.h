// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONVIEW_H
#define INTERFERENCEFUNCTIONVIEW_H

#include "ConnectableView.h"

//! Represents all interference functions on the scene
class InterferenceFunctionView : public ConnectableView
{
public:
    InterferenceFunctionView(QGraphicsItem* parent = nullptr);
    void addView(IView*) override;
};

#endif // INTERFERENCEFUNCTIONVIEW_H
