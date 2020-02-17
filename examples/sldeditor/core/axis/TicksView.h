// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TICKSVIEW_H
#define TICKSVIEW_H

/*!
@class TicksView
@brief This instance will manage the ticks and their spacing
*/
class TicksView
{

public:
    TicksView();
    TicksView(float min, float max);
    void calculate();
    float niceNum(float range, bool round);
    void setMinMaxPoints(float minPoint, float maxPoint);
    void setMaxTicks(float maxTicks);
    int decimals(void);

public:
    float minPoint;
    float maxPoint;
    float maxTicks;
    float tickSpacing;
    float range;
    float niceMin;
    float niceMax;
};
#endif // TICKSVIEW_H