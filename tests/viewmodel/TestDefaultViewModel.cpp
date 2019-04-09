#include "defaultviewmodel.h"
#include "google_test.h"
#include "sessionmodel.h"
#include "vectoritem.h"
#include "viewitems.h"
#include <QDebug>
#include <QSignalSpy>

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
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), nullptr);
}

//! Single property item in a model.

TEST_F(TestDefaultViewModel, fromPropertyItem)
{
    SessionModel model;
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

//! Single property item in a model.

TEST_F(TestDefaultViewModel, sessionItemFromIndex)
{
    SessionModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
    EXPECT_EQ(viewModel.sessionItemFromIndex(labelIndex), propertyItem);
    EXPECT_EQ(viewModel.sessionItemFromIndex(dataIndex), propertyItem);
}

//! Index from single property item.

TEST_F(TestDefaultViewModel, indexFromSessionItem)
{
    SessionModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    QModelIndexList expected {labelIndex, dataIndex};
    EXPECT_EQ(viewModel.indexOfSessionItem(propertyItem), expected);
}

//! Find ViewItem's corresponding to given PropertyItem.

TEST_F(TestDefaultViewModel, findPropertyItemView)
{
    SessionModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    auto views = viewModel.findViews(propertyItem);
    EXPECT_EQ(views.size(), 2);
}

//! Constructing ViewModel from single PropertyItem.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(TestDefaultViewModel, propertyItemDataChanged)
{
    SessionModel model;
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

//! Inserting single top level item.

TEST_F(TestDefaultViewModel, insertSingleTopItem)
{
    SessionModel model;
    const model_type modelType(Constants::BaseType);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);

    // inserting single item
    model.insertNewItem(modelType);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // removing child
    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);
}

//! Removing single top level item.

TEST_F(TestDefaultViewModel, removeSingleTopItem)
{
    SessionModel model;
    const model_type modelType(Constants::BaseType);

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
    model.removeItem(model.rootItem(), "", 0);
    ASSERT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QList<QVariant> arguments = spyRemove.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).toInt(), 0);
    EXPECT_EQ(arguments.at(2).toInt(), 0);
}

//! Remove one of two top level items. The pecularity of DefaultViewModel is that it will
//! remove all children of given parent and then recreate missing.

TEST_F(TestDefaultViewModel, removeOneOfTopItems)
{
    SessionModel model;
    const model_type modelType(Constants::BaseType);

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
    model.removeItem(model.rootItem(), "", 0);

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

//! Single property item in ViewModel with various appearance flags.

TEST_F(TestDefaultViewModel, propertyItemAppearance)
{
    SessionModel model;

    // default item
    auto item1 = model.insertNewItem(Constants::PropertyType);
    item1->setData(42.0, ItemDataRole::DATA);

    // disabled item
    auto item2 = model.insertNewItem(Constants::PropertyType);
    item2->setData(42.0, ItemDataRole::DATA);
    item2->setEnabled(false);

    // read only item
    auto item3 = model.insertNewItem(Constants::PropertyType);
    item3->setData(42.0, ItemDataRole::DATA);
    item3->setEditable(false);

    // making view model
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    // In tests below is important that SessionItem::isEnabled==false means that item is
    // shown in gray color. While QStandardItem::isEnabled means "no interaction".
    // In our case QStandardItem::isEnabled should be always true.

    // ViewLabel of item1
    EXPECT_FALSE(viewModel.item(0, 0)->isEditable()); // label is always readonly
    EXPECT_TRUE(viewModel.item(0, 0)->isEnabled());   // QStandardItem is always enabled
    // ViewData of item1
    EXPECT_TRUE(viewModel.item(0, 1)->isEditable());
    EXPECT_TRUE(viewModel.item(0, 1)->isEnabled());

    // ViewLabel of item2
    EXPECT_FALSE(viewModel.item(1, 0)->isEditable()); // label is always readonly
    EXPECT_TRUE(viewModel.item(1, 0)->isEnabled());   // QStandardItem is always enabled
    // ViewData of item2
    EXPECT_FALSE(viewModel.item(1, 1)->isEditable());
    EXPECT_TRUE(viewModel.item(1, 1)->isEnabled());

    // ViewLabel of item3
    EXPECT_FALSE(viewModel.item(2, 0)->isEditable()); // label is always readonly
    EXPECT_TRUE(viewModel.item(2, 0)->isEnabled());   // QStandardItem is always enabled
    // ViewData of item3
    EXPECT_FALSE(viewModel.item(2, 1)->isEditable());
    EXPECT_TRUE(viewModel.item(2, 1)->isEnabled());
}

//! Signals in ViewModel when property item changes its appearance.

TEST_F(TestDefaultViewModel, propertyItemAppearanceChanged)
{
    SessionModel model;

    // default item
    auto item = model.insertNewItem(Constants::PropertyType);
    item->setData(42.0, ItemDataRole::DATA);

    // setting up ViewModel and spying it's dataChanged signals
    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    auto labelView = viewModel.item(0, 0);
    auto dataView = viewModel.item(0, 1);
    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    // Changing item appearance
    item->setEnabled(false);
    EXPECT_EQ(spyDataChanged.count(), 2); // change in LabelView and DataView

    // first pack of arguments is related to ViewLabelItem
    QList<QVariant> arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    auto index1 = arguments.at(0).value<QModelIndex>();
    auto index2 = arguments.at(1).value<QModelIndex>();
    auto roles = arguments.at(2).value<QVector<int>>();
    EXPECT_EQ(index1, viewModel.indexFromItem(labelView));
    EXPECT_EQ(index2, viewModel.indexFromItem(labelView));
    QVector<int> expected_roles = {Qt::TextColorRole};
    EXPECT_EQ(roles, expected_roles);

    // second pack of arguments is related to ViewDataItem
    arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    index1 = arguments.at(0).value<QModelIndex>();
    index2 = arguments.at(1).value<QModelIndex>();
    roles = arguments.at(2).value<QVector<int>>();
    EXPECT_EQ(index1, viewModel.indexFromItem(dataView));
    EXPECT_EQ(index2, viewModel.indexFromItem(dataView));
    expected_roles = {Qt::TextColorRole};
    EXPECT_EQ(roles, expected_roles);
}

//! Setting top level item as ROOT item

TEST_F(TestDefaultViewModel, setRootItem)
{
    SessionModel model;
    const model_type modelType(Constants::BaseType);

    DefaultViewModel viewModel;
    auto item = model.insertNewItem(modelType);

    viewModel.setSessionModel(&model);
    viewModel.setRootSessionItem(item);

    // new root item doesn't have children
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);
}
