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
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>

using namespace ModelView;

//! Tests for toy Layer in the context of model and view model.

class ToyLayerItemTest : public ::testing::Test
{
public:
    ~ToyLayerItemTest();
};

ToyLayerItemTest::~ToyLayerItemTest() = default;

//! Initial state.

TEST_F(ToyLayerItemTest, initialState)
{
    ToyItems::LayerItem item;
    EXPECT_TRUE(item.isSinglePropertyTag(ToyItems::LayerItem::P_THICKNESS));
    EXPECT_TRUE(item.isSinglePropertyTag(ToyItems::LayerItem::P_COLOR));
    EXPECT_FALSE(item.isSinglePropertyTag(ToyItems::LayerItem::T_PARTICLES));
}

//! Toy layer as prodused by toy SampleModel.

TEST_F(ToyLayerItemTest, inModel)
{
    ToyItems::SampleModel model;
    auto layer = model.insertItem<ToyItems::LayerItem>();

    EXPECT_FALSE(layer->data<QVariant>().isValid());
    EXPECT_EQ(layer->displayName(), ToyItems::Constants::LayerItemType);
}

TEST_F(ToyLayerItemTest, inViewModel)
{
    ToyItems::SampleModel model;
    auto layerItem = model.insertItem<ToyItems::LayerItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child, item looking at our layerItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex layerIndex = viewModel.index(0, 0);
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(layerIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), layerItem);

    // it has two rows and two columns, corresponding to our "thickness" and "color" properties
    EXPECT_EQ(viewModel.rowCount(layerIndex), 2);
    EXPECT_EQ(viewModel.columnCount(layerIndex), 2);

    // accessing to views representing label and value of thickness property
    QModelIndex thicknessLabelIndex = viewModel.index(0, 0, layerIndex);
    auto thicknessLabelView =
        dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(thicknessLabelIndex));
    EXPECT_TRUE(thicknessLabelView != nullptr);

    QModelIndex thicknessValueIndex = viewModel.index(0, 1, layerIndex);
    auto thicknessValueView =
        dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(thicknessValueIndex));
    EXPECT_TRUE(thicknessValueView != nullptr);

    // internally, views for label and data should point to single SessionItem corresponding to
    // thickness property
    EXPECT_EQ(thicknessLabelView->item(), layerItem->getItem(ToyItems::LayerItem::P_THICKNESS));
    EXPECT_EQ(thicknessValueView->item(), layerItem->getItem(ToyItems::LayerItem::P_THICKNESS));
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(ToyLayerItemTest, layerItemDataChanged)
{
    ToyItems::SampleModel model;
    auto layerItem = model.insertItem<ToyItems::LayerItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    QModelIndex layerIndex = viewModel.index(0, 0);
    QModelIndex thicknessIndex = viewModel.index(0, 1, layerIndex);

    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    layerItem->setProperty(ToyItems::LayerItem::P_THICKNESS, 50.0);
    EXPECT_EQ(spyDataChanged.count(), 1);

    // dataChanged should report thicknessIndex and two roles
    QList<QVariant> arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex left, QModelIndex right, QVector<int> roles
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), thicknessIndex);
    EXPECT_EQ(arguments.at(1).value<QModelIndex>(), thicknessIndex);
    QVector<int> expectedRoles = {Qt::DisplayRole, Qt::EditRole};
    EXPECT_EQ(arguments.at(2).value<QVector<int>>(), expectedRoles);
}

//! Validates display name

TEST_F(ToyLayerItemTest, displayNameInMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayer = model.insertItem<ToyItems::MultiLayerItem>();

    auto layer0 = model.insertItem<ToyItems::LayerItem>(multiLayer);
    EXPECT_EQ(layer0->displayName(), "Layer");

    auto layer1 = model.insertItem<ToyItems::LayerItem>(multiLayer);
    EXPECT_EQ(layer0->displayName(), "Layer0");
    EXPECT_EQ(layer1->displayName(), "Layer1");
}

//! LayerItem as rootItem.

TEST_F(ToyLayerItemTest, setRootItemContext)
{
    ToyItems::SampleModel model;
    auto layer = model.insertItem<ToyItems::LayerItem>();
    DefaultViewModel viewModel(&model);
    viewModel.setRootSessionItem(layer);

    EXPECT_EQ(viewModel.rowCount(QModelIndex()), 2);
    EXPECT_EQ(viewModel.columnCount(QModelIndex()), 2);

    // index of item representing thickness
    QModelIndex thicknessIndex = viewModel.index(0, 0, QModelIndex());
    EXPECT_EQ(viewModel.sessionItemFromIndex(thicknessIndex),
              layer->getItem(ToyItems::LayerItem::P_THICKNESS));
}
