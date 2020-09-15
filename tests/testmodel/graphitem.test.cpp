// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MockWidgets.h"
#include "google_test.h"
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/linkeditem.h>
#include <QColor>

using namespace ModelView;
using ::testing::_;

//! Testing GraphItem.

class GraphItemTest : public ::testing::Test
{
public:
    ~GraphItemTest();
};

GraphItemTest::~GraphItemTest() = default;

//! Initial state.

TEST_F(GraphItemTest, initialState)
{
    GraphItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
    EXPECT_EQ(item.binCenters(), std::vector<double>{});
    EXPECT_EQ(item.binValues(), std::vector<double>{});
}

//! Setting dataItem in model context.

TEST_F(GraphItemTest, setDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    graph_item->setDataItem(data_item);

    EXPECT_EQ(graph_item->dataItem(), data_item);
}

//! Setting dataItem in model context.

TEST_F(GraphItemTest, binCenters)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data_item->setContent(expected_content);

    graph_item->setDataItem(data_item);

    EXPECT_EQ(graph_item->binValues(), expected_content);
    EXPECT_EQ(graph_item->binCenters(), expected_centers);
}

//! Check unlinking when nullptr is set as Data1DItem.

TEST_F(GraphItemTest, setNullData)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    // preparing data item
    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data_item->setContent(expected_content);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(graph_item->dataItem(), data_item);

    // setting null as data item
    graph_item->setDataItem(nullptr);
    EXPECT_TRUE(graph_item->dataItem() == nullptr);
    EXPECT_EQ(graph_item->binCenters(), std::vector<double>{});
    EXPECT_EQ(graph_item->binValues(), std::vector<double>{});
}

//! Check signaling on set data item.

TEST_F(GraphItemTest, onSetDataItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    MockWidgetForItem widget(graph_item);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(graph_item, GraphItem::P_LINK)).Times(1);
    EXPECT_CALL(widget, onChildPropertyChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onAboutToRemoveItem(_, _)).Times(0);

    // performing action
    graph_item->setDataItem(data_item);
}

TEST_F(GraphItemTest, setFromGraphItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();
    auto graph_item2 = model.insertItem<GraphItem>();

    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis(FixedBinAxisItem::create(3, 0.0, 3.0));
    data_item->setContent(expected_content);

    graph_item->setDataItem(data_item);
    graph_item->setProperty(GraphItem::P_COLOR, QColor(Qt::red));

    graph_item2->setFromGraphItem(graph_item);

    EXPECT_EQ(graph_item2->binValues(), expected_content);
    EXPECT_EQ(graph_item2->binCenters(), expected_centers);
    EXPECT_EQ(graph_item2->property<QColor>(GraphItem::P_COLOR), QColor(Qt::red));
}
