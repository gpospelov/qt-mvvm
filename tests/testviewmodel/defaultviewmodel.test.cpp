// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include <QDebug>
#include <QJsonObject>
#include <QSignalSpy>
#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsondocument.h>
#include <mvvm/serialization/jsonitem_types.h>
#include <mvvm/serialization/jsonmodelconverter.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

class DefaultViewModelTest : public FolderBasedTest
{
public:
    DefaultViewModelTest() : FolderBasedTest("test_DefaultViewModel") {}
    ~DefaultViewModelTest();
};

DefaultViewModelTest::~DefaultViewModelTest() = default;

TEST_F(DefaultViewModelTest, initialState)
{
    SessionModel model;
    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
}

//! Single property item in a model.

TEST_F(DefaultViewModelTest, fromPropertyItem)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    // it should be ViewLabelItem looking at our PropertyItem item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), propertyItem);
}

//! Single property item in a model, inserted after DefaultViewModel was setup.

TEST_F(DefaultViewModelTest, initThenInsert)
{
    SessionModel model;
    DefaultViewModel viewModel(&model);

    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    // it should be ViewLabelItem looking at our PropertyItem item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    // Feature: since our PropertyItem got it's value after ViewModel was initialized, the model
    // still holds ViewEmptyItem and not ViewDataItem.
    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
    ASSERT_TRUE(dataItem != nullptr);
}

//! Single property item in a model.

TEST_F(DefaultViewModelTest, sessionItemFromIndex)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    DefaultViewModel viewModel(&model);
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

TEST_F(DefaultViewModelTest, indexFromSessionItem)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    QModelIndexList expected{labelIndex, dataIndex};
    EXPECT_EQ(viewModel.indexOfSessionItem(propertyItem), expected);
}

//! Find ViewItem's corresponding to given PropertyItem.

TEST_F(DefaultViewModelTest, findPropertyItemView)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    DefaultViewModel viewModel(&model);
    auto views = viewModel.findViews(propertyItem);
}

//! Constructing ViewModel from single PropertyItem.
//! Change thickness property in SessionItem, control dataChanged signals from ViewModel.

TEST_F(DefaultViewModelTest, propertyItemDataChanged)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    QModelIndex dataIndex = viewModel.index(0, 1);

    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    propertyItem->setData(50.0);
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

TEST_F(DefaultViewModelTest, insertSingleTopItem)
{
    SessionModel model;
    DefaultViewModel viewModel(&model);

    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);

    // inserting single item
    model.insertItem<SessionItem>();

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // removing child
    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Removing single top level item.

TEST_F(DefaultViewModelTest, removeSingleTopItem)
{
    SessionModel model;

    // inserting single item
    model.insertItem<SessionItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);

    // removing child
    model.removeItem(model.rootItem(), {"", 0});
    ASSERT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    QList<QVariant> arguments = spyRemove.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Remove one of two top level items.

TEST_F(DefaultViewModelTest, removeOneOfTopItems)
{
    SessionModel model;

    // inserting single item
    model.insertItem<SessionItem>();
    model.insertItem<SessionItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child
    EXPECT_EQ(viewModel.rowCount(), 2);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);

    // removing child
    model.removeItem(model.rootItem(), {"", 0});

    // removal was called once
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // no call to insert
    EXPECT_EQ(spyInsert.count(), 0);

    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Single property item in ViewModel with various appearance flags.

TEST_F(DefaultViewModelTest, propertyItemAppearance)
{
    SessionModel model;

    // default item
    auto item1 = model.insertItem<PropertyItem>();
    item1->setData(42.0);

    // disabled item
    auto item2 = model.insertItem<PropertyItem>();
    item2->setData(42.0);
    item2->setEnabled(false); // our convention: gray color, read only

    // read only item
    auto item3 = model.insertItem<PropertyItem>();
    item3->setData(42.0);
    item3->setEditable(false); // our convention: normal color, read only

    // making view model
    DefaultViewModel viewModel(&model);

    // In tests below is important that SessionItem::isEnabled==false means that item is
    // shown in gray color. While QStandardItem::isEnabled means "no interaction".
    // In our case QStandardItem::isEnabled should be always true.

    // ViewLabel and ViewDataItem of item1
    EXPECT_FALSE(viewModel.flags(viewModel.index(0, 0)) & Qt::ItemIsEditable);
    EXPECT_TRUE(viewModel.flags(viewModel.index(0, 1)) & Qt::ItemIsEditable);

    // ViewLabel and ViewDataItem of item2
    EXPECT_FALSE(viewModel.flags(viewModel.index(1, 0)) & Qt::ItemIsEditable);
    EXPECT_FALSE(viewModel.flags(viewModel.index(1, 1)) & Qt::ItemIsEditable);

    // ViewLabel and ViewDataItem of item2
    EXPECT_FALSE(viewModel.flags(viewModel.index(2, 0)) & Qt::ItemIsEditable);
    EXPECT_FALSE(viewModel.flags(viewModel.index(2, 1)) & Qt::ItemIsEditable);
}

