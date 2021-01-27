// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/graphitem.h"

#include "google_test.h"
#include "mockwidgets.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/plottableitems.h"
#include <QColor>

using namespace ModelView;
using ::testing::_;

//! Testing GraphItem.

class GraphItemTest : public ::testing::Test {
};

//! Initial state.

TEST_F(GraphItemTest, initialState)
{
    GraphItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
    EXPECT_EQ(item.binCenters(), std::vector<double>{});
    EXPECT_EQ(item.binValues(), std::vector<double>{});
    EXPECT_EQ(item.binErrors(), std::vector<double>{});
    EXPECT_EQ(item.colorName(), std::string("#000000"));
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

TEST_F(GraphItemTest, binValues)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    std::vector<double> expected_values = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);

    EXPECT_EQ(graph_item->binValues(), expected_values);
    EXPECT_EQ(graph_item->binCenters(), expected_centers);
}

//! Setting dataItem with errors

TEST_F(GraphItemTest, binErrors)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    std::vector<double> expected_values = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    std::vector<double> expected_errors = {0.1, 0.2, 0.3};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);
    data_item->setErrors(expected_errors);

    graph_item->setDataItem(data_item);

    EXPECT_EQ(graph_item->binValues(), expected_values);
    EXPECT_EQ(graph_item->binCenters(), expected_centers);
    EXPECT_EQ(graph_item->binErrors(), expected_errors);
}

//! Check unlinking when nullptr is set as Data1DItem.

TEST_F(GraphItemTest, setNullData)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();

    // preparing data item
    std::vector<double> expected_values = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(graph_item->dataItem(), data_item);

    // setting null as data item
    graph_item->setDataItem(nullptr);
    EXPECT_TRUE(graph_item->dataItem() == nullptr);
    EXPECT_EQ(graph_item->binCenters(), std::vector<double>{});
    EXPECT_EQ(graph_item->binValues(), std::vector<double>{});
    EXPECT_EQ(graph_item->binErrors(), std::vector<double>{});
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

//! Sets GraphItem from another GraphItem

TEST_F(GraphItemTest, setFromGraphItem)
{
    SessionModel model;
    auto data_item = model.insertItem<Data1DItem>();
    auto graph_item = model.insertItem<GraphItem>();
    auto graph_item2 = model.insertItem<GraphItem>();

    std::vector<double> expected_values = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);
    graph_item->penItem()->setProperty(PenItem::P_COLOR, QColor(Qt::red));

    graph_item2->setFromGraphItem(graph_item);

    EXPECT_EQ(graph_item2->binValues(), expected_values);
    EXPECT_EQ(graph_item2->binCenters(), expected_centers);
    EXPECT_EQ(graph_item2->penItem()->property<QColor>(PenItem::P_COLOR), QColor(Qt::red));
}

TEST_F(GraphItemTest, penItem_setNamedColor)
{
    GraphItem item;
    item.setNamedColor("mediumaquamarine");
    EXPECT_EQ(item.colorName(), std::string("#66cdaa"));
}
