// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include <QSignalSpy>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of toy MultiLayer in the context of model and viewmodel.

class ToyMultilayerItemTest : public ::testing::Test
{
public:
    ~ToyMultilayerItemTest();
};

ToyMultilayerItemTest::~ToyMultilayerItemTest() = default;

//! Initial state.

TEST_F(ToyMultilayerItemTest, initialState)
{
    ToyItems::MultiLayerItem item;
    EXPECT_FALSE(item.isSinglePropertyTag(ToyItems::MultiLayerItem::T_LAYERS));
}

//! Toy multilayer in a SampleModel.

TEST_F(ToyMultilayerItemTest, multiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayer = model.insertItem<ToyItems::MultiLayerItem>();

    EXPECT_FALSE(multiLayer->data<QVariant>().isValid());
    EXPECT_EQ(multiLayer->displayName(), ToyItems::Constants::MultiLayerItemType);
}

//! Constructing ViewModel from a MultiLayer.
//! Checking that view items point co correct SessionItem.

TEST_F(ToyMultilayerItemTest, multiLayerView)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertItem<ToyItems::MultiLayerItem>();

    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex = viewModel.index(0, 0);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);

    // adding layer
    model.insertItem<ToyItems::LayerItem>(multiLayerItem);
    EXPECT_EQ(viewModel.rowCount(mlIndex), 1);
    EXPECT_EQ(viewModel.columnCount(mlIndex), 2);
}

//! Find ViewItem corresponding to given MultiLayer item.

TEST_F(ToyMultilayerItemTest, findMultiLayerView)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertItem<ToyItems::MultiLayerItem>();

    DefaultViewModel viewModel(&model);

    auto views = viewModel.findViews(multiLayerItem);
    EXPECT_EQ(views.size(), 2);
    EXPECT_EQ(views.at(0)->item(), multiLayerItem);
}

//! How ViewLabelItem sees MultiLayer

TEST_F(ToyMultilayerItemTest, viewItemsForMultiLayer)
{
    ToyItems::SampleModel model;

    auto multiLayer = model.insertItem<ToyItems::MultiLayerItem>();

    ViewLabelItem labelItem(multiLayer);
    EXPECT_EQ(labelItem.data(Qt::DisplayRole).toString().toStdString(),
              ToyItems::Constants::MultiLayerItemType);
}
