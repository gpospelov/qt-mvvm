#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include "customvariants.h"
#include <memory>

class TestItemUtils : public ::testing::Test
{
public:
    ~TestItemUtils();
};

TestItemUtils::~TestItemUtils() = default;

//! Simple iteration over item and its children

TEST_F(TestItemUtils, iterateItem)
{
    std::vector<const SessionItem*> visited_items;

    auto fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
    };

    // iteration over nullptr
    Utils::iterate(nullptr, fun);
    EXPECT_TRUE(visited_items.empty());

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);

    // adding children
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);

    visited_items.clear();
    Utils::iterate(parent.get(), fun);

    expected = {parent.get(), child1, child2};
    EXPECT_EQ(visited_items, expected);
}

//! Conditional iteration over item and its children.

TEST_F(TestItemUtils, iterateIfItem)
{
    std::vector<const SessionItem*> visited_items;

    // function which will not let iterate over children
    std::function<bool(const SessionItem*)> fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
        return false;
    };

    // iteration over lonely parent
    std::unique_ptr<SessionItem> parent(new SessionItem);
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(-1, child1);
    parent->insertItem(-1, child2);

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate_if(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);
}

//! Iteration over root item of the model.

TEST_F(TestItemUtils, iterateModel)
{
    const model_type modelType("abc");
    SessionModel model;

    // building model
    auto parent1 = model.insertNewItem(modelType);
    auto parent2 = model.insertNewItem(modelType);
    auto child1 = model.insertNewItem(modelType, parent1);
    auto child2 = model.insertNewItem(modelType, parent1);

    std::vector<const SessionItem*> visited_items;
    auto fun = [&](const SessionItem* item ) {
        visited_items.push_back(item);
    };

    // iteration
    Utils::iterate(model.rootItem(), fun);

    std::vector<const SessionItem*> expected = {model.rootItem(), parent1, child1, child2, parent2};
    EXPECT_EQ(visited_items, expected);
}

//! Comparing types of variant.

TEST_F(TestItemUtils, VariantType)
{
    EXPECT_TRUE(Utils::VariantType(QVariant::fromValue(1.0))
                == Utils::VariantType(QVariant::fromValue(2.0)));
    EXPECT_FALSE(Utils::VariantType(QVariant::fromValue(1.0))
                 == Utils::VariantType(QVariant::fromValue(1)));
    EXPECT_FALSE(Utils::VariantType(QVariant::fromValue(1.0))
                 == Utils::VariantType(QVariant::fromValue(std::string("a"))));

    QVariant v1, v2;
    EXPECT_TRUE(Utils::VariantType(v1) == Utils::VariantType(v2));
    EXPECT_FALSE(Utils::VariantType(v1)
                 == Utils::VariantType(QVariant::fromValue(42.0)));

//    ComboProperty c1, c2;
//    EXPECT_TRUE(Utils::VariantType(c1.variant())
//                == Utils::VariantType(c2.variant()));
//    EXPECT_FALSE(Utils::VariantType(c1.variant())
//                 == Utils::VariantType(QVariant::fromValue(42.0)));
//    EXPECT_FALSE(Utils::VariantType(c1.variant())
//                 == Utils::VariantType(QVariant()));

//    ExternalProperty p1, p2;
//    EXPECT_TRUE(Utils::VariantType(p1.variant())
//                == Utils::VariantType(p2.variant()));
//    EXPECT_FALSE(Utils::VariantType(p1.variant())
//                 == Utils::VariantType(QVariant::fromValue(42.0)));
//    EXPECT_FALSE(Utils::VariantType(p1.variant())
//                 == Utils::VariantType(c1.variant()));
//    EXPECT_FALSE(Utils::VariantType(p1.variant())
//                 == Utils::VariantType(QVariant()));
}

//! Comparing types of variant.

TEST_F(TestItemUtils, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant intProperty = QVariant::fromValue(1);
    QVariant doubleProperty = QVariant::fromValue(42.0);
    QVariant stringProperty = QVariant::fromValue(std::string("string"));
    //    QVariant comboProperty = QVariant::fromValue(ComboProperty());
    //    QVariant externProperty = QVariant::fromValue(ExternalProperty());

    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, intProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, doubleProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, stringProperty));
//    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, comboProperty));
//    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, externProperty));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(intProperty, intProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(doubleProperty, doubleProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(stringProperty, stringProperty));
//    EXPECT_TRUE(Utils::CompatibleVariantTypes(comboProperty, comboProperty));
//    EXPECT_TRUE(Utils::CompatibleVariantTypes(externProperty, externProperty));

    EXPECT_FALSE(Utils::CompatibleVariantTypes(intProperty, doubleProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(intProperty, stringProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(doubleProperty, stringProperty));
//    EXPECT_FALSE(Utils::CompatibleVariantTypes(doubleProperty, comboProperty));
//    EXPECT_FALSE(Utils::CompatibleVariantTypes(comboProperty, doubleProperty));
}

//! Test variant equality reported by SessionItemUtils::isTheSame

TEST_F(TestItemUtils, IsTheSameVariant)
{
    // comparing undefined variants
    QVariant v1, v2;
    EXPECT_TRUE(Utils::IsTheSame(v1, v2));

    // comparing QVariant based on double
    EXPECT_TRUE(Utils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1.0)));
    EXPECT_FALSE(Utils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(2.0)));

    // comparing QVariant based on strings
    EXPECT_TRUE(Utils::IsTheSame(QVariant::fromValue(std::string("a")),
                                            QVariant::fromValue(std::string("a"))));
    EXPECT_FALSE(Utils::IsTheSame(QVariant::fromValue(std::string("a")),
                                             QVariant::fromValue(std::string("b"))));

    // Variants of std::string and QString
    EXPECT_FALSE(Utils::IsTheSame(QVariant::fromValue(std::string("a")),
                                             QVariant::fromValue(QString("a"))));

    // comparing variants of different type
//    EXPECT_FALSE(Utils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1)));

//    // comparing custom variants (should be always false)
//    ExternalProperty p1, p2;
//    EXPECT_FALSE(Utils::IsTheSame(p1.variant(), p2.variant()));
//    EXPECT_FALSE(Utils::IsTheSame(p1.variant(), QVariant::fromValue(42.0)));

//    ComboProperty c1, c2;
//    EXPECT_FALSE(Utils::IsTheSame(c1.variant(), c2.variant()));
//    EXPECT_FALSE(Utils::IsTheSame(c1.variant(), QVariant::fromValue(42.0)));

//    EXPECT_FALSE(Utils::IsTheSame(p1.variant(), c1.variant()));
}
