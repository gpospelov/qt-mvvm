// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "TicksView.h"
#include <math.h>
#include <algorithm> 

TicksView::TicksView()
{
    maxTicks = 6;
}

TicksView::TicksView(float min, float max)
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
void TicksView::calculate() 
{
    range = niceNum(maxPoint - minPoint, true);
    tickSpacing = niceNum(range / (maxTicks - 1), true);
    niceMin = floor(minPoint / tickSpacing) * tickSpacing;
    niceMax = ceil(maxPoint / tickSpacing) * tickSpacing;
}

/**
* Returns a "nice" number approximately equal to range 
  Rounds the number if round = true Takes the ceiling if round = false.
*
* @param range the data range
* @param round whether to round the result
* @return a "nice" number to be used for the data range
*/
float TicksView::niceNum(float range, bool round) 
{   
    float exponent; /** exponent of range */
    float fraction; /** fractional part of range */
    float niceFraction; /** nice, rounded fraction */

    exponent = floor(log10(range));
    fraction = range / pow(10.f, exponent);

    if (round) 
    {   if (fraction < 1.5)
            niceFraction = 1;
        else if (fraction < 3)
            niceFraction = 2;
        else if (fraction < 7)
            niceFraction = 5;
        else
            niceFraction = 10;
    } 
    else 
    {   if (fraction <= 1)
            niceFraction = 1;
        else if (fraction <= 2)
            niceFraction = 2;
        else if (fraction <= 5)
            niceFraction = 5;
        else
            niceFraction = 10;
    }

    return niceFraction * pow(10, exponent);
}

/**
* Sets the minimum and maximum data points for the axis.
*
* @param minPoint the minimum data point on the axis
* @param maxPoint the maximum data point on the axis
*/
void TicksView::setMinMaxPoints(float minPoint, float maxPoint) 
{
    minPoint = std::min(minPoint, maxPoint);
    maxPoint = std::max(minPoint, maxPoint);
    calculate();
}

/**
* Sets maximum number of tick marks we're comfortable with
*
* @param maxTicks the maximum number of tick marks for the axis
*/
void TicksView::setMaxTicks(float maxTicks) 
{
    this->maxTicks = maxTicks;
    calculate();
}

// minimum number of decimals in tick labels
// use in sprintf statement:
// sprintf(buf, "%.*f", decimals(), tickValue);
int TicksView::decimals(void)
{
    float logTickX = log10(tickSpacing);
    if(logTickX >= 0)
        return 0;
    return (int)(abs(floor(logTickX)));
}
