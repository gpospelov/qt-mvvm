#ifndef ITEMMOCKWIDGET_H
#define ITEMMOCKWIDGET_H

#include "ItemTestWidget.h"
#include <gmock/gmock.h>

namespace ModelView {
class SessionItem;
class SessionModel;
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

//! Mock class to test ModelMapper functionality.

class MockWidgetForModel : public TestUtils::ModelTestWidgetInterface {
public:
    MockWidgetForModel(ModelView::SessionModel* item);

    void setModel(ModelView::SessionModel* model);

    MOCK_METHOD2(onDataChange, void(ModelView::SessionItem* item, int role));
    MOCK_METHOD2(onRowInserted, void(ModelView::SessionItem* item, int row));
    MOCK_METHOD2(onRowRemoved, void(ModelView::SessionItem* item, int row));

private:
    ModelView::SessionModel* m_model;
};

#endif //  ITEMMOCKWIDGET_H
