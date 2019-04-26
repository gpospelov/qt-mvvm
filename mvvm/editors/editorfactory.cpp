// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorfactory.h"
#include "customvariants.h"
#include "comboproperty.h"
#include "combopropertyeditor.h"
#include "sessionitem.h"
#include "viewitem.h"
#include "abstractviewmodel.h"
#include "booleditor.h"
#include "coloreditor.h"
#include <QDebug>
#include <QModelIndex>

using namespace ModelView;

namespace
{

const SessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const AbstractViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

} // namespace

EditorFactory::EditorFactory() {}

CustomEditor* EditorFactory::createEditor(const QModelIndex& index, QWidget* parent) const
{
    CustomEditor* result(nullptr);

    if (auto item = itemFromIndex(index))
        return createEditor(item, parent);

    return result;
}

CustomEditor* EditorFactory::createEditor(const SessionItem* item, QWidget* parent) const
{
    if (!item)
        return nullptr;

    CustomEditor* result(nullptr);

    auto value = item->data(ItemDataRole::DATA);

    if (Utils::IsComboVariant(value))
        result = new ComboPropertyEditor;

    else if (Utils::IsBoolVariant(value))
        result = new BoolEditor;

    else if (Utils::IsColorVariant(value))
        result = new ColorEditor;

    if (result)
        result->setParent(parent);

    return result;
}

//! Returns true if the index data has known (custom) convertion to string.

bool EditorFactory::hasStringRepresentation(const QModelIndex& index)
{
    return !toString(index).empty();
}

//! Provides string representation of index data.

std::string EditorFactory::toString(const QModelIndex& index)
{
    auto variant = index.data();

    if (Utils::IsComboVariant(variant))
        return variant.value<ComboProperty>().label();

    else if (Utils::IsBoolVariant(variant))
        return variant.toBool() ? "True" : "False";

    return {};
}
