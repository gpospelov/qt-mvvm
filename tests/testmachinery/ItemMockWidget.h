#ifndef ITEMMOCKWIDGET_H
#define ITEMMOCKWIDGET_H

#include "ItemTestWidget.h"
#include <gmock/gmock.h>

namespace ModelView {
class SessionItem;
}

//! Mock class to test ItemMapper functionality.

class MockWidget : public TestUtils::ItemTestWidgetInterface {
public:
    MockWidget(ModelView::SessionItem* item);
    ~MockWidget();

    void setItem(ModelView::SessionItem* item);

    MOCK_METHOD1(onItemDestroy, void(ModelView::SessionItem* item));
    MOCK_METHOD2(onDataChange, void(ModelView::SessionItem* item, int role));

private:
    ModelView::SessionItem* m_item;
};

#endif //  ITEMMOCKWIDGET_H
