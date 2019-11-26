// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include <mvvm/model/comboproperty.h>
#include <QColor>

using namespace ModelView;

// ----------------------------------------------------------------------------

BeamItem::BeamItem()
    : ModelView::CompoundItem(::Constants::BeamItemType)
{
    auto combo = ComboProperty::createFrom({"x-rays", "neutrons"});
    addProperty(P_BEAM_TYPE, combo)->setDisplayName("Type");

    addProperty(P_IS_POLARIZED, true)->setDisplayName("Polarization");
    addProperty(P_WAVELENGTH, 42.0)->setDisplayName("Wavelength");
    addProperty<DistributionGroupItem>(P_ANGULAR_DISTRIBUTION)->setDisplayName("Angular distribution");

    addProperty(P_ACCESS_LIGHT_BULB_COLOR, QColor(Qt::red))->setDisplayName("Access light");
}

// ----------------------------------------------------------------------------

DistributionNoneItem::DistributionNoneItem()
    : ModelView::CompoundItem(::Constants::DistributionNoneItemType)
{
    addProperty(P_MEAN, 0.5);
}

// ----------------------------------------------------------------------------

DistributionGaussianItem::DistributionGaussianItem()
    : ModelView::CompoundItem(::Constants::DistributionGaussianItemType)
{
    addProperty(P_MEAN, 0.5);
    addProperty(P_STD_DEV, 1.0);
}

// ----------------------------------------------------------------------------

DistributionLogNormalItem::DistributionLogNormalItem()
    : ModelView::CompoundItem(::Constants::DistributionLogNormalItemType)
{
    addProperty(P_MEDIAN, 1.0);
    addProperty(P_SCALE_PAR, 1.0);
}

// ----------------------------------------------------------------------------

DistributionTrapezoidItem::DistributionTrapezoidItem()
    : ModelView::CompoundItem(::Constants::DistributionTrapezoidItemType)
{
    addProperty(P_CENTER, 1.0);
    addProperty(P_LEFTWIDTH, 0.5);
    addProperty(P_MIDDLEWIDTH, 1.0);
    addProperty(P_RIGHTWIDTH, 0.6);
}

// ----------------------------------------------------------------------------

DistributionGroupItem::DistributionGroupItem() : GroupItem(::Constants::DistributionGroupItemType)
{
    registerItem<DistributionNoneItem>("None");
    registerItem<DistributionGaussianItem>("Gaussian");
    registerItem<DistributionLogNormalItem>("Log normal");
    registerItem<DistributionTrapezoidItem>("Trpezoid");
    init_group();
}
