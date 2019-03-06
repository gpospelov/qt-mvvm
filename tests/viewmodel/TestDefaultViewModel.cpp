#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "defaultviewmodel.h"
#include "vectoritem.h"
#include <QSignalSpy>
#include <QDebug>

using namespace ModelView;

class TestDefaultViewModel : public ::testing::Test
{
public:
    ~TestDefaultViewModel();
};

TestDefaultViewModel::~TestDefaultViewModel() = default;

TEST_F(TestDefaultViewModel, initialState)
{
    DefaultViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! Single property item in a model.

TEST_F(TestDefaultViewModel, fromPropertyItem)
{
    ToyItems::SampleModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
    EXPECT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
    EXPECT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), propertyItem);
}

//! Find ViewItem's corresponding to given PropertyItem.

TEST_F(TestDefaultViewModel, findPropertyItemView)
{
    ToyItems::SampleModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    auto views = viewModel.findViews(propertyItem);
    EXPECT_EQ(views.size(), 2);
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Checking that view items point to correct SessionItem.

TEST_F(TestDefaultViewModel, fromLayer)
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

//! Constructing ViewModel from single PropertyItem.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(TestDefaultViewModel, propertyItemDataChanged)
{
    ToyItems::SampleModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    // constructing viewModel from sample model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    QModelIndex dataIndex = viewModel.index(0, 1);

    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    propertyItem->setData(50.0, ItemDataRole::DATA);
    EXPECT_EQ(spyDataChanged.count(), 1);

    // dataChanged should report thicknessIndex and two roles
    QList<QVariant> arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex left, QModelIndex right, QVector<int> roles
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), dataIndex);
    EXPECT_EQ(arguments.at(1).value<QModelIndex>(), dataIndex);
    QVector<int> expectedRoles = {Qt::DisplayRole, Qt::EditRole};
    EXPECT_EQ(arguments.at(2).value<QVector<int>>(), expectedRoles);
}

//! Constructing ViewModel from a Layer with one "thickness" property.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(TestDefaultViewModel, layerItemDataChanged)
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

//! Removing single top level item.

TEST_F(TestDefaultViewModel, removeSingleTopItem)
{
    SessionModel model;
    const model_type modelType("abc");

    // inserting single item
    model.insertNewItem(modelType);

    // constructing viewModel from sample model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);

    // removing child
    model.removeItem(model.rootItem(), 0);
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);
}

//! Remove one of two top level items. The pecularity of DefaultViewModel is that it will
//! remove all children of given parent and then recreate missing.

TEST_F(TestDefaultViewModel, removeOneOfTopItems)
{
    SessionModel model;
    const model_type modelType("abc");

    // inserting single item
    model.insertNewItem(modelType);
    model.insertNewItem(modelType);

    // constructing viewModel from sample model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 2);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);

    // removing child
    model.removeItem(model.rootItem(), 0);

    // removal was called once
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // insert was called once to restore missed items
    EXPECT_EQ(spyInsert.count(), 1);

    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0); //
    EXPECT_EQ(arguments.at(2).toInt(), 1); // two children was removed

    arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0); // one child was inserted back.
}

//! Removing single top level item.

TEST_F(TestDefaultViewModel, insertSingleTopItem)
{
    SessionModel model;
    const model_type modelType("abc");

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);

    // inserting single item
    model.insertNewItem(modelType);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // removing child
    model.removeItem(model.rootItem(), 0);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);
}
