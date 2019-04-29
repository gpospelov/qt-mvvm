// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaultcelldecoration.h"
#include "comboproperty.h"
#include "customvariants.h"
#include <QModelIndex>

using namespace ModelView;

bool DefaultCellDecoration::hasCustomDecoration(const QModelIndex& index) const
{
    return !cellText(index).empty();
}

std::string DefaultCellDecoration::cellText(const QModelIndex& index) const
{
    auto variant = index.data();

    if (Utils::IsComboVariant(variant))
        return variant.value<ComboProperty>().label();

    else if (Utils::IsBoolVariant(variant))
        return variant.toBool() ? "True" : "False";

    else if (Utils::IsBoolVariant(variant))
        return variant.toBool() ? "True" : "False";

    return {};
}
