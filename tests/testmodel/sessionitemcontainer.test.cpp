// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/sessionitemcontainer.h"

#include "google_test.h"
#include "mvvm/model/sessionitem.h"

using namespace ModelView;

//! Tests for TestSessionItemContainer class.

class SessionItemContainerTest : public ::testing::Test {
};

//! Initial state of emty SessionItemTag.

TEST_F(SessionItemContainerTest, initialState)
{
    const std::string name("tag");
    SessionItemContainer tag(TagInfo::universalTag(name));

    EXPECT_EQ(tag.itemCount(), 0);
    EXPECT_TRUE(tag.empty());
    EXPECT_EQ(tag.name(), name);
    EXPECT_EQ(tag.items(), std::vector<SessionItem*>());
}

//! Checking ::insertItem.

TEST_F(SessionItemContainerTest, insertItem)
{
    const std::string tag_name("tag");
    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // inserting non-existing item is not allowed
    EXPECT_FALSE(tag.insertItem(nullptr, tag.itemCount()));
    EXPECT_EQ(tag.itemCount(), 0);

    // insertion at the end
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child2, tag.itemCount()));
    EXPECT_EQ(tag.itemCount(), 2);
    EXPECT_FALSE(tag.empty());
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // insertion at the beginning
    auto child3 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child3, 0));
    expected = {child3, child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // insertion in between
    auto child4 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child4, 1));
    expected = {child3, child4, child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // using index equal to number of items
    auto child5 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child5, tag.itemCount()));
    expected = {child3, child4, child1, child2, child5};
    EXPECT_EQ(tag.items(), expected);

    // insertion with wrong index
    auto child6 = new SessionItem;
    EXPECT_FALSE(tag.insertItem(child6, 42));
    EXPECT_EQ(tag.items(), expected);
    delete child6;
}

//! Checking ::insertItem when item has specific model type.

TEST_F(SessionItemContainerTest, insertItemModelType)
{
    const std::string tag_name("tag");
    const std::vector<std::string> model_types = {"model_a"};

    SessionItemContainer tag(TagInfo::universalTag(tag_name, model_types));

    // insertion of wrong model type is not allowed
    auto child1 = new SessionItem("model_a");
    auto child2 = new SessionItem("model_b");
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_FALSE(tag.insertItem(child2, tag.itemCount()));
    delete child2;

    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.items(), expected);
}

//! Checking ::insertItem when tag is related to property tag.

TEST_F(SessionItemContainerTest, insertItemPropertyType)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemContainer tag(TagInfo::propertyTag(name, property_type));

    // insertion of second property item is not allowed (because of reached maximum)
    auto child1 = new SessionItem(property_type);
    auto child2 = new SessionItem(property_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_FALSE(tag.insertItem(child2, tag.itemCount()));
    delete child2;

    // insertion of wrong model type is not allowed
    auto child3 = new SessionItem("another_model");
    EXPECT_FALSE(tag.insertItem(child3, tag.itemCount()));
    delete child3;
    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.items(), expected);
}

//! Checking ::indexOfItem.

TEST_F(SessionItemContainerTest, indexOfItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // index of two items
    auto child1 = new SessionItem(model_type);
    auto child2 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_EQ(tag.indexOfItem(child1), 0);
    EXPECT_TRUE(tag.insertItem(child2, tag.itemCount()));
    EXPECT_EQ(tag.indexOfItem(child1), 0);
    EXPECT_EQ(tag.indexOfItem(child2), 1);

    // not existing items
    EXPECT_EQ(tag.indexOfItem(nullptr), -1);
    auto child3 = std::make_unique<SessionItem>(model_type);
    EXPECT_EQ(tag.indexOfItem(child3.get()), -1);
}

//! Checking ::itemAt.

TEST_F(SessionItemContainerTest, itemAt)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // items at given indices
    auto child1 = new SessionItem(model_type);
    auto child2 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child2, tag.itemCount()));
    EXPECT_EQ(tag.itemAt(0), child1);
    EXPECT_EQ(tag.itemAt(1), child2);

    // non-existing indices
    EXPECT_EQ(tag.itemAt(2), nullptr);
    EXPECT_EQ(tag.itemAt(3), nullptr);
    EXPECT_EQ(tag.itemAt(-1), nullptr);
}

//! Checking ::takeItem.

