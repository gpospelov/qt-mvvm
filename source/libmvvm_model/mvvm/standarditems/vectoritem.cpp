// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/customvariants.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/standarditems/vectoritem.h>
#include <sstream>

using namespace ModelView;

const std::string VectorItem::P_X = "X";
const std::string VectorItem::P_Y = "Y";
const std::string VectorItem::P_Z = "Z";

VectorItem::VectorItem() : CompoundItem(Constants::VectorItemType)
{
    addProperty(P_X, 0.0);
    addProperty(P_Y, 0.0);
    addProperty(P_Z, 0.0);

    setEditable(false);

    update_label();
}

void VectorItem::activate()
{
    auto on_property_change = [this](SessionItem*, std::string) { update_label(); };
    mapper()->setOnPropertyChange(on_property_change, this);
}

void VectorItem::update_label()
{
    std::ostringstream ostr;
    ostr << "(" << property(P_X).value<double>() << ", " << property(P_Y).value<double>() << ", "
         << property(P_Z).value<double>() << ")";
    setDataIntern(QVariant::fromValue(ostr.str()), ItemDataRole::DATA);
}
