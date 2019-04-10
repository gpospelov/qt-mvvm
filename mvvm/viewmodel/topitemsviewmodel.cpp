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

using namespace ModelView;

TopItemsViewModel::TopItemsViewModel(QObject* parent) : DefaultViewModel(parent)
{

}

std::vector<SessionItem*> TopItemsViewModel::item_children(const SessionItem* item) const
{
    return item->children();
}
