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
#include <mvvm/viewmodel/refviewitem.h>

using namespace ModelView;

//! Tests for RefViewItem class.

class RefViewItemTest : public ::testing::Test
{
public:
    ~RefViewItemTest();
    class TestItem : public RefViewItem
    {
    public:
        TestItem() : RefViewItem(nullptr, 0) {}
        ~TestItem() override;
    };

    //! Helper function to create row of test items.

    std::vector<std::unique_ptr<RefViewItem>> create_row(int ncolumns) const
    {
        return TestUtils::create_row<RefViewItem, TestItem>(ncolumns);
    }

    //! Helper function to get vector of bare pointer out of vector of unique_ptr.
    //! Used to validate logic when using std::move.

    std::vector<RefViewItem*> get_expected(const std::vector<std::unique_ptr<RefViewItem>>& vec)
    {
        return TestUtils::create_pointers(vec);
    }

};

RefViewItemTest::~RefViewItemTest() = default;
RefViewItemTest::TestItem::~TestItem() = default;

//! Initial state of RefViewItem.

TEST_F(RefViewItemTest, initialState)
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

TEST_F(RefViewItemTest, appendRow)
{
    auto children = create_row(/*ncolumns*/1);
    auto expected = get_expected(children);

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

TEST_F(RefViewItemTest, removeRow)
{
    auto children = create_row(/*ncolumns*/1);

    // appending row with single item
    TestItem view_item;
    view_item.appendRow(std::move(children));
    view_item.removeRow(0);

    // checking parent
    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
}


//! Append two rows with two items each.

TEST_F(RefViewItemTest, appendTwoRows)
{
    // preparing two rows of children, two columns each
    auto children_row0 = create_row(/*ncolumns*/2);
    auto children_row1 = create_row(/*ncolumns*/2);
    auto expected_row0 = get_expected(children_row0);
    auto expected_row1 = get_expected(children_row1);

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
    auto children_row2 = create_row(/*ncolumns*/1);
    EXPECT_THROW(view_item.appendRow(std::move(children_row2)), std::runtime_error);
    EXPECT_EQ(view_item.rowCount(), 2);
    EXPECT_EQ(view_item.columnCount(), 2);
}

//! Append two rows with two items each.

TEST_F(RefViewItemTest, insertRowsThenRemove)
{
    // preparing two rows of children, two columns each
    auto children_row0 = create_row(/*ncolumns*/2);
    auto children_row1 = create_row(/*ncolumns*/2);
    auto children_row2 = create_row(/*ncolumns*/2);
    auto expected_row0 = get_expected(children_row0);
    auto expected_row1 = get_expected(children_row1);
    auto expected_row2 = get_expected(children_row2);

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

TEST_F(RefViewItemTest, clear)
{
    auto children = create_row(/*ncolumns*/1);

    TestItem view_item;
    view_item.appendRow(std::move(children));
    view_item.clear();

    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
}
