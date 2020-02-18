// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QSignalSpy>
#include <QStandardItemModel>
#include <mvvm/viewmodel/refviewitem.h>
#include <mvvm/viewmodel/refviewmodel.h>

using namespace ModelView;

//! Tests for RefViewModel class.

class RefViewModelTest : public ::testing::Test
{
public:
    ~RefViewModelTest();
};

RefViewModelTest::~RefViewModelTest() = default;

//! Checking behaviour of QStandardItemModel for reference.

TEST_F(RefViewModelTest, standardItemModel)
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

//! Initial state of empty RefViewModel.

TEST_F(RefViewModelTest, initialState)
{
    RefViewModel viewmodel;
    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
    EXPECT_TRUE(viewmodel.rootItem() != nullptr);
    EXPECT_EQ(viewmodel.itemFromIndex(QModelIndex()), nullptr);
    auto non_existing_index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_FALSE(non_existing_index.isValid());
    EXPECT_EQ(viewmodel.itemFromIndex(non_existing_index), nullptr);
}

TEST_F(RefViewModelTest, appendRow)
{
    RefViewModel viewmodel;

    // item to append
    std::vector<std::unique_ptr<RefViewItem>> children;
    children.emplace_back(std::make_unique<RefViewItem>());
    RefViewItem* expected = children[0].get();

    // appending one row
    viewmodel.appendRow(QModelIndex(), std::move(children));
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 1);

    // constructing index for child
    auto index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), 0);
    EXPECT_EQ(index.model(), &viewmodel);

    //  getting child from index
    EXPECT_EQ(viewmodel.itemFromIndex(index), expected);

    // no grand-children
    EXPECT_EQ(viewmodel.rowCount(index), 0);
    EXPECT_EQ(viewmodel.columnCount(index), 0);
}

TEST_F(RefViewModelTest, rowsInserted)
{
    RefViewModel viewmodel;

    // two items to append as a single row with two columns
    std::vector<std::unique_ptr<RefViewItem>> children;
    children.emplace_back(std::make_unique<RefViewItem>());
    children.emplace_back(std::make_unique<RefViewItem>());
    std::vector<RefViewItem*> expected = {children[0].get(), children[1].get()};

    QSignalSpy spyInsert(&viewmodel, &RefViewModel::rowsInserted);

    // appending one row
    viewmodel.appendRow(QModelIndex(), std::move(children));
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 2);

    // checking that signaling is about the parent
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
