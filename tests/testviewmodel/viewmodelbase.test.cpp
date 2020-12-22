// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodelbase.h"

#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/viewmodel/standardviewitems.h"
#include <QSignalSpy>
#include <QStandardItemModel>

using namespace ModelView;

//! Tests for ViewModelBase class.

class ViewModelBaseTest : public ::testing::Test {
public:
    class TestItem : public ViewItem {
    public:
        TestItem() : ViewItem(nullptr, 0) {}
    };

    using children_t = std::vector<std::unique_ptr<ViewItem>>;
    using expected_t = std::vector<ViewItem*>;

    //! Helper function to get two vectors, each ncolumns length, in the form of a pair.
    //! First vector contains unique_ptr objects, second vector bare pointers to same objects.
    //! First vector is intended to be moved inside a model, second vector is to validate
    //! the content of a model after the move.

    std::pair<children_t, expected_t> test_data(int ncolumns)
    {
        auto vector_of_unique = TestUtils::create_row<ViewItem, TestItem>(ncolumns);
        auto vector_of_pointers = TestUtils::create_pointers(vector_of_unique);
        return std::make_pair(std::move(vector_of_unique), std::move(vector_of_pointers));
    }
};

//! Checking behaviour of QStandardItemModel for reference.

TEST_F(ViewModelBaseTest, standardItemModel)
{
    QStandardItemModel model;
    auto parent = model.invisibleRootItem();

    EXPECT_EQ(model.rowCount(), 0);
    EXPECT_EQ(model.columnCount(), 0);

    QList<QStandardItem*> children{new QStandardItem, new QStandardItem};
    parent->appendRow(children);
    auto index = model.index(0, 1, QModelIndex());
    EXPECT_EQ(model.itemFromIndex(index), children.at(1));

    // construction of index for non-existing column leads to invalid index
    auto non_existing_index = model.index(0, 2, QModelIndex());
    EXPECT_FALSE(non_existing_index.isValid());
    EXPECT_EQ(non_existing_index, QModelIndex());

    // attempt to retrieve item using this non-existing index leads to nullptr.
    EXPECT_EQ(model.itemFromIndex(non_existing_index), nullptr);

    // default constructed index gives same nullptr
    EXPECT_EQ(model.itemFromIndex(QModelIndex()), nullptr);

    // to summarize, default-constructed index, invalid index and index leading to non-existing
    // item are the same
}

//! Initial state of empty ViewModelBase.

TEST_F(ViewModelBaseTest, initialState)
{
    ViewModelBase viewmodel;
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
    EXPECT_TRUE(viewmodel.rootItem() != nullptr);
    EXPECT_EQ(viewmodel.itemFromIndex(QModelIndex()), nullptr);
    auto non_existing_index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_FALSE(non_existing_index.isValid());
    EXPECT_EQ(viewmodel.itemFromIndex(non_existing_index), nullptr);
    EXPECT_EQ(viewmodel.parent(QModelIndex()), QModelIndex());
    EXPECT_EQ(viewmodel.indexFromItem(viewmodel.rootItem()), QModelIndex());
}

TEST_F(ViewModelBaseTest, appendRow)
{
    ViewModelBase viewmodel;

    // item to append
    auto [children, expected] = test_data(/*ncolumns*/ 1);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 1);

    // constructing index for child
    auto child_index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_EQ(child_index.row(), 0);
    EXPECT_EQ(child_index.column(), 0);
    EXPECT_EQ(child_index.model(), &viewmodel);

    // indexFromItem
    EXPECT_EQ(viewmodel.indexFromItem(expected[0]), child_index);

    //  getting child from index
    EXPECT_EQ(viewmodel.itemFromIndex(child_index), expected[0]);

    // no grand-children
    EXPECT_EQ(viewmodel.rowCount(child_index), 0);
    EXPECT_EQ(viewmodel.columnCount(child_index), 0);

    // parent index
    EXPECT_EQ(viewmodel.parent(child_index), QModelIndex());
}

//! Insert one row befor another.

TEST_F(ViewModelBaseTest, insertRow)
{
    ViewModelBase viewmodel;

    // item to append
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 1);
    auto [children_front, expected_front] = test_data(/*ncolumns*/ 1);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row0));
    viewmodel.insertRow(viewmodel.rootItem(), 0, std::move(children_front));
    EXPECT_EQ(viewmodel.rowCount(), 2);
    EXPECT_EQ(viewmodel.columnCount(), 1);

    // constructing index for child
    auto child_index0 = viewmodel.index(0, 0, QModelIndex());
    auto child_index1 = viewmodel.index(1, 0, QModelIndex());

    // indexFromItem
    EXPECT_EQ(viewmodel.indexFromItem(expected_row0[0]), child_index1);
    EXPECT_EQ(viewmodel.indexFromItem(expected_front[0]), child_index0);

    //  getting child from index
    EXPECT_EQ(viewmodel.itemFromIndex(child_index0), expected_front[0]);
    EXPECT_EQ(viewmodel.itemFromIndex(child_index1), expected_row0[0]);
}

TEST_F(ViewModelBaseTest, removeRow)
{
    ViewModelBase viewmodel;

    // item to append
    auto [children, expected] = test_data(/*ncolumns*/ 1);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 1);

    // removing row
    viewmodel.removeRow(viewmodel.rootItem(), 0);
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
}

