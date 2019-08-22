#include "google_test.h"
#include "graphitem.h"
#include "sessionmodel.h"
#include "data1ditem.h"

using namespace ModelView;

//! Testing GraphItem.

class TestGraphItem : public ::testing::Test
{
public:
    ~TestGraphItem();
};

TestGraphItem::~TestGraphItem() = default;

//! Initial state.

TEST_F(TestGraphItem, initialState)
{
    GraphItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
}

//! Setting dataItem in model context.

TEST_F(TestGraphItem, setDataItem)
{
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));

    graph_item->setDataItem(data_item);

    EXPECT_EQ(graph_item->dataItem(), data_item);
}