TEST_F(SessionItemContainerTest, takeItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // taking non existing items
    EXPECT_EQ(tag.takeItem(0), nullptr);

    // inserting items
    auto child1 = new SessionItem(model_type);
    auto child2 = new SessionItem(model_type);
    auto child3 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child2, tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child3, tag.itemCount()));

    // taking item in between
    auto taken2 = tag.takeItem(1);
    EXPECT_EQ(child2, taken2);
    delete taken2;

    // order of remaining children
    std::vector<SessionItem*> expected = {child1, child3};
    EXPECT_EQ(tag.items(), expected);

    // taking non existing items
    EXPECT_EQ(tag.takeItem(-1), nullptr);
    EXPECT_EQ(tag.takeItem(tag.itemCount()), nullptr);
}

//! Checking ::canTakeItem.

TEST_F(SessionItemContainerTest, canTakeItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // taking non existing items
    EXPECT_FALSE(tag.canTakeItem(0));

    // inserting items
    auto child1 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));
    EXPECT_TRUE(tag.canTakeItem(0));

    // taking non existing items
    EXPECT_FALSE(tag.canTakeItem(-1));
    EXPECT_FALSE(tag.canTakeItem(tag.itemCount()));
}

//! Checking ::canInsertItem.

TEST_F(SessionItemContainerTest, canInsertItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // inserting non-existing item
    EXPECT_FALSE(tag.canInsertItem(nullptr, 0));

    // we should be allowed to insert valid child
    auto child1 = std::make_unique<SessionItem>(model_type);
    EXPECT_TRUE(tag.canInsertItem(child1.get(), 0));

    // wrong index is not allowed for insertion
    EXPECT_FALSE(tag.canInsertItem(child1.get(), 1));
    EXPECT_FALSE(tag.canInsertItem(child1.get(), -1));

    // inserting child
    EXPECT_TRUE(tag.insertItem(child1.release(), tag.itemCount()));

    // can we insert second child?
    auto child2 = std::make_unique<SessionItem>(model_type);
    EXPECT_TRUE(tag.canInsertItem(child2.get(), 0));
    EXPECT_TRUE(tag.canInsertItem(child2.get(), 1));
    EXPECT_FALSE(tag.canInsertItem(child2.get(), 2));
    EXPECT_FALSE(tag.canInsertItem(child2.get(), -1));
}

//! Checking ::canInsertItem.

TEST_F(SessionItemContainerTest, canInsertItemForPropertyTag)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemContainer tag(TagInfo::propertyTag(name, property_type));

    // we should be allowed to insert valid child
    auto child1 = std::make_unique<SessionItem>(property_type);
    EXPECT_TRUE(tag.canInsertItem(child1.get(), 0));

    // inserting child
    EXPECT_TRUE(tag.insertItem(child1.release(), tag.itemCount()));

    // second property shouldn't be posible to insert because of exceeded maximum
    auto child2 = std::make_unique<SessionItem>(property_type);
    EXPECT_FALSE(tag.canInsertItem(child2.get(), 0));
}

//! Checking ::canInsertItem.

TEST_F(SessionItemContainerTest, canInsertItemForUniversalTag)
{
    const std::string tag1 = "tag1";
    const int maxItems = 2;
    auto parent = std::make_unique<SessionItem>();
    SessionItemContainer tag(TagInfo(tag1, 0, maxItems, std::vector<std::string>() = {}));

    // inserting child
    auto child1 = std::make_unique<SessionItem>();
    EXPECT_FALSE(tag.canInsertItem(child1.get(), -1)); // implementation requires exact index
    EXPECT_TRUE(tag.canInsertItem(child1.get(), 0));
    EXPECT_TRUE(tag.canInsertItem(child1.get(), tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child1.release(), tag.itemCount()));

    // inserting second child
    auto child2 = std::make_unique<SessionItem>();
    EXPECT_FALSE(tag.canInsertItem(child2.get(), -1));
    EXPECT_TRUE(tag.canInsertItem(child2.get(), 0));
    EXPECT_TRUE(tag.canInsertItem(child2.get(), tag.itemCount()));
    EXPECT_TRUE(tag.insertItem(child2.release(), tag.itemCount()));

    // inserting third child is not possible
    auto child3 = std::make_unique<SessionItem>();
    EXPECT_FALSE(tag.canInsertItem(child3.get(), -1));
    EXPECT_FALSE(tag.canInsertItem(child3.get(), 0));
    EXPECT_FALSE(tag.canInsertItem(child3.get(), tag.itemCount()));
}


//! Checking ::takeItem when tag is related to property tag.

TEST_F(SessionItemContainerTest, takeItemPropertyType)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemContainer tag(TagInfo::propertyTag(name, property_type));

    // insertion of second property item is not allowed (because of reached maximum)
    auto child1 = new SessionItem(property_type);
    EXPECT_TRUE(tag.insertItem(child1, tag.itemCount()));

    // attempt to take property item
    EXPECT_FALSE(tag.canTakeItem(0));
    EXPECT_EQ(tag.takeItem(0), nullptr);
}
