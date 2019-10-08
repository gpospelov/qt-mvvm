#include "google_test.h"
#include "sessionitem.h"
#include "sessionitemcontainer.h"
#include "test_utils.h"

using namespace ModelView;

//! Tests for TestSessionItemContainer class.

class TestSessionItemContainer : public ::testing::Test
{
public:
    ~TestSessionItemContainer();
};

TestSessionItemContainer::~TestSessionItemContainer() = default;

//! Initial state of emty SessionItemTag.

TEST_F(TestSessionItemContainer, initialState)
{
    const std::string name("tag");
    SessionItemContainer tag(TagInfo::universalTag(name));

    EXPECT_EQ(tag.itemCount(), 0);
    EXPECT_EQ(tag.name(), name);
    EXPECT_EQ(tag.items(), std::vector<SessionItem*>());
}

//! Checking ::insertItem.

TEST_F(TestSessionItemContainer, insertItem)
{
    const std::string tag_name("tag");
    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // inserting non-existing item is not allowed
    EXPECT_FALSE(tag.insertItem(nullptr));
    EXPECT_EQ(tag.itemCount(), 0);

    // insertion at the end
    SessionItem* child1 = new SessionItem;
    SessionItem* child2 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_EQ(tag.itemCount(), 2);
    std::vector<SessionItem*> expected = {child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // insertion at the beginning
    SessionItem* child3 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child3, 0));
    expected = {child3, child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // insertion in between
    SessionItem* child4 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child4, 1));
    expected = {child3, child4, child1, child2};
    EXPECT_EQ(tag.items(), expected);

    // using index equal to number of items
    SessionItem* child5 = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child5, tag.itemCount()));
    expected = {child3, child4, child1, child2, child5};
    EXPECT_EQ(tag.items(), expected);

    // insertion with wrong index
    SessionItem* child6 = new SessionItem;
    EXPECT_FALSE(tag.insertItem(child6, 42));
    EXPECT_EQ(tag.items(), expected);
    delete child6;
}

//! Checking ::insertItem when item has specific model type.

TEST_F(TestSessionItemContainer, insertItemModelType)
{
    const std::string tag_name("tag");
    const std::vector<std::string> model_types = {"model_a"};

    SessionItemContainer tag(TagInfo::universalTag(tag_name, model_types));

    // insertion of wrong model type is not allowed
    SessionItem* child1 = new SessionItem("model_a");
    SessionItem* child2 = new SessionItem("model_b");
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_FALSE(tag.insertItem(child2));
    delete child2;

    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.items(), expected);
}

//! Checking ::insertItem when tag is related to property tag.

TEST_F(TestSessionItemContainer, insertItemPropertyType)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemContainer tag(TagInfo::propertyTag(name, property_type));

    // insertion of second property item is not allowed (because of reached maximum)
    SessionItem* child1 = new SessionItem(property_type);
    SessionItem* child2 = new SessionItem(property_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_FALSE(tag.insertItem(child2));
    delete child2;

    // insertion of wrong model type is not allowed
    SessionItem* child3 = new SessionItem("another_model");
    EXPECT_FALSE(tag.insertItem(child3));
    delete child3;
    std::vector<SessionItem*> expected = {child1};
    EXPECT_EQ(tag.items(), expected);
}

//! Checking ::indexOfItem.

TEST_F(TestSessionItemContainer, indexOfItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // index of two items
    SessionItem* child1 = new SessionItem(model_type);
    SessionItem* child2 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_EQ(tag.indexOfItem(child1), 0);
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_EQ(tag.indexOfItem(child1), 0);
    EXPECT_EQ(tag.indexOfItem(child2), 1);

    // not existing items
    EXPECT_EQ(tag.indexOfItem(nullptr), -1);
    auto child3 = std::make_unique<SessionItem>(model_type);
    EXPECT_EQ(tag.indexOfItem(child3.get()), -1);
}

//! Checking ::itemAt.

TEST_F(TestSessionItemContainer, itemAt)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // items at given indices
    SessionItem* child1 = new SessionItem(model_type);
    SessionItem* child2 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_EQ(tag.itemAt(0), child1);
    EXPECT_EQ(tag.itemAt(1), child2);

    // non-existing indices
    EXPECT_EQ(tag.itemAt(2), nullptr);
    EXPECT_EQ(tag.itemAt(3), nullptr);
    EXPECT_EQ(tag.itemAt(-1), nullptr);
}

//! Checking ::takeItem.

TEST_F(TestSessionItemContainer, takeItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // taking non existing items
    EXPECT_EQ(tag.takeItem(0), nullptr);

    // inserting items
    SessionItem* child1 = new SessionItem(model_type);
    SessionItem* child2 = new SessionItem(model_type);
    SessionItem* child3 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_TRUE(tag.insertItem(child2));
    EXPECT_TRUE(tag.insertItem(child3));

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

TEST_F(TestSessionItemContainer, canTakeItem)
{
    const std::string tag_name("tag");
    const std::string model_type("model_a");

    SessionItemContainer tag(TagInfo::universalTag(tag_name));

    // taking non existing items
    EXPECT_FALSE(tag.canTakeItem(0));

    // inserting items
    SessionItem* child1 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1));
    EXPECT_TRUE(tag.canTakeItem(0));

    // taking non existing items
    EXPECT_FALSE(tag.canTakeItem(-1));
    EXPECT_FALSE(tag.canTakeItem(tag.itemCount()));
}


//! Checking ::takeItem when tag is related to property tag.

TEST_F(TestSessionItemContainer, takeItemPropertyType)
{
    const std::string name("tag");
    const std::string property_type("Property");

    SessionItemContainer tag(TagInfo::propertyTag(name, property_type));

    // insertion of second property item is not allowed (because of reached maximum)
    SessionItem* child1 = new SessionItem(property_type);
    EXPECT_TRUE(tag.insertItem(child1));

    // attempt to take property item
    EXPECT_FALSE(tag.canTakeItem(0));
    EXPECT_EQ(tag.takeItem(0), nullptr);
}
