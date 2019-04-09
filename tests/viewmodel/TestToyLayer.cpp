#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "defaultviewmodel.h"
#include "vectoritem.h"
#include <QSignalSpy>
#include <QDebug>

using namespace ModelView;

//! Tests for toy Layer in the context of model and view model.

class TestToyLayer : public ::testing::Test
{
public:
    ~TestToyLayer();
};

TestToyLayer::~TestToyLayer() = default;

//! Toy layer as prodused by toy SampleModel.

TEST_F(TestToyLayer, inModel)
{
    ToyItems::SampleModel model;
    auto layer = model.insertNewItem(ToyItems::Constants::LayerType);

    EXPECT_FALSE(layer->data(ItemDataRole::DATA).isValid());
    EXPECT_EQ(layer->displayName(), ToyItems::Constants::LayerType);
}

TEST_F(TestToyLayer, inViewModel)
{
    ToyItems::SampleModel model;
    auto layerItem = model.insertNewItem(ToyItems::Constants::LayerType);

    // constructing viewModel from sample model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child, item looking at our layerItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex layerIndex = viewModel.index(0, 0);
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(layerIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), layerItem);

    // it has one row and two columns, corresponding to our "thickness" property
    EXPECT_EQ(viewModel.rowCount(layerIndex), 1);
    EXPECT_EQ(viewModel.columnCount(layerIndex), 2);

    // accessing to views representing label and value of thickness property
    QModelIndex thicknessLabelIndex = viewModel.index(0, 0, layerIndex);
    auto thicknessLabelView
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(thicknessLabelIndex));
    EXPECT_TRUE(thicknessLabelView != nullptr);

    QModelIndex thicknessValueIndex = viewModel.index(0, 1, layerIndex);
    auto thicknessValueView
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(thicknessValueIndex));
    EXPECT_TRUE(thicknessValueView != nullptr);

    // internally, views for label and data should point to single SessionItem corresponding to
    // thickness property
    EXPECT_EQ(thicknessLabelView->item(), layerItem->getItem(ToyItems::Layer::P_THICKNESS));
    EXPECT_EQ(thicknessValueView->item(), layerItem->getItem(ToyItems::Layer::P_THICKNESS));
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(TestToyLayer, layerItemDataChanged)
{
    ToyItems::SampleModel model;
    auto layerItem = dynamic_cast<CompoundItem*>(model.insertNewItem(ToyItems::Constants::LayerType));

    // constructing viewModel from sample model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    QModelIndex layerIndex = viewModel.index(0, 0);
    QModelIndex thicknessIndex = viewModel.index(0, 1, layerIndex);

    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    layerItem->setItemValue(ToyItems::Layer::P_THICKNESS, 50.0);
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

TEST_F(TestToyLayer, displayNameInMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayer = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    auto layer0 = model.insertNewItem(ToyItems::Constants::LayerType, multiLayer);
    EXPECT_EQ(layer0->displayName(), "Layer");

    auto layer1 = model.insertNewItem(ToyItems::Constants::LayerType, multiLayer);
    EXPECT_EQ(layer0->displayName(), "Layer0");
    EXPECT_EQ(layer1->displayName(), "Layer1");
}

//! LayerItem as rootItem.

TEST_F(TestToyLayer, setRootItemContext)
{
    ToyItems::SampleModel model;
    auto layer = model.insertNewItem(ToyItems::Constants::LayerType);
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    viewModel.setRootSessionItem(layer);

    EXPECT_EQ(viewModel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewModel.columnCount(QModelIndex()), 2);

    // index of item representing thickness
    QModelIndex thicknessIndex = viewModel.index(0, 0, QModelIndex());
    EXPECT_EQ(viewModel.sessionItemFromIndex(thicknessIndex), layer->getItem(ToyItems::Layer::P_THICKNESS));
}
