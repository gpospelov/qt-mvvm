// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_ITEMS_H
#define FLATEDITORCORE_ITEMS_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/groupitem.h>
#include <string>

namespace Constants
{

const std::string DistributionGaussianItemType = "DistributionGaussian";
const std::string DistributionLogNormalItemType = "DistributionLogNormal";
const std::string DistributionTrapezoidItemType = "DistributionTrapezoid";
const std::string DistributionGroupItemType = "DistributionGroup";

} // namespace Constants

/*!
@class DistributionGaussianItem
@brief Item to represent gaussian distribution.
*/

class DistributionGaussianItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_MEAN = "P_MEAN";
    static inline const std::string P_STD_DEV = "P_STD_DEV";

    DistributionGaussianItem();
};

/*!
@class DistributionLogNormalItem
@brief Item to represent log normal distribution.
*/

class DistributionLogNormalItem : public ModelView::CompoundItem
{

public:
    static inline const std::string P_MEDIAN = "P_MEDIAN";
    static inline const std::string P_SCALE_PAR = "P_SCALE_PAR";

    DistributionLogNormalItem();
};

/*!
@class DistributionTrapezoidItem
@brief Item to represent trapezoid distribution.
*/

class DistributionTrapezoidItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_CENTER = "P_CENTER";
    static inline const std::string P_LEFTWIDTH = "P_LEFTWIDTH";
    static inline const std::string P_MIDDLEWIDTH = "P_MIDDLEWIDTH";
    static inline const std::string P_RIGHTWIDTH = "P_RIGHTWIDTH";

    DistributionTrapezoidItem();
};

/*!
@class DistributionGroupItem
@brief Group to hold probability distribution items.
*/

class DistributionGroupItem : public ModelView::GroupItem
{
public:
    DistributionGroupItem();
};

#endif // FLATEDITORCORE_ITEMS_H
