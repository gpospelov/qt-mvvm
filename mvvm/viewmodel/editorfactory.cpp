// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorfactory.h"
#include "viewitem.h"
#include "viewmodel.h"
#include "comboproperty.h"
#include "combopropertyeditor.h"
#include "sessionitem.h"
#include <QModelIndex>
#include <QDebug>

using namespace ModelView;

namespace {

const SessionItem* itemFromIndex(const QModelIndex& index) {
    auto model = dynamic_cast<const ViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

}

EditorFactory::EditorFactory()
{

}

QWidget* EditorFactory::createEditor(const QModelIndex& index) const
{
    QWidget* result(nullptr);

    if (auto item = itemFromIndex(index))
        return createEditor(item);

    return result;
}

QWidget* EditorFactory::createEditor(const SessionItem* item) const
{
    if (!item)
        return nullptr;

    QWidget* result(nullptr);

    if (isComboProperty(item->data(ItemDataRole::DATA))) {
        auto editor = new ComboPropertyEditor;
        result = editor;
        qDebug() << "EditorFactory::createEditor():" << item << editor;
    }

    return result;
}
