#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "obsoleteviewmodel.h"
#include "vectoritem.h"
#include <QSignalSpy>
#include <QDebug>

using namespace ModelView;

class TestObsoleteViewModel : public ::testing::Test
{
public:
    ~TestObsoleteViewModel();
};

TestObsoleteViewModel::~TestObsoleteViewModel() = default;

TEST_F(TestObsoleteViewModel, initialState)
{
    ObsoleteViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! Constructing ViewModel from a MultiLayer.
//! Checking that view items point co correct SessionItem.

TEST_F(TestObsoleteViewModel, fromMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex = viewModel.index(0, 0);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Checking that view items point to correct SessionItem.

TEST_F(TestObsoleteViewModel, fromLayer)
{
    ToyItems::SampleModel model;
    auto layerItem = model.insertNewItem(ToyItems::Constants::LayerType);

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
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

//! Constructing ViewModel from a VectorItem.
//! Checking that view items point to correct SessionItem.

TEST_F(TestObsoleteViewModel, fromVector)
{
    ToyItems::SampleModel model;
    auto vectorItem = model.insertNewItem(Constants::VectorType);

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex vectorIndex = viewModel.index(0, 0);

    // it has three rows and two columns, corresponding to our P_X, P_Y, P_Z
    EXPECT_EQ(viewModel.rowCount(vectorIndex), 3);
    EXPECT_EQ(viewModel.columnCount(vectorIndex), 2);

    // ViewLabelItem and ViewDataItem correspondint to P_X
    auto pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(0, 0, vectorIndex)));
    auto pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(0, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_X));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_X));

    // ViewLabelItem and ViewDataItem correspondint to P_Y
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(1, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(1, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Y));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Y));

    // ViewLabelItem and ViewDataItem correspondint to P_Z
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(2, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(2, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Z));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Z));
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Change thickness property in SessionItem, control itemChanged signals from ViewModel.

TEST_F(TestObsoleteViewModel, itemChanged)
{
    ToyItems::SampleModel model;
    auto layerItem = dynamic_cast<CompoundItem*>(model.insertNewItem(ToyItems::Constants::LayerType));

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);

    QSignalSpy spyDataChanged(&viewModel, &ObsoleteViewModel::itemChanged);

    layerItem->setItemValue(ToyItems::Layer::P_THICKNESS, 50.0);
    EXPECT_EQ(spyDataChanged.count(), 1);
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(TestObsoleteViewModel, dataChanged)
{
    ToyItems::SampleModel model;
    auto layerItem = dynamic_cast<CompoundItem*>(model.insertNewItem(ToyItems::Constants::LayerType));

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);

    QModelIndex layerIndex = viewModel.index(0, 0);
    QModelIndex thicknessIndex = viewModel.index(0, 1, layerIndex);

    QSignalSpy spyDataChanged(&viewModel, &ObsoleteViewModel::dataChanged);

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

//! Inserting item in parent

TEST_F(TestObsoleteViewModel, insertItem)
{
    SessionModel model;
    const model_type modelType("abc");

    // inserting single item
    auto parent = model.insertNewItem(modelType);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // parent item should have no children
    QModelIndex parentIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.rowCount(parentIndex), 0);
    EXPECT_EQ(viewModel.columnCount(parentIndex), 0);

    QSignalSpy spyInsert(&viewModel, &ObsoleteViewModel::rowsInserted);

    // adding child
    model.insertNewItem(modelType, parent);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(viewModel.rowCount(parentIndex), 1);
    EXPECT_EQ(viewModel.columnCount(parentIndex), 1); // inserted item has no data

    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), parentIndex);
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);

    // appending second child
    model.insertNewItem(modelType, parent);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(viewModel.rowCount(parentIndex), 2);
    EXPECT_EQ(viewModel.columnCount(parentIndex), 1); // inserted item has no data
    arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), parentIndex);
    EXPECT_EQ(arguments.at(1).toInt(), 1);
    EXPECT_EQ(arguments.at(2).toInt(), 1);
}

//! Removing item from parent

TEST_F(TestObsoleteViewModel, removeRow)
{
    SessionModel model;
    const model_type modelType("abc");

    // inserting single item
    auto parent = model.insertNewItem(modelType);
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);
    model.insertNewItem(modelType, parent);

    // constructing viewModel from sample model
    ObsoleteViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // parent item should have no children
    QModelIndex parentIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.rowCount(parentIndex), 1);
    EXPECT_EQ(viewModel.columnCount(parentIndex), 1); // no data in item

    QSignalSpy spyRemove(&viewModel, &ObsoleteViewModel::rowsRemoved);

    // removing child
    model.removeItem(parent, 0);
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(parentIndex), 0);
    EXPECT_EQ(viewModel.columnCount(parentIndex), 1); // for some reason child removal doesn't affect column

    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), parentIndex);
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);
}
