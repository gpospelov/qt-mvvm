// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/linkeditem.h"

#include "google_test.h"
#include "mockwidgets.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"

using namespace ModelView;
using ::testing::_;

//! LinkedItem tests.

class LinkedItemTest : public ::testing::Test {
};

//! Initial state of item when it is created outside of model context.

TEST_F(LinkedItemTest, initialState)
{
    LinkedItem item;
    EXPECT_EQ(item.get(), nullptr);
    EXPECT_EQ(item.data<std::string>(), std::string());
}

//! Link in single model context.

TEST_F(LinkedItemTest, sameModelContext)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    auto link = model.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting the link
    link->setLink(item);

    // now linked
    EXPECT_EQ(link->get(), item);
    EXPECT_EQ(link->data<std::string>(), item->identifier());
}

//! Link in different model context.

TEST_F(LinkedItemTest, differentModelContext)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model1("TestModel1", pool);
    SessionModel model2("TestModel2", pool);

    auto item = model1.insertItem<PropertyItem>();
    auto link = model2.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting the link
    link->setLink(item);

    // now linked
    EXPECT_EQ(link->get(), item);
}

//! Signals when links is set.

TEST_F(LinkedItemTest, onSetLink)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();
    auto link = model.insertItem<LinkedItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    MockWidgetForItem widget(link);

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = link;
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);
    EXPECT_CALL(widget, onPropertyChange(_, _)).Times(0);

    // making action
    link->setLink(item);
}

//! Link in different model context.

TEST_F(LinkedItemTest, setNullAsLink)
{
    auto pool = std::make_shared<ItemPool>();

    SessionModel model("TestModel", pool);
    auto link = model.insertItem<LinkedItem>();
    auto item = model.insertItem<PropertyItem>();

    // no link by default
    EXPECT_EQ(link->get(), nullptr);

    // setting link
    link->setLink(item);
    EXPECT_EQ(link->get(), item);

    // still null link
    link->setLink(nullptr);
    EXPECT_EQ(link->get(), nullptr);
    EXPECT_TRUE(link->data<QVariant>().isValid());
    EXPECT_EQ(link->data<std::string>(), std::string());
}
