#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "defaultviewmodel.h"
#include "viewmodelutils.h"
#include <QSignalSpy>

using namespace ModelView;

//! Tests of toy MultiLayer in the context of model and viewmodel.

class TestToyMultilayerItem : public ::testing::Test
{
public:
    ~TestToyMultilayerItem();
};

TestToyMultilayerItem::~TestToyMultilayerItem() = default;

//! Toy multilayer as produced bo toy SampleModel.

TEST_F(TestToyMultilayerItem, multiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayer = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    EXPECT_FALSE(multiLayer->data().isValid());
    EXPECT_EQ(multiLayer->displayName(), ToyItems::Constants::MultiLayerType);
}

//! Constructing ViewModel from a MultiLayer.
//! Checking that view items point co correct SessionItem.

TEST_F(TestToyMultilayerItem, multiLayerView)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex = viewModel.index(0, 0);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);
}

//! Find ViewItem corresponding to given MultiLayer item.

TEST_F(TestToyMultilayerItem, findMultiLayerView)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    DefaultViewModel viewModel(&model);

    auto views = Utils::findViews(&viewModel, multiLayerItem);
    EXPECT_EQ(views.size(), 1);
    EXPECT_EQ(views.at(0)->item(), multiLayerItem);
}

//! How ViewLabelItem sees MultiLayer

TEST_F(TestToyMultilayerItem, viewItemsForMultiLayer)
{
    ToyItems::SampleModel model;

    auto multiLayer = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ViewLabelItem labelItem(multiLayer);
    EXPECT_EQ(labelItem.data(Qt::DisplayRole).toString().toStdString(),
              ToyItems::Constants::MultiLayerType);
}
