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
    EXPECT_EQ(item.binCenters(), std::vector<double>{});
    EXPECT_EQ(item.binValues(), std::vector<double>{});
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

//! Setting dataItem in model context.

TEST_F(TestGraphItem, binCenters)
{
    SessionModel model;
    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType));

    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setFixedBinAxis(3, 0.0, 3.0);
    data_item->setContent(expected_content);

    EXPECT_EQ(graph_item->binValues(), expected_content);
    EXPECT_EQ(graph_item->binCenters(), expected_centers);
}