//! Signals in ViewModel when property item changes its appearance.

TEST_F(DefaultViewModelTest, propertyItemAppearanceChanged)
{
    SessionModel model;

    // default item
    auto item = model.insertItem<PropertyItem>();
    item->setData(42.0);

    // setting up ViewModel and spying it's dataChanged signals
    DefaultViewModel viewModel(&model);
    auto labelView = viewModel.itemFromIndex(viewModel.index(0, 0));
    auto dataView = viewModel.itemFromIndex(viewModel.index(0, 1));
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QVector<int> expected_roles = {Qt::ForegroundRole};
#else
    QVector<int> expected_roles = {Qt::TextColorRole};
#endif
    EXPECT_EQ(roles, expected_roles);

    // second pack of arguments is related to ViewDataItem
    arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    index1 = arguments.at(0).value<QModelIndex>();
    index2 = arguments.at(1).value<QModelIndex>();
    roles = arguments.at(2).value<QVector<int>>();
    EXPECT_EQ(index1, viewModel.indexFromItem(dataView));
    EXPECT_EQ(index2, viewModel.indexFromItem(dataView));

#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    expected_roles = {Qt::ForegroundRole};
#else
    expected_roles = {Qt::TextColorRole};
#endif

    EXPECT_EQ(roles, expected_roles);
}

//! Signals in ViewModel when property item changes its tooltips.

TEST_F(DefaultViewModelTest, tooltipChanged)
{
    SessionModel model;

    // default item
    auto item = model.insertItem<PropertyItem>();
    item->setData(42.0);
    item->setToolTip("abc");

    // setting up ViewModel and spying it's dataChanged signals
    DefaultViewModel viewModel(&model);
    auto labelView = viewModel.itemFromIndex(viewModel.index(0, 0));
    auto dataView = viewModel.itemFromIndex(viewModel.index(0, 1));

    EXPECT_EQ(viewModel.data(viewModel.index(0, 0), Qt::ToolTipRole).toString(), QString("abc"));
    EXPECT_EQ(viewModel.data(viewModel.index(0, 1), Qt::ToolTipRole).toString(), QString("abc"));

    QSignalSpy spyDataChanged(&viewModel, &DefaultViewModel::dataChanged);

    // Changing tooltip
    item->setToolTip("abc2");
    EXPECT_EQ(spyDataChanged.count(), 2); // change in LabelView and DataView

    // first pack of arguments is related to ViewLabelItem
    QList<QVariant> arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    auto index1 = arguments.at(0).value<QModelIndex>();
    auto index2 = arguments.at(1).value<QModelIndex>();
    auto roles = arguments.at(2).value<QVector<int>>();
    EXPECT_EQ(index1, viewModel.indexFromItem(labelView));
    EXPECT_EQ(index2, viewModel.indexFromItem(labelView));
    QVector<int> expected_roles = {Qt::ToolTipRole};
    EXPECT_EQ(roles, expected_roles);

    // second pack of arguments is related to ViewDataItem
    arguments = spyDataChanged.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    index1 = arguments.at(0).value<QModelIndex>();
    index2 = arguments.at(1).value<QModelIndex>();
    roles = arguments.at(2).value<QVector<int>>();
    EXPECT_EQ(index1, viewModel.indexFromItem(dataView));
    EXPECT_EQ(index2, viewModel.indexFromItem(dataView));

    expected_roles = {Qt::ToolTipRole};
    EXPECT_EQ(roles, expected_roles);
}

//! Setting property item as ROOT item.

TEST_F(DefaultViewModelTest, setPropertyItemAsRoot)
{
    SessionModel model;
    DefaultViewModel viewModel(&model);

    QSignalSpy spyAboutReset(&viewModel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewModel, &DefaultViewModel::modelReset);

    auto item = model.insertItem<PropertyItem>();
    viewModel.setRootSessionItem(item);

    // new root item doesn't have children
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    // attempt to use nullptr as root item
    EXPECT_THROW(viewModel.setRootSessionItem(nullptr), std::runtime_error);

    // attempt to use alien model
    SessionModel model2;
    EXPECT_THROW(viewModel.setRootSessionItem(model2.rootItem()), std::runtime_error);
}

//! Setting property item as ROOT item.
//! Same as above, only view model was initialized after.

