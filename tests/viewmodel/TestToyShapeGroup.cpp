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
    ASSERT_EQ(item.children().size(), 3);

    // parent child relationship
    EXPECT_EQ(item.children().at(0)->parent(), &item);
    EXPECT_EQ(item.children().at(1)->parent(), &item);
    EXPECT_EQ(item.children().at(2)->parent(), &item);

    // expected value in combo
    ComboProperty combo = item.data(ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical piramyd"}));
}

TEST_F(TestToyShapeGroup, setCurrentType)
{
    ToyItems::ShapeGroup item;
    item.setCurrentType(ToyItems::Constants::CylinderType);

    EXPECT_EQ(item.currentIndex(), 1);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentItem()->modelType(), ToyItems::Constants::SphereType);
    EXPECT_TRUE(item.data(ItemDataRole::DATA).isValid());
    EXPECT_EQ(item.children().size(), 3);

    // expected value in combo
    ComboProperty combo = item.data(ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical piramyd"}));
}

TEST_F(TestToyShapeGroup, inModelContext)
{
    ToyItems::SampleModel model;
    auto item = dynamic_cast<GroupItem *>(model.insertNewItem(ToyItems::Constants::ShapeGroupType));
    ASSERT_TRUE(item != nullptr);

    EXPECT_EQ(item->currentIndex(), 1);
    ASSERT_TRUE(item->currentItem() != nullptr);
    EXPECT_TRUE(item->data(ItemDataRole::DATA).isValid());
    EXPECT_EQ(item->currentType(), item->currentItem()->modelType());
    EXPECT_EQ(item->children().size(), 3);

    // parent child relationship
    EXPECT_EQ(item->children().at(0)->parent(), item);
    EXPECT_EQ(item->children().at(1)->parent(), item);
    EXPECT_EQ(item->children().at(2)->parent(), item);

    // model relationship
    EXPECT_EQ(item->children().at(0)->model(), &model);
    EXPECT_EQ(item->children().at(1)->model(), &model);
    EXPECT_EQ(item->children().at(2)->model(), &model);
}

TEST_F(TestToyShapeGroup, setDataInModelContext)
{
    ToyItems::SampleModel model;
    auto item = dynamic_cast<GroupItem *>(model.insertNewItem(ToyItems::Constants::ShapeGroupType));
    ASSERT_TRUE(item != nullptr);

    // initial status
    EXPECT_EQ(item->currentIndex(), 1);
    EXPECT_EQ(item->currentType(), ToyItems::Constants::SphereType);
    ComboProperty combo = model.data(item, ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);

    // setting through combo
    combo.setCurrentIndex(0);
    model.setData(item, combo.variant(), ItemDataRole::DATA);

    EXPECT_EQ(item->currentIndex(), 0);
    EXPECT_EQ(item->currentType(), ToyItems::Constants::CylinderType);

}
