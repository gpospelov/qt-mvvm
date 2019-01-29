// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ItemTestWidget.h"
#include "sessionitem.h"
#include "itemmapper.h"

using namespace TestUtils;

void ConnectItemWidget(ItemTestWidgetInterface* widget, ModelView::SessionItem* item)
{
    item->mapper()->setOnItemDestroy([widget](ModelView::SessionItem* item) {
        widget->onItemDestroy(item);
    });

    item->mapper()->setOnDataChange([widget](ModelView::SessionItem* item, int role) {
        widget->onDataChange(item, role);
    });
}
