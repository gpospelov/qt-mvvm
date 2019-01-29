// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMTESTWIDGET_H
#define ITEMTESTWIDGET_H

//! Various common utils for unit tests.

namespace ModelView {
class SessionItem;
}

namespace TestUtils
{

//! Interface for testing callbacks comming from SessionItem within gmock framework.

class ItemTestWidgetInterface {
public:
    virtual ~ItemTestWidgetInterface() = default;

    virtual void onItemDestroy(ModelView::SessionItem* item) = 0;
    virtual void onDataChange(ModelView::SessionItem* item, int role) = 0;

};

//! Connects all callbacks between testing class and SessionItem.
void ConnectItemWidget(ItemTestWidgetInterface* widget, ModelView::SessionItem* item);

} // TestUtils

#endif // ITEMTESTWIDGET_H
