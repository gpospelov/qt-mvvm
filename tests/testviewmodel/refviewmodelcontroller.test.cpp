// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QSignalSpy>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>

using namespace ModelView;

//! Tests of RefViewModelController class.

class RefViewModelControllerTest : public ::testing::Test
{
public:
    ~RefViewModelControllerTest();

    auto create_controller(SessionModel* session_model, RefViewModel* view_model)
    {
        auto result = std::make_unique<RefViewModelController>(session_model, view_model);
        result->setRowStrategy(std::make_unique<LabelDataRowStrategy>());
        result->setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
        result->init();
        return result;
    }
};

RefViewModelControllerTest::~RefViewModelControllerTest() = default;

//! Initial state of the controller. Empty SessionModel, empty ViewModel.

TEST_F(RefViewModelControllerTest, initialState)
{
    SessionModel session_model;
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(controller->sessionModel(), &session_model);
    EXPECT_EQ(controller->rootSessionItem(), session_model.rootItem());
    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(view_model.rowCount(), 0);
}

//! Single property item in a model.

TEST_F(RefViewModelControllerTest, fromPropertyItem)
{
    SessionModel session_model;
    auto propertyItem = session_model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = view_model.index(0, 0);
    QModelIndex dataIndex = view_model.index(0, 1);

    // it should be ViewLabelItem and ViewDataItem looking at our PropertyItem item
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item_role(), ItemDataRole::DISPLAY);
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item(), propertyItem);
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item_role(), ItemDataRole::DATA);
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item(), propertyItem);
}

//! VectorItem in a model.

TEST_F(RefViewModelControllerTest, fromVectorItem)
{
    SessionModel session_model;
    auto vectorItem = session_model.insertItem<VectorItem>();

    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex vectorLabelIndex = view_model.index(0, 0);
    QModelIndex vectorDataIndex = view_model.index(0, 1);

    // it should be ViewLabelItem and ViewDataItem looking at our VectorItem item
    EXPECT_EQ(view_model.itemFromIndex(vectorLabelIndex)->item_role(), ItemDataRole::DISPLAY);
    EXPECT_EQ(view_model.itemFromIndex(vectorLabelIndex)->item(), vectorItem);
    EXPECT_EQ(view_model.itemFromIndex(vectorDataIndex)->item_role(), ItemDataRole::DATA);
    EXPECT_EQ(view_model.itemFromIndex(vectorDataIndex)->item(), vectorItem);

    // checking X, Y, Z
    std::vector<SessionItem*> children = vectorItem->children();
    for (int row = 0; row < 3; ++row) { // x, y, z
        QModelIndex x_labelIndex = view_model.index(row, 0, vectorLabelIndex);
        QModelIndex x_dataIndex = view_model.index(row, 1, vectorLabelIndex);
        EXPECT_EQ(view_model.itemFromIndex(x_labelIndex)->item_role(), ItemDataRole::DISPLAY);
        EXPECT_EQ(view_model.itemFromIndex(x_labelIndex)->item(),
                  children[static_cast<size_t>(row)]);
        EXPECT_EQ(view_model.itemFromIndex(x_dataIndex)->item_role(), ItemDataRole::DATA);
        EXPECT_EQ(view_model.itemFromIndex(x_dataIndex)->item(),
                  children[static_cast<size_t>(row)]);
    }
}

//! Single property item in a model, inserted after controller was setup.

TEST_F(RefViewModelControllerTest, initThenInsertProperty)
{
    SessionModel session_model;

    RefViewModel view_model;
    QSignalSpy spyInsert(&view_model, &RefViewModel::rowsInserted);
    QSignalSpy spyRemove(&view_model, &RefViewModel::rowsRemoved);

    auto controller = create_controller(&session_model, &view_model);
    auto propertyItem = session_model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    // checking signaling
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(spyRemove.count(), 0);
    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    // checking model layout
    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = view_model.index(0, 0);
    QModelIndex dataIndex = view_model.index(0, 1);

    // it should be ViewLabelItem and ViewDataItem looking at our PropertyItem item
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item_role(), ItemDataRole::DISPLAY);
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item(), propertyItem);
    // Feature: since our PropertyItem got it's value after ViewModel was initialized, the model
    // still holds ViewEmptyItem and not ViewDataItem.
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item_role(), 0);
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item(), nullptr);
}

//! Insert two property items in a model, inserted after controller was setup.

TEST_F(RefViewModelControllerTest, initThenInsertProperties)
{
    SessionModel session_model;

    RefViewModel view_model;
    QSignalSpy spyInsert(&view_model, &RefViewModel::rowsInserted);
    QSignalSpy spyRemove(&view_model, &RefViewModel::rowsRemoved);

    auto controller = create_controller(&session_model, &view_model);
    session_model.insertItem<PropertyItem>();
    session_model.insertItem<PropertyItem>();

    // checking signaling
    EXPECT_EQ(spyInsert.count(), 2);

    // checking model layout
    EXPECT_EQ(view_model.rowCount(), 2);
    EXPECT_EQ(view_model.columnCount(), 2);
}

