#include "comboproperty.h"
#include "google_test.h"
#include "toy_includes.h"

using namespace ModelView;

//! Tests of toy ShapeGroup in the context of model and viewmodel.

class TestToyShapeGroup : public ::testing::Test
{
public:
    ~TestToyShapeGroup();
};

TestToyShapeGroup::~TestToyShapeGroup() = default;

//! Toy multilayer as produced bo toy SampleModel.

TEST_F(TestToyShapeGroup, initialState)
{
    ToyItems::ShapeGroup item;

    EXPECT_EQ(item.currentIndex(), 1);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_TRUE(item.data(ItemDataRole::DATA).isValid());
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.children().size(), 3);

    // expected value in combo
    ComboProperty combo = item.data(ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical piramyd"}));
}

TEST_F(TestToyShapeGroup, setCurrentType)
{
    ToyItems::ShapeGroup item;
    const std::string expected_type = ToyItems::Constants::CylinderType;
    item.setCurrentType(expected_type);

    EXPECT_EQ(item.currentIndex(), 0);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentItem()->modelType(), expected_type);
    EXPECT_TRUE(item.data(ItemDataRole::DATA).isValid());
    EXPECT_EQ(item.children().size(), 3);

    // expected value in combo
    ComboProperty combo = item.data(ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical piramyd"}));
}