TEST_F(ViewModelBaseTest, appendRowToRow)
{
    ViewModelBase viewmodel;

    // preparing two rows of children, two columns each
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);

    // appending rows to root
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row0));
    // appending rows to row
    auto child0_index = viewmodel.index(0, 0, QModelIndex());
    auto child1_index = viewmodel.index(0, 1, QModelIndex());
    viewmodel.appendRow(expected_row0[0], std::move(children_row1));

    // checking results
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    EXPECT_EQ(viewmodel.rowCount(child0_index), 1);
    EXPECT_EQ(viewmodel.columnCount(child0_index), 2);

    // checking parent index of children in second row
    auto grandchild0_index = viewmodel.index(0, 0, child0_index);
    auto grandchild1_index = viewmodel.index(0, 1, child0_index);
    EXPECT_EQ(viewmodel.parent(grandchild0_index), child0_index);
    EXPECT_EQ(viewmodel.parent(grandchild1_index), child0_index);

    // index of item
    EXPECT_EQ(viewmodel.indexFromItem(expected_row0[0]), child0_index);
    EXPECT_EQ(viewmodel.indexFromItem(expected_row0[1]), child1_index);
    EXPECT_EQ(viewmodel.indexFromItem(expected_row1[0]), grandchild0_index);
    EXPECT_EQ(viewmodel.indexFromItem(expected_row1[1]), grandchild1_index);
}

TEST_F(ViewModelBaseTest, onRowsAppended)
{
    ViewModelBase viewmodel;

    // two items to append as a single row with two columns
    auto [children, expected] = test_data(/*ncolumns*/ 2);

    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);

    // checking that signaling is about the parent
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 1);
    QList<QVariant> arguments = spyInsert.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    //  getting child from index
    auto index0 = viewmodel.index(0, 0, QModelIndex());
    auto index1 = viewmodel.index(0, 1, QModelIndex());
    EXPECT_EQ(viewmodel.itemFromIndex(index0), expected[0]);
    EXPECT_EQ(viewmodel.itemFromIndex(index1), expected[1]);
}

TEST_F(ViewModelBaseTest, rowsRemoved)
{
    ViewModelBase viewmodel;

    // three rows of items
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);
    auto [children_row2, expected_row2] = test_data(/*ncolumns*/ 2);

    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row0));
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row1));
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row2));

    // removing middle row
    viewmodel.removeRow(viewmodel.rootItem(), 1);

    // checking that signaling is about the parent
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(spyInsert.count(), 3);
    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 1);
    EXPECT_EQ(arguments.at(2).value<int>(), 1);
}

TEST_F(ViewModelBaseTest, data)
{
    SessionItem item;
    QVariant expected(42.0);
    item.setData(expected);

    children_t children;
    children.emplace_back(std::make_unique<ViewDataItem>(&item));

    ViewModelBase viewmodel;
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));

    QModelIndex children_index = viewmodel.index(0, 0, QModelIndex());

    EXPECT_EQ(viewmodel.data(children_index, Qt::EditRole), expected);
}

TEST_F(ViewModelBaseTest, setData)
{
    // creating single item
    SessionItem item;
    QVariant expected(42.0);
    item.setData(expected);

    // creating view model displaying given SessionItem
    children_t children;
    children.emplace_back(std::make_unique<ViewDataItem>(&item));
    ViewModelBase viewmodel;
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));

    QSignalSpy spyData(&viewmodel, &ViewModelBase::dataChanged);

    // changing the data
    QModelIndex children_index = viewmodel.index(0, 0, QModelIndex());
    QVariant new_value(43.0);
    EXPECT_TRUE(viewmodel.setData(children_index, new_value, Qt::EditRole));

    // checking signaling
    EXPECT_EQ(spyData.count(), 1);
    QList<QVariant> arguments = spyData.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), children_index);
    EXPECT_EQ(arguments.at(1).value<QModelIndex>(), children_index);
    QVector<int> expected_roles{Qt::EditRole};
    EXPECT_EQ(arguments.at(2).value<QVector<int>>(), expected_roles);
}

TEST_F(ViewModelBaseTest, flags)
{
    SessionItem item;
    QVariant expected(42.0);
    item.setData(expected);
    item.setDisplayName("Name");

    children_t children;
    children.emplace_back(std::make_unique<ViewLabelItem>(&item));
    children.emplace_back(std::make_unique<ViewDataItem>(&item));

    ViewModelBase viewmodel;
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children));

    QModelIndex label_index = viewmodel.index(0, 0, QModelIndex());
    QModelIndex data_index = viewmodel.index(0, 1, QModelIndex());

    EXPECT_TRUE(viewmodel.flags(label_index) & Qt::ItemIsSelectable);
    EXPECT_TRUE(viewmodel.flags(label_index) & Qt::ItemIsEnabled);
    EXPECT_FALSE(viewmodel.flags(label_index) & Qt::ItemIsEditable);

    EXPECT_TRUE(viewmodel.flags(data_index) & Qt::ItemIsSelectable);
    EXPECT_TRUE(viewmodel.flags(data_index) & Qt::ItemIsEnabled);
    EXPECT_TRUE(viewmodel.flags(data_index) & Qt::ItemIsEditable);
}

TEST_F(ViewModelBaseTest, clearRowsFromRoot)
{
    ViewModelBase viewmodel;

    // three rows of items
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);

    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    // appending one row
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row0));
    viewmodel.appendRow(viewmodel.rootItem(), std::move(children_row1));

    viewmodel.clearRows(viewmodel.rootItem());

    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);

    // checking that signaling is about the parent
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(spyInsert.count(), 2);
    QList<QVariant> arguments = spyRemove.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 1);
}
