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

#include <string>

//! Various common utils for unit tests.

namespace ModelView {
class SessionItem;
}

//! Interface for testing callbacks comming from SessionItem within gmock framework.

class ItemTestWidgetInterface {
public:
    virtual ~ItemTestWidgetInterface();

    virtual void onItemDestroy(ModelView::SessionItem* item) = 0;
    virtual void onDataChange(ModelView::SessionItem* item, int role) = 0;
    virtual void onPropertyChange(ModelView::SessionItem* item, std::string name) = 0;
};

//! Interface for testing callbacks comming from SessionModel within gmock framework.

class ModelTestWidgetInterface {
public:
    virtual ~ModelTestWidgetInterface();

    virtual void onDataChange(ModelView::SessionItem* item, int role) = 0;
    virtual void onRowInserted(ModelView::SessionItem* item, int row) = 0;
    virtual void onRowRemoved(ModelView::SessionItem* item, int row) = 0;
};

#endif // ITEMTESTWIDGET_H
