// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include <QColor>
#include <mvvm/model/comboproperty.h>
#include <mvvm/signals/itemmapper.h>

using namespace ModelView;

namespace
{
const std::string xrays = "x-rays";
const std::string neutrons = "neutrons";
} // namespace

// ----------------------------------------------------------------------------

BeamItem::BeamItem() : ModelView::CompoundItem(::Constants::BeamItemType)
{
    auto combo = ComboProperty::createFrom({xrays, neutrons});
    addProperty(P_BEAM_TYPE, combo)->setDisplayName("Type");

    addProperty(P_IS_POLARIZED, false)->setDisplayName("Polarization");
    addProperty(P_WAVELENGTH, 42.0)->setDisplayName("Wavelength");
    addProperty<DistributionGroupItem>(P_ANGULAR_DISTRIBUTION)
        ->setDisplayName("Angular distribution");

    addProperty(P_ACCESS_LIGHT_BULB_COLOR, QColor(Qt::red))->setDisplayName("Access light");

    update_appearance();
}

void BeamItem::activate()
{
    auto on_beam_type_change = [this](SessionItem*, std::string property) {
        if (property == P_BEAM_TYPE)
            update_appearance();
    };

    mapper()->setOnPropertyChange(on_beam_type_change, this);
}

//! Enables IS_POLARIZED property when beam type changes from x-rays to neutrons.

void BeamItem::update_appearance()
{
    auto polarized_property = getItem(P_IS_POLARIZED);
    auto beam_type = property(P_BEAM_TYPE).value<ComboProperty>().value();

    if (beam_type == xrays)
        setProperty(P_IS_POLARIZED, false);

    polarized_property->setEnabled(property(P_BEAM_TYPE).value<ComboProperty>().value()
                                   == neutrons);
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
    registerItem<DistributionTrapezoidItem>("Trapezoid");
    init_group();
}
