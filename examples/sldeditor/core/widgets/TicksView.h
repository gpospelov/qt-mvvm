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

#include <algorithm> 

class TicksView 
{   
public:

    float minPoint;
    float maxPoint;
    float maxTicks;
    float tickSpacing;
    float range;
    float niceMin;
    float niceMax;

public:
    TicksView()
    {   
        maxTicks = 6;
    }

    /**
    * Instantiates a new instance of the NiceScale class.
    *
    * @param min the minimum data point on the axis
    * @param max the maximum data point on the axis
    */
    TicksView(float min, float max) 
    {   
        maxTicks = 6;
        minPoint = std::min(min, max);
        maxPoint = std::max(min, max);
        calculate();
    }

    /**
    * Calculate and update values for tick spacing and nice
    * minimum and maximum data points on the axis.
    */
    void calculate() ;

    /**
    * Returns a "nice" number approximately equal to range Rounds
    * the number if round = true Takes the ceiling if round = false.
    *
    * @param range the data range
    * @param round whether to round the result
    * @return a "nice" number to be used for the data range
    */
    float niceNum(float range, bool round) ;

    /**
    * Sets the minimum and maximum data points for the axis.
    *
    * @param minPoint the minimum data point on the axis
    * @param maxPoint the maximum data point on the axis
    */
    void setMinMaxPoints(float minPoint, float maxPoint) ;

    /**
    * Sets maximum number of tick marks we're comfortable with
    *
    * @param maxTicks the maximum number of tick marks for the axis
    */
    void setMaxTicks(float maxTicks) ;
    int decimals(void);
};
#endif //TICKSVIEW_H