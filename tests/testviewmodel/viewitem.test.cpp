// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewitem.h"

#include "google_test.h"
#include "test_utils.h"
#include <stdexcept>

using namespace ModelView;

//! Tests for ViewItem class.

class ViewItemTest : public ::testing::Test {
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

//! Initial state of RefViewItem.

TEST_F(ViewItemTest, initialState)
{
    TestItem view_item;

    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
    EXPECT_EQ(view_item.row(), -1);
    EXPECT_EQ(view_item.column(), -1);
    EXPECT_EQ(view_item.parent(), nullptr);
    EXPECT_THROW(view_item.child(0, 0), std::runtime_error);
    EXPECT_EQ(view_item.item(), nullptr);
    EXPECT_EQ(view_item.item_role(), 0);
}

//! Append single item as row.

TEST_F(ViewItemTest, appendRow)
{
    auto [children, expected] = test_data(/*ncolumns*/ 1);

    // appending row with single item
    TestItem view_item;
    view_item.appendRow(std::move(children));

    // checking parent
    EXPECT_EQ(view_item.rowCount(), 1);
    EXPECT_EQ(view_item.columnCount(), 1);
    EXPECT_EQ(view_item.child(0, 0), expected[0]);
    EXPECT_THROW(view_item.child(0, 1), std::runtime_error);

    // checking appended child
    EXPECT_EQ(expected[0]->parent(), &view_item);
    EXPECT_EQ(expected[0]->row(), 0);
    EXPECT_EQ(expected[0]->column(), 0);
}

//! Remove row.

TEST_F(ViewItemTest, removeRow)
{
    auto [children, expected] = test_data(/*ncolumns*/ 1);

    // appending row with single item
    TestItem view_item;
    view_item.appendRow(std::move(children));
    view_item.removeRow(0);

    // checking parent
    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
}

//! Append two rows with two items each.

TEST_F(ViewItemTest, appendTwoRows)
{
    // preparing two rows of children, two columns each
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);

    // appending rows
    TestItem view_item;
    view_item.appendRow(std::move(children_row0));
    view_item.appendRow(std::move(children_row1));

    EXPECT_EQ(view_item.rowCount(), 2);
    EXPECT_EQ(view_item.columnCount(), 2);
    EXPECT_EQ(view_item.child(0, 0), expected_row0[0]);
    EXPECT_EQ(view_item.child(0, 1), expected_row0[1]);
    EXPECT_EQ(view_item.child(1, 0), expected_row1[0]);
    EXPECT_EQ(view_item.child(1, 1), expected_row1[1]);
    EXPECT_THROW(view_item.child(2, 2), std::runtime_error);

    // checking parents
    EXPECT_EQ(expected_row0[0]->parent(), &view_item);
    EXPECT_EQ(expected_row0[1]->parent(), &view_item);
    EXPECT_EQ(expected_row1[0]->parent(), &view_item);
    EXPECT_EQ(expected_row1[1]->parent(), &view_item);

    // checking row and column of children
    EXPECT_EQ(expected_row0[0]->row(), 0);
    EXPECT_EQ(expected_row0[1]->row(), 0);
    EXPECT_EQ(expected_row1[0]->row(), 1);
    EXPECT_EQ(expected_row1[1]->row(), 1);
    EXPECT_EQ(expected_row0[0]->column(), 0);
    EXPECT_EQ(expected_row0[1]->column(), 1);
    EXPECT_EQ(expected_row1[0]->column(), 0);
    EXPECT_EQ(expected_row1[1]->column(), 1);

    // attempt to add row with different amount of children should fail
    auto [children_row2, expected_row2] = test_data(/*ncolumns*/ 1);
    EXPECT_THROW(view_item.appendRow(std::move(children_row2)), std::runtime_error);
    EXPECT_EQ(view_item.rowCount(), 2);
    EXPECT_EQ(view_item.columnCount(), 2);
}

//! Append two rows with two items each.

TEST_F(ViewItemTest, insertRowsThenRemove)
{
    // preparing two rows of children, two columns each
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);
    auto [children_row2, expected_row2] = test_data(/*ncolumns*/ 2);

    // appending rows
    TestItem view_item;
    view_item.appendRow(std::move(children_row0));
    view_item.appendRow(std::move(children_row1));
    view_item.insertRow(1, std::move(children_row2)); // inserting in-between

    EXPECT_EQ(view_item.rowCount(), 3);
    EXPECT_EQ(view_item.columnCount(), 2);
    EXPECT_EQ(view_item.child(0, 0), expected_row0[0]);
    EXPECT_EQ(view_item.child(0, 1), expected_row0[1]);
    EXPECT_EQ(view_item.child(1, 0), expected_row2[0]);
    EXPECT_EQ(view_item.child(1, 1), expected_row2[1]);
    EXPECT_EQ(view_item.child(2, 0), expected_row1[0]);
    EXPECT_EQ(view_item.child(2, 1), expected_row1[1]);

    // checking parents
    EXPECT_EQ(expected_row0[0]->parent(), &view_item);
    EXPECT_EQ(expected_row0[1]->parent(), &view_item);
    EXPECT_EQ(expected_row1[0]->parent(), &view_item);
    EXPECT_EQ(expected_row1[1]->parent(), &view_item);
    EXPECT_EQ(expected_row2[0]->parent(), &view_item);
    EXPECT_EQ(expected_row2[1]->parent(), &view_item);

    // checking row and column of children
    EXPECT_EQ(expected_row0[0]->row(), 0);
    EXPECT_EQ(expected_row0[1]->row(), 0);
    EXPECT_EQ(expected_row1[0]->row(), 2);
    EXPECT_EQ(expected_row1[1]->row(), 2);
    EXPECT_EQ(expected_row2[0]->row(), 1);
    EXPECT_EQ(expected_row2[1]->row(), 1);
    EXPECT_EQ(expected_row0[0]->column(), 0);
    EXPECT_EQ(expected_row0[1]->column(), 1);
    EXPECT_EQ(expected_row1[0]->column(), 0);
    EXPECT_EQ(expected_row1[1]->column(), 1);
    EXPECT_EQ(expected_row2[0]->column(), 0);
    EXPECT_EQ(expected_row2[1]->column(), 1);

    // removing middle row
    view_item.removeRow(1);
    EXPECT_EQ(view_item.child(0, 0), expected_row0[0]);
    EXPECT_EQ(view_item.child(0, 1), expected_row0[1]);
    EXPECT_EQ(view_item.child(1, 0), expected_row1[0]);
    EXPECT_EQ(view_item.child(1, 1), expected_row1[1]);
}

//! Clean item's children.

TEST_F(ViewItemTest, clear)
{
    auto [children, expected] = test_data(/*ncolumns*/ 1);

    TestItem view_item;
    view_item.appendRow(std::move(children));
    view_item.clear();

    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
}

TEST_F(ViewItemTest, children)
{
    auto [children_row0, expected_row0] = test_data(/*ncolumns*/ 2);
    auto [children_row1, expected_row1] = test_data(/*ncolumns*/ 2);

    TestItem view_item;
    view_item.appendRow(std::move(children_row0));
    view_item.appendRow(std::move(children_row1));

    std::vector<ViewItem*> expected;
    std::copy(expected_row0.begin(), expected_row0.end(), std::back_inserter(expected));
    std::copy(expected_row1.begin(), expected_row1.end(), std::back_inserter(expected));

    EXPECT_EQ(view_item.children(), expected);
}
