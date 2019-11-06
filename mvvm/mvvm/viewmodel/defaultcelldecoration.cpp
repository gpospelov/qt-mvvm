// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/viewmodel/defaultcelldecoration.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/externalproperty.h>
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
        return variant.value<bool>() ? "True" : "False";

    else if (Utils::IsExtPropertyVariant(variant))
        return variant.value<ExternalProperty>().text();

    return {};
}

