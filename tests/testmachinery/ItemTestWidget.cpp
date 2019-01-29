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
#include <QDebug>

void TestUtils::ConnectItemWidget(TestUtils::ItemTestWidgetInterface* widget, ModelView::SessionItem* item)
{
    item->mapper()->setOnItemDestroy([widget](ModelView::SessionItem* item) {
        qDebug() << "in ConnectitemWidget";
        widget->onItemDestroy(item);
    }, widget);

    item->mapper()->setOnDataChange([widget](ModelView::SessionItem* item, int role) {
        widget->onDataChange(item, role);
    }, widget);
}
