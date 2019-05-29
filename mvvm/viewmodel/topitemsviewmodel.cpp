// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "topitemsviewmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include "childrenstrategies.h"

using namespace ModelView;

TopItemsViewModel::TopItemsViewModel(SessionModel* model, QObject* parent) : DefaultViewModel(model, parent)
{
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}
