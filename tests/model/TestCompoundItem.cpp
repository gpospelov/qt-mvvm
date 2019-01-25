#include "google_test.h"
#include "test_utils.h"
#include "compounditem.h"
#include "sessionmodel.h"
#include <memory>
#include <stdexcept>

using namespace ModelView;

//! Test of CompountItem machinery (property children etc).

class TestCompoundItem : public ::testing::Test
{
public:
    ~TestCompoundItem();
};

TestCompoundItem::~TestCompoundItem() = default;

TEST_F(TestCompoundItem, initialState)
{
    CompoundItem item;
    EXPECT_EQ(item.childrenCount(), 0);
}

TEST_F(TestCompoundItem, addProperty)
{
    CompoundItem item;

    // Adding properties is only possible when item is created through the model,
    // since item itself know nothing about factories.
    EXPECT_THROW(item.addProperty("height", 42.0), std::runtime_error);

    SessionModel model;
    auto item2 = dynamic_cast<CompoundItem*>(model.insertNewItem(Constants::CompoundType));
    EXPECT_TRUE(item2 != nullptr);

    item2->addProperty("height", 42.0);
    EXPECT_TRUE(item2->isTag("height"));

    EXPECT_EQ(item2->childrenCount(), 1);
    EXPECT_EQ(item2->getItem("height")->modelType(), Constants::PropertyType);
}
