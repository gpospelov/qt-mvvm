#include "google_test.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "modelmapper.h"
#include "ItemMockWidget.h"

using namespace ModelView;
using ::testing::_;

class TestModelMapper : public ::testing::Test
{
public:
    ~TestModelMapper();
};

TestModelMapper::~TestModelMapper() = default;

//! Setting item data and checking corresponding signal.

TEST(TestModelMapper, onDataChange)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    auto item = model.insertNewItem("parent", model.rootItem(), 0, "");

    // expecting signal to be called once
    const int role = ItemDataRole::DATA;
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting same data shouldn't trigger the signal
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting new data through item
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    item->setData(43.0, ItemDataRole::DATA); // perform action
}
