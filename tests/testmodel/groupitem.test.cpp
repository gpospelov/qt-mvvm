// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/groupitem.h"

#include "google_test.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

namespace {
const std::string SphereType = "Sphere";
const std::string CylinderType = "Cylinder";
const std::string SphereLabel = "SphereLabel";
const std::string CylinderLabel = "CylinderLabel";
} // namespace

//! Testing GroupItem class.

class GroupItemTest : public ::testing::Test {
public:
    //! Test items.

    //! Empty group item.
    class EmptyGroupItem : public GroupItem {
    public:
        EmptyGroupItem() : GroupItem("EmptyGroupItem") {}
    };

    //! ShereItem (content for GroupItem).
    class SphereItem : public CompoundItem {
    public:
        SphereItem() : CompoundItem(SphereType) { addProperty("Radius", 8.0); }
    };

    //! CyinederItem (content for GroupItem).
    class CylinderItem : public CompoundItem {
    public:
        CylinderItem() : CompoundItem(CylinderType)
        {
            addProperty("Radius", 8.0);
            addProperty("Height", 10.0);
        }
    };

    //! Test group item holding sphere and group items.
    class TestGroupItem : public GroupItem {
    public:
        TestGroupItem() : GroupItem("TestGroupItem")
        {
            addToGroup<SphereItem>(SphereLabel);
            addToGroup<CylinderItem>(); // to check usage of default label
        }
    };

    //! The model capable of holidng group item.
    class TestModel : public SessionModel {
    public:
        TestModel() : SessionModel("TestModel") { registerItem<TestGroupItem>(); }
    };
};

//! Initial state of the group item.

TEST_F(GroupItemTest, emptyGroupInitialState)
{
    EmptyGroupItem item;
    EXPECT_EQ(item.currentIndex(), -1);
    EXPECT_EQ(item.currentItem(), nullptr);
    EXPECT_EQ(item.currentType(), "");
    EXPECT_TRUE(item.hasData());
    EXPECT_TRUE(item.children().empty());
    EXPECT_THROW(item.setCurrentType("abc"), std::runtime_error);
}

//! Initial state of TestGroupItem

TEST_F(GroupItemTest, testGroupItemInitialState)
{
    TestGroupItem item;

    EXPECT_EQ(item.currentIndex(), 0);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_TRUE(item.data<QVariant>().isValid());
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentType(), SphereType);
    ASSERT_EQ(item.children().size(), 2);

    // parent child relationship
    EXPECT_EQ(item.children().at(0)->parent(), &item);
    EXPECT_EQ(item.children().at(1)->parent(), &item);

    // expected value in combo
    auto combo = item.data<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.values(), std::vector<std::string>({SphereLabel, CylinderType}));
}

TEST_F(GroupItemTest, setCurrentType)
{
    TestGroupItem item;
    item.setCurrentType(CylinderType);

    EXPECT_EQ(item.currentIndex(), 1);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentItem()->modelType(), CylinderType);
    EXPECT_TRUE(item.data<QVariant>().isValid());
    EXPECT_EQ(item.children().size(), 2);

    // expected value in combo
    auto combo = item.data<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.values(), std::vector<std::string>({SphereLabel, CylinderType}));
}

TEST_F(GroupItemTest, currentItemNoConst)
{
    TestGroupItem item;
    item.currentItem()->setProperty("Radius", 42.0);
    EXPECT_EQ(item.currentItem()->property<double>("Radius"), 42.0);
}

TEST_F(GroupItemTest, inModelContext)
{
    TestModel model;
    auto item = model.insertItem<TestGroupItem>();
    ASSERT_TRUE(item != nullptr);

    EXPECT_EQ(item->currentIndex(), 0);
    ASSERT_TRUE(item->currentItem() != nullptr);
    EXPECT_TRUE(item->data<QVariant>().isValid());
    EXPECT_EQ(item->currentType(), item->currentItem()->modelType());
    EXPECT_EQ(item->children().size(), 2);

    // parent child relationship
    EXPECT_EQ(item->children().at(0)->parent(), item);
    EXPECT_EQ(item->children().at(1)->parent(), item);

    // model relationship
    EXPECT_EQ(item->children().at(0)->model(), &model);
    EXPECT_EQ(item->children().at(1)->model(), &model);
}

TEST_F(GroupItemTest, setDataInModelContext)
{
    TestModel model;
    auto item = model.insertItem<TestGroupItem>();
    ASSERT_TRUE(item != nullptr);

    auto combo = model.data(item, ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 0);

    // setting through combo
    combo.setCurrentIndex(1);
    model.setData(item, QVariant::fromValue(combo), ItemDataRole::DATA);

    EXPECT_EQ(item->currentIndex(), 1);
    EXPECT_EQ(item->currentType(), CylinderType);
}