//! Insert two property items in a model, inserted after controller was setup.

TEST_F(RefViewModelControllerTest, initThenInsertVector)
{
    SessionModel session_model;

    RefViewModel view_model;
    QSignalSpy spyInsert(&view_model, &RefViewModel::rowsInserted);
    QSignalSpy spyRemove(&view_model, &RefViewModel::rowsRemoved);

    auto controller = create_controller(&session_model, &view_model);
    session_model.insertItem<VectorItem>();
    session_model.insertItem<VectorItem>();

    // checking signaling
    EXPECT_EQ(spyInsert.count(), 2);

    // checking model layout
    EXPECT_EQ(view_model.rowCount(), 2);
    EXPECT_EQ(view_model.columnCount(), 2);
}

//! Removing single top level item.

TEST_F(RefViewModelControllerTest, removeSingleTopItem)
{
    // constructing the model with single item
    SessionModel session_model;
    session_model.insertItem<SessionItem>();

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    // root item should have one child
    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    QSignalSpy spyInsert(&view_model, &RefViewModel::rowsInserted);
    QSignalSpy spyRemove(&view_model, &RefViewModel::rowsRemoved);

    // removing child
    session_model.removeItem(session_model.rootItem(), {"", 0});
    ASSERT_EQ(spyInsert.count(), 0);
    ASSERT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(view_model.rowCount(), 0);
    EXPECT_EQ(view_model.columnCount(), 0);

    QList<QVariant> arguments = spyRemove.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Remove one of two top level items.

TEST_F(RefViewModelControllerTest, removeOneOfTopItems)
{
    // constructing model with two items
    SessionModel session_model;
    session_model.insertItem<SessionItem>();
    session_model.insertItem<SessionItem>();

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    // root item should have one child
    EXPECT_EQ(view_model.rowCount(), 2);
    EXPECT_EQ(view_model.columnCount(), 2);

    QSignalSpy spyRemove(&view_model, &RefViewModel::rowsRemoved);
    QSignalSpy spyInsert(&view_model, &RefViewModel::rowsInserted);

    // removing child
    session_model.removeItem(session_model.rootItem(), {"", 0});

    // no insert was called
    EXPECT_EQ(spyInsert.count(), 0);

    // removal was called once
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Setting top level item as ROOT item

TEST_F(RefViewModelControllerTest, setRootItem)
{
    SessionModel session_model;

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    auto item = session_model.insertItem<PropertyItem>();

    controller->setRootSessionItem(item);

    // new root item doesn't have children
    EXPECT_EQ(view_model.rowCount(), 0);
    EXPECT_EQ(view_model.columnCount(), 0);
}

//! Setting top level item as ROOT item (case parent and children).

TEST_F(RefViewModelControllerTest, setCompoundAsRootItem)
{
    SessionModel session_model;

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    auto item = session_model.insertItem<CompoundItem>();
    item->addProperty("thickness", 42.0);
    item->addProperty<VectorItem>("position");
    item->addProperty("radius", 43.0);

    controller->setRootSessionItem(item);

    EXPECT_EQ(view_model.rowCount(), 3);
    EXPECT_EQ(view_model.columnCount(), 2);

    // checking vector item
    auto index_of_vector_item = view_model.index(1, 0);
    EXPECT_EQ(view_model.rowCount(index_of_vector_item), 3);
    EXPECT_EQ(view_model.columnCount(index_of_vector_item), 2);
}

//! On model destroyed.

TEST_F(RefViewModelControllerTest, onModelReset)
{
    SessionModel session_model;
    session_model.insertItem<SessionItem>();
    session_model.insertItem<SessionItem>();
    session_model.insertItem<SessionItem>();

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);
    EXPECT_EQ(controller->rootSessionItem(), session_model.rootItem());

    QSignalSpy spyRset(&view_model, &RefViewModel::modelReset);

    session_model.clear();

    EXPECT_EQ(spyRset.count(), 1);
    EXPECT_EQ(view_model.rowCount(), 0);
    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(controller->rootSessionItem(), session_model.rootItem());
}

//! On model destroyed.

TEST_F(RefViewModelControllerTest, onModelDestroyed)
{
    auto session_model = std::make_unique<SessionModel>();
    session_model->insertItem<SessionItem>();

    // constructing viewmodel and its controller
    RefViewModel view_model;
    auto controller = create_controller(session_model.get(), &view_model);
    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    session_model.reset();
    EXPECT_EQ(view_model.rowCount(), 0);
    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(view_model.rootItem()->item(), nullptr);
}