TEST_F(DefaultViewModelTest, setPropertyItemAsRootAfter)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    DefaultViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QSignalSpy spyAboutReset(&viewModel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewModel, &DefaultViewModel::modelReset);
    viewModel.setRootSessionItem(item);

    // new root item doesn't have children
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    // attempt to use nullptr as root item
    EXPECT_THROW(viewModel.setRootSessionItem(nullptr), std::runtime_error);

    // attempt to use alien model
    SessionModel model2;
    EXPECT_THROW(viewModel.setRootSessionItem(model2.rootItem()), std::runtime_error);
}

//! Setting top level item as ROOT item (case parent and children).

TEST_F(DefaultViewModelTest, setCompoundAsRootItem)
{
    SessionModel model;
    DefaultViewModel viewModel(&model);

    auto item = model.insertItem<CompoundItem>();
    item->addProperty("thickness", 42.0);
    item->addProperty<VectorItem>("position");
    item->addProperty("radius", 43.0);

    viewModel.setRootSessionItem(item);

    EXPECT_EQ(viewModel.rowCount(), 3);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // checking vector item
    auto index_of_vector_item = viewModel.index(1, 0);
    EXPECT_EQ(viewModel.rowCount(index_of_vector_item), 3);
    EXPECT_EQ(viewModel.columnCount(index_of_vector_item), 2);
}

//! Setting vector item as ROOT item.

TEST_F(DefaultViewModelTest, setVectorItemAsRoot)
{
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();

    DefaultViewModel viewModel(&model);
    viewModel.setRootSessionItem(vectorItem);

    EXPECT_EQ(viewModel.rowCount(), 3);
    EXPECT_EQ(viewModel.columnCount(), 2);
}

//! On model destroyed.

TEST_F(DefaultViewModelTest, onModelReset)
{
    auto model = std::make_unique<SessionModel>();
    model->insertItem<SessionItem>();
    model->insertItem<SessionItem>();
    model->insertItem<SessionItem>();

    DefaultViewModel viewModel(model.get());

    QSignalSpy spyAboutReset(&viewModel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewModel, &DefaultViewModel::modelReset);

    model->clear();
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);
}

//! On model destroyed.

TEST_F(DefaultViewModelTest, onModelDestroyed)
{
    auto model = std::make_unique<SessionModel>();
    model->insertItem<SessionItem>();

    DefaultViewModel viewModel(model.get());
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    model.reset();
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(DefaultViewModelTest, fromVector)
{
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex vectorIndex = viewModel.index(0, 0);

    // it has three rows and two columns, corresponding to our P_X, P_Y, P_Z
    EXPECT_EQ(viewModel.rowCount(vectorIndex), 3);
    EXPECT_EQ(viewModel.columnCount(vectorIndex), 2);

    // ViewLabelItem and ViewDataItem correspondint to P_X
    auto pxLabel =
        dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(0, 0, vectorIndex)));
    auto pxData =
        dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(0, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_X));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_X));

    // ViewLabelItem and ViewDataItem correspondint to P_Y
    pxLabel =
        dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(1, 0, vectorIndex)));
    pxData =
        dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(1, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Y));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Y));

    // ViewLabelItem and ViewDataItem correspondint to P_Z
    pxLabel =
        dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(2, 0, vectorIndex)));
    pxData =
        dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(2, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Z));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Z));
}

TEST_F(DefaultViewModelTest, horizontalLabels)
{
    SessionModel model;
    model.insertItem<VectorItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    EXPECT_EQ(viewModel.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString(), QString("Name"));
    EXPECT_EQ(viewModel.headerData(1, Qt::Horizontal, Qt::DisplayRole).toString(),
              QString("Value"));
}

//! Testing ViewModel signals while loading data with the help of json loader.

TEST_F(DefaultViewModelTest, jsonConverterLoadModel)
{
    JsonModelConverter converter(ConverterMode::project);
    QJsonObject object;

    // preparing jsob object
    {
        SessionModel model("TestModel");
        model.insertItem<PropertyItem>();
        JsonModelConverter converter(ConverterMode::project);
        // writing model to json
        object = converter.to_json(model);
    }

    // loading model
    SessionModel model("TestModel");
    DefaultViewModel viewmodel(&model);
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);

    QSignalSpy spyInsert(&viewmodel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyAboutReset(&viewmodel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewmodel, &DefaultViewModel::modelReset);

    converter.from_json(object, model);

    EXPECT_EQ(spyInsert.count(), 1); // FIXME shouldn't it be '0'?
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);
}

//! Testing ViewModel signals while loading data with the help of json document.
//! Model is empty.

