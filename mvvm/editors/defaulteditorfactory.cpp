// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaulteditorfactory.h"
#include "customvariants.h"
#include "comboproperty.h"
#include "combopropertyeditor.h"
#include "sessionitem.h"
#include "viewitem.h"
#include "abstractviewmodel.h"
#include "booleditor.h"
#include "coloreditor.h"
#include "externalpropertyeditor.h"
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

DefaultEditorFactory::DefaultEditorFactory() {}

CustomEditor* DefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    CustomEditor* result(nullptr);

    if (auto item = itemFromIndex(index))
        return createEditor(item);

    return result;
}

CustomEditor* DefaultEditorFactory::createEditor(const SessionItem* item) const
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

    else if (Utils::IsExtPropertyVariant(value))
        result = new ExternalPropertyEditor;

    return result;
}
