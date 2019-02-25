#include "google_test.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "MockWidgets.h"

using namespace ModelView;
using ::testing::_;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

//! Check that mapper works only in model context.

TEST(TestItemMapper, initialState)
{
    // item outside model context can't have a mapper
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    EXPECT_THROW(item->mapper(), std::runtime_error);

    // item in model context does have a mapper
    SessionModel model;
    auto item2 = model.insertNewItem("parent", model.rootItem(), 0, "");
    EXPECT_NO_THROW(item2->mapper());
}

//! Setting data to item, expecting onDataChange callback.

TEST(TestItemMapper, onDataChange)
{
    SessionModel model;
    auto item = model.insertNewItem("parent", model.rootItem(), 0, "");

    MockWidgetForItem widget(item);

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = item;
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

    // perform action
    item->setData(42.0, ItemDataRole::DATA);
}
