// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "vectoritem.h"
#include "itemmapper.h"
#include "customvariants.h"
#include <sstream>

using namespace ModelView;

const std::string VectorItem::P_X = "X";
const std::string VectorItem::P_Y = "Y";
const std::string VectorItem::P_Z = "Z";

VectorItem::VectorItem() : CompoundItem(Constants::VectorType)
{
    addProperty<>(P_X, 0.0);
    addProperty<>(P_Y, 0.0);
    addProperty<>(P_Z, 0.0);

    setEditable(false);

    update_label();
}

void VectorItem::activate()
{
    mapper()->setOnPropertyChange([this](SessionItem*, std::string) { update_label(); });
}

void VectorItem::update_label()
{
    std::ostringstream ostr;
    ostr << "("
         << getItemValue(P_X).toDouble() << ", "
         << getItemValue(P_Y).toDouble() << ", "
         << getItemValue(P_Z).toDouble()
         << ")";
    setDataIntern(QVariant::fromValue(ostr.str()), ItemDataRole::DATA);
}
