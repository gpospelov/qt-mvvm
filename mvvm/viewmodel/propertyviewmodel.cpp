// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyviewmodel.h"
#include "groupitem.h"
#include "childrenstrategies.h"
#include "labeldatarowconstructor.h"
#include "propertyviewmodelcontroller.h"

using namespace ModelView;

PropertyViewModel::PropertyViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<PropertyViewModelController>(this), parent)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
    setSessionModel(model);
}
