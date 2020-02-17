// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/viewmodel/refviewitem.h>

using namespace ModelView;

//! Tests for RefViewItem class.

class RefViewItemTest : public ::testing::Test
{
public:
    ~RefViewItemTest();
};

RefViewItemTest::~RefViewItemTest() = default;

//! Initial state of RefViewItem.

TEST_F(RefViewItemTest, initialState)
{
    RefViewItem view_item;

    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
    EXPECT_THROW(view_item.child(0, 0), std::runtime_error);
}

//! Append single item as row.

TEST_F(RefViewItemTest, appendRow)
{
    std::vector<std::unique_ptr<RefViewItem>> children;
    children.emplace_back(std::make_unique<RefViewItem>());

    RefViewItem* expected = children[0].get();

    RefViewItem view_item;
    view_item.appendRow(std::move(children));

    EXPECT_EQ(view_item.rowCount(), 1);
    EXPECT_EQ(view_item.columnCount(), 1);
    EXPECT_EQ(view_item.child(0, 0), expected);
    EXPECT_THROW(view_item.child(0, 1), std::runtime_error);
}

//! Append two rows with two items each.

TEST_F(RefViewItemTest, appendTwoRows)
{
    std::vector<std::unique_ptr<RefViewItem>> children_row0, children_row1, children_row2;

    children_row0.emplace_back(std::make_unique<RefViewItem>());
    children_row0.emplace_back(std::make_unique<RefViewItem>());
    children_row1.emplace_back(std::make_unique<RefViewItem>());
    children_row1.emplace_back(std::make_unique<RefViewItem>());

    std::vector<RefViewItem*> expected0 = {children_row0[0].get(), children_row0[1].get()};
    std::vector<RefViewItem*> expected1 = {children_row1[0].get(), children_row1[1].get()};

    RefViewItem view_item;
    view_item.appendRow(std::move(children_row0));
    view_item.appendRow(std::move(children_row1));

    EXPECT_EQ(view_item.rowCount(), 2);
    EXPECT_EQ(view_item.columnCount(), 2);
    EXPECT_EQ(view_item.child(0, 0), expected0[0]);
    EXPECT_EQ(view_item.child(0, 1), expected0[1]);
    EXPECT_EQ(view_item.child(1, 0), expected1[0]);
    EXPECT_EQ(view_item.child(1, 1), expected1[1]);
    EXPECT_THROW(view_item.child(2, 2), std::runtime_error);

    // attempt to add row with different amount of children should fail
    children_row2.emplace_back(std::make_unique<RefViewItem>());
    EXPECT_THROW(view_item.appendRow(std::move(children_row2)), std::runtime_error);
    EXPECT_EQ(view_item.rowCount(), 2);
    EXPECT_EQ(view_item.columnCount(), 2);
}

//! Append single item as row.

TEST_F(RefViewItemTest, clear)
{
    std::vector<std::unique_ptr<RefViewItem>> children;
    children.emplace_back(std::make_unique<RefViewItem>());

    RefViewItem view_item;
    view_item.appendRow(std::move(children));
    view_item.clear();

    EXPECT_EQ(view_item.rowCount(), 0);
    EXPECT_EQ(view_item.columnCount(), 0);
}
