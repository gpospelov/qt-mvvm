// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QDebug>
#include <QJsonObject>
#include <mvvm/serialization/jsonmodelconverter.h>
#include <mvvm/standarditems/standarditemincludes.h>
#include <mvvm/model/modelutils.h>

using namespace ModelView;

//! Testing serialization of ToyItems using json converters.

class StandardItemsSerializationTest : public ::testing::Test
{
public:
    ~StandardItemsSerializationTest();
};

StandardItemsSerializationTest::~StandardItemsSerializationTest() = default;

//! Checking that serialization works (not crashing) for all defined standard items.

TEST_F(StandardItemsSerializationTest, allItems)
{
    SessionModel model;
    model.insertItem<ColorMapItem>();
    model.insertItem<ColorMapViewportItem>();
    model.insertItem<CompoundItem>();
    model.insertItem<ContainerItem>();
    model.insertItem<Data1DItem>();
    model.insertItem<Data2DItem>();
    model.insertItem<FixedBinAxisItem>();
    model.insertItem<GraphItem>();
    model.insertItem<GraphViewportItem>();
    model.insertItem<LinkedItem>();
    model.insertItem<PenItem>();
    model.insertItem<PointwiseAxisItem>();
    model.insertItem<PropertyItem>();
    model.insertItem<SessionItem>();
    model.insertItem<TextItem>();
    model.insertItem<VectorItem>();
    model.insertItem<ViewportAxisItem>();

    auto modelCopy = Utils::CreateCopy(model);
    EXPECT_EQ(model.rootItem()->childrenCount(), modelCopy->rootItem()->childrenCount());
}

//! Creating graph with data. It has to be identical after serialization.

TEST_F(StandardItemsSerializationTest, GraphItemAndDataSerialization)
{
    // preparing model, data item and graph pointing to it
    SessionModel model;
    auto graph_item = model.insertItem<GraphItem>();
    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);
    graph_item->setDataItem(data_item);

    // accessing copied items
    auto modelCopy = Utils::CreateCopy(model);
    EXPECT_EQ(model.rootItem()->childrenCount(), modelCopy->rootItem()->childrenCount());

    auto graphCopy = modelCopy->topItem<GraphItem>();
    auto dataCopy = modelCopy->topItem<Data1DItem>();

    // analyzing copies
    EXPECT_EQ(graphCopy->dataItem(), dataCopy);
    EXPECT_EQ(dataCopy->binCenters(), expected_centers);
    EXPECT_EQ(dataCopy->binValues(), expected_values);
}

//! Creating viewport with one graph. Serializing and restoring the model.

TEST_F(StandardItemsSerializationTest, graphViewPortItemSerialization)
{
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    auto data_item = model.insertItem<Data1DItem>();

    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    graph_item->setDataItem(data_item);
    EXPECT_EQ(viewport_item->graphItems().size(), 1);

    // updating viewport to graph
    viewport_item->setViewportToContent();

    // accessing copied items
    auto modelCopy = Utils::CreateCopy(model);
    EXPECT_EQ(model.rootItem()->childrenCount(), modelCopy->rootItem()->childrenCount());
    auto viewportCopy = modelCopy->topItem<GraphViewportItem>();
    ASSERT_EQ(viewportCopy->graphItems().size(), 1);
    auto graphCopy = viewportCopy->graphItems().at(0);
    auto dataCopy = modelCopy->topItem<Data1DItem>();

    // analyzing copies
    EXPECT_EQ(graphCopy->dataItem(), dataCopy);
    EXPECT_EQ(graphCopy->dataItem(), dataCopy);
    EXPECT_EQ(dataCopy->binCenters(), expected_centers);
    EXPECT_EQ(dataCopy->binValues(), expected_values);

    EXPECT_DOUBLE_EQ(viewportCopy->xAxis()->property<double>(ViewportAxisItem::P_MIN),
                     expected_centers[0]);
    EXPECT_DOUBLE_EQ(viewportCopy->xAxis()->property<double>(ViewportAxisItem::P_MAX),
                     expected_centers[2]);
}
