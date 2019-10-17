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

class InterferenceFunction1DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_1D_LATTICE };
    InterferenceFunction1DLatticeView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

class InterferenceFunction2DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE };
    InterferenceFunction2DLatticeView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

class InterferenceFunction2DParaCrystalView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA };
    InterferenceFunction2DParaCrystalView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

class InterferenceFunctionFinite2DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_FINITE_2D_LATTICE };
    InterferenceFunctionFinite2DLatticeView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

class InterferenceFunctionHardDiskView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_HARD_DISK };
    InterferenceFunctionHardDiskView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

class InterferenceFunctionRadialParaCrystalView : public ConnectableView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_RADIAL_PARA };
    InterferenceFunctionRadialParaCrystalView(QGraphicsItem *parent = nullptr);
    int type() const { return TYPE; }
};

#endif // INTERFERENCEFUNCTIONVIEW_H
