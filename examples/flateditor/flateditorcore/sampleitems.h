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

const std::string BeamItemType = "Beam";
const std::string DistributionNoneItemType = "DistributionNone";
const std::string DistributionGaussianItemType = "DistributionGaussian";
const std::string DistributionLogNormalItemType = "DistributionLogNormal";
const std::string DistributionTrapezoidItemType = "DistributionTrapezoid";
const std::string DistributionGroupItemType = "DistributionGroup";

} // namespace Constants

//! Item to represent x-ray or neutron beam with properties to setup.

class BeamItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_BEAM_TYPE = "P_BEAM_TYPE";
    static inline const std::string P_IS_POLARIZED = "P_IS_POLARIZED";
    static inline const std::string P_WAVELENGTH = "P_WAVELENGTH";
    static inline const std::string P_ANGULAR_DISTRIBUTION = "P_ANGULAR_DISTRIBUTION";
    static inline const std::string P_ACCESS_LIGHT_BULB_COLOR = "P_COLOR";
    BeamItem();

    void activate() override;

private:
    void update_appearance();
};

//! Item to represent fixed value.

class DistributionNoneItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_MEAN = "P_MEAN";
    DistributionNoneItem();
};

//! Item to represent gaussian distribution.

class DistributionGaussianItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_MEAN = "P_MEAN";
    static inline const std::string P_STD_DEV = "P_STD_DEV";

    DistributionGaussianItem();
};

//! Item to represent log normal distribution.

class DistributionLogNormalItem : public ModelView::CompoundItem
{

public:
    static inline const std::string P_MEDIAN = "P_MEDIAN";
    static inline const std::string P_SCALE_PAR = "P_SCALE_PAR";

    DistributionLogNormalItem();
};

//! Item to represent trapezoid distribution.

class DistributionTrapezoidItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_CENTER = "P_CENTER";
    static inline const std::string P_LEFTWIDTH = "P_LEFTWIDTH";
    static inline const std::string P_MIDDLEWIDTH = "P_MIDDLEWIDTH";
    static inline const std::string P_RIGHTWIDTH = "P_RIGHTWIDTH";

    DistributionTrapezoidItem();
};

//! Group to hold probability distribution items.

class DistributionGroupItem : public ModelView::GroupItem
{
public:
    DistributionGroupItem();
};

#endif // FLATEDITORCORE_ITEMS_H