TEST_F(DefaultViewModelTest, jsonDocumentLoadEmptyModel)
{
    auto fileName = TestUtils::TestFileName(testDir(), "jsonDocumentLoadEmptyModel.json");

    // preparing jsob object
    {
        SessionModel model("TestModel");
        JsonDocument document({&model});
        document.save(fileName);
    }

    // loading model
    SessionModel model("TestModel");
    DefaultViewModel viewmodel(&model);
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);

    JsonDocument document({&model});

    QSignalSpy spyInsert(&viewmodel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyAboutReset(&viewmodel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewmodel, &DefaultViewModel::modelReset);

    document.load(fileName);

    EXPECT_EQ(spyInsert.count(), 0);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
}

//! Testing ViewModel signals while loading data with the help of json document.
//! Model is empty.

TEST_F(DefaultViewModelTest, jsonDocumentLoadModel)
{
    auto fileName = TestUtils::TestFileName(testDir(), "jsonDocumentLoadModel.json");

    // preparing jsob object
    {
        SessionModel model("TestModel");
        JsonDocument document({&model});
        model.insertItem<PropertyItem>();
        document.save(fileName);
    }

    // loading model
    SessionModel model("TestModel");
    DefaultViewModel viewmodel(&model);
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);

    JsonDocument document({&model});

    QSignalSpy spyInsert(&viewmodel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyAboutReset(&viewmodel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewmodel, &DefaultViewModel::modelReset);

    document.load(fileName);

    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);
}

//! Testing view model after restoring from json document.

TEST_F(DefaultViewModelTest, vectorItemInJsonDocument)
{
    auto fileName = TestUtils::TestFileName(testDir(), "vectorItemInJsonDocument.json");

    SessionModel model;
    model.insertItem<VectorItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewmodel(&model);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);

    JsonDocument document({&model});
    document.save(fileName);

    // cleaning original model
    model.clear();

    QSignalSpy spyInsert(&viewmodel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyAboutReset(&viewmodel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewmodel, &DefaultViewModel::modelReset);

    document.load(fileName);

    EXPECT_EQ(spyInsert.count(), 4);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);
}

//! Testing view model after restoring from json document.
//! VectorItem is made root item. Test demonstrates that controller is capable
//! to restore old rootSessionItem on onModelReset signal

TEST_F(DefaultViewModelTest, vectorItemAsRootInJsonDocument)
{
    auto fileName = TestUtils::TestFileName(testDir(), "vectorItemAsRootInJsonDocument.json");

    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(vectorItem);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewmodel.rowCount(), 3);
    EXPECT_EQ(viewmodel.columnCount(), 2);
    EXPECT_EQ(viewmodel.rootSessionItem(), vectorItem);

    JsonDocument document({&model});
    document.save(fileName);

    //    model.clear(); // if we uncomment this, information about rootSessionItem will be lost

    QSignalSpy spyInsert(&viewmodel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyAboutReset(&viewmodel, &DefaultViewModel::modelAboutToBeReset);
    QSignalSpy spyReset(&viewmodel, &DefaultViewModel::modelReset);

    document.load(fileName);

    EXPECT_EQ(spyInsert.count(), 3);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 1);
    EXPECT_EQ(spyReset.count(), 1);

    EXPECT_EQ(viewmodel.rootSessionItem(), model.rootItem()->children().at(0)); // vectorItem

    EXPECT_EQ(viewmodel.rowCount(), 3);
    EXPECT_EQ(viewmodel.columnCount(), 2);
}

//! Real life bug. One container with Data1DItem's, one ViewportItem with single graph.
//! DefaultViewModel is looking on ViewPortItem. Graph is deleted first.

TEST_F(DefaultViewModelTest, deleteGraphVromViewport)
{
    SessionModel model;

    // creating data container and single Data1DItem in it
    auto data_container = model.insertItem<ContainerItem>();
    auto data_item = model.insertItem<Data1DItem>(data_container);
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(std::vector<double>({1.0, 2.0, 3.0}));

    // creating Viewport with single graph
    auto viewport_item = model.insertItem<GraphViewportItem>();
    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    graph_item->setDataItem(data_item);

    DefaultViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(viewport_item);

    // validating that we see graph at propeer index
    EXPECT_EQ(viewmodel.rowCount(), 3); // X, Y and Graph
    QModelIndex graph_index = viewmodel.index(2, 0);
    auto graphLabel = dynamic_cast<ViewLabelItem*>(viewmodel.itemFromIndex(graph_index));
    ASSERT_TRUE(graphLabel != nullptr);
    EXPECT_EQ(graphLabel->item(), graph_item);

    // removing graph item
    model.removeItem(graph_item->parent(), graph_item->tagRow());
    EXPECT_EQ(viewmodel.rowCount(), 2); // X, Y

    graph_item = model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(viewmodel.rowCount(), 3); // X, Y
}
