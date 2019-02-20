#include "google_test.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include "customvariants.h"
#include "taginfo.h"
#include <memory>

using namespace ModelView;

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
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    std::vector<const SessionItem*> expected = {parent.get()};
    Utils::iterate(parent.get(), fun);
    EXPECT_EQ(visited_items, expected);

    // adding children
    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(child1, -1);
    parent->insertItem(child2, -1);

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
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    auto child1 = new SessionItem;
    auto child2 = new SessionItem;
    parent->insertItem(child1, -1);
    parent->insertItem(child2, -1);

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
    parent1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);
    parent2->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);
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
    QVariant undefined;
    QVariant intProperty = QVariant::fromValue(1);
    QVariant doubleProperty = QVariant::fromValue(42.0);
    QVariant stringProperty = QVariant::fromValue(std::string("abc"));
    std::vector<double> vec {1, 2};
    QVariant vectorProperty = QVariant::fromValue(vec);

    EXPECT_TRUE(Utils::VariantType(undefined) == Utils::VariantType(QVariant()));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(intProperty));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(doubleProperty));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(stringProperty));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(vectorProperty));

    EXPECT_TRUE(Utils::VariantType(intProperty) == Utils::VariantType(QVariant::fromValue(2)));
    EXPECT_FALSE(Utils::VariantType(intProperty) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(intProperty) == Utils::VariantType(doubleProperty));
    EXPECT_FALSE(Utils::VariantType(intProperty) == Utils::VariantType(stringProperty));
    EXPECT_FALSE(Utils::VariantType(intProperty) == Utils::VariantType(vectorProperty));

    EXPECT_TRUE(Utils::VariantType(doubleProperty) == Utils::VariantType(QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::VariantType(doubleProperty) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(doubleProperty) == Utils::VariantType(intProperty));
    EXPECT_FALSE(Utils::VariantType(doubleProperty) == Utils::VariantType(stringProperty));
    EXPECT_FALSE(Utils::VariantType(doubleProperty) == Utils::VariantType(vectorProperty));

    EXPECT_TRUE(Utils::VariantType(stringProperty) == Utils::VariantType(QVariant::fromValue(std::string("cde"))));
    EXPECT_FALSE(Utils::VariantType(stringProperty) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(stringProperty) == Utils::VariantType(intProperty));
    EXPECT_FALSE(Utils::VariantType(stringProperty) == Utils::VariantType(doubleProperty));
    EXPECT_FALSE(Utils::VariantType(stringProperty) == Utils::VariantType(vectorProperty));

    std::vector<double> vec2 {1, 2};
    EXPECT_TRUE(Utils::VariantType(vectorProperty) == Utils::VariantType(QVariant::fromValue(vec2)));
    EXPECT_FALSE(Utils::VariantType(vectorProperty) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(vectorProperty) == Utils::VariantType(intProperty));
    EXPECT_FALSE(Utils::VariantType(vectorProperty) == Utils::VariantType(doubleProperty));
    EXPECT_FALSE(Utils::VariantType(vectorProperty) == Utils::VariantType(stringProperty));
}

//! Variant compatibility.
//! For the moment, undefined variant

TEST_F(TestItemUtils, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant intProperty = QVariant::fromValue(1);
    QVariant doubleProperty = QVariant::fromValue(42.0);
    QVariant stringProperty = QVariant::fromValue(std::string("string"));
    std::vector<double> vec {1, 2};
    QVariant vectorProperty = QVariant::fromValue(vec);

    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, intProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, doubleProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, stringProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, vectorProperty));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(intProperty, intProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(intProperty, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(intProperty, doubleProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(intProperty, stringProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(intProperty, vectorProperty));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(doubleProperty, doubleProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(doubleProperty, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(doubleProperty, stringProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(doubleProperty, intProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(doubleProperty, vectorProperty));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(stringProperty, stringProperty));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(stringProperty, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(stringProperty, intProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(stringProperty, doubleProperty));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(stringProperty, vectorProperty));
}

//! Test variant equality reported by SessionItemUtils::isTheSame

TEST_F(TestItemUtils, IsTheSameVariant)
{
    QVariant undefined;
    QVariant intProperty = QVariant::fromValue(1);
    QVariant doubleProperty = QVariant::fromValue(42.0);
    QVariant stringProperty = QVariant::fromValue(std::string("string"));
    std::vector<double> vec {1, 2};
    QVariant vectorProperty = QVariant::fromValue(vec);

    // undefined variant
    EXPECT_TRUE(Utils::IsTheSame(undefined, QVariant()));
    EXPECT_FALSE(Utils::IsTheSame(undefined, intProperty));
    EXPECT_FALSE(Utils::IsTheSame(undefined, doubleProperty));
    EXPECT_FALSE(Utils::IsTheSame(undefined, stringProperty));
    EXPECT_FALSE(Utils::IsTheSame(undefined, vectorProperty));

    // int variant
    EXPECT_TRUE(Utils::IsTheSame(intProperty, intProperty));
    EXPECT_FALSE(Utils::IsTheSame(intProperty, undefined));
    EXPECT_FALSE(Utils::IsTheSame(intProperty, QVariant::fromValue(2)));
    EXPECT_FALSE(Utils::IsTheSame(intProperty, doubleProperty));
    EXPECT_FALSE(Utils::IsTheSame(intProperty, stringProperty));
    EXPECT_FALSE(Utils::IsTheSame(intProperty, vectorProperty));

    // double variant
    EXPECT_TRUE(Utils::IsTheSame(doubleProperty, doubleProperty));
    EXPECT_FALSE(Utils::IsTheSame(doubleProperty, undefined));
    EXPECT_FALSE(Utils::IsTheSame(doubleProperty, QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::IsTheSame(doubleProperty, intProperty));
    EXPECT_FALSE(Utils::IsTheSame(doubleProperty, stringProperty));
    EXPECT_FALSE(Utils::IsTheSame(doubleProperty, vectorProperty));

    // string variant
    EXPECT_TRUE(Utils::IsTheSame(stringProperty, stringProperty));
    EXPECT_FALSE(Utils::IsTheSame(stringProperty, undefined));
    EXPECT_FALSE(Utils::IsTheSame(stringProperty, QVariant::fromValue(std::string("cde"))));
    EXPECT_FALSE(Utils::IsTheSame(stringProperty, intProperty));
    EXPECT_FALSE(Utils::IsTheSame(stringProperty, doubleProperty));
    EXPECT_FALSE(Utils::IsTheSame(stringProperty, vectorProperty));

    // vector variant
    std::vector<double> vec2 {1, 2, 3}, vec3{1, 1};
    EXPECT_TRUE(Utils::IsTheSame(vectorProperty, vectorProperty));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, QVariant::fromValue(vec2)));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, QVariant::fromValue(vec3)));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, undefined));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, intProperty));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, doubleProperty));
    EXPECT_FALSE(Utils::IsTheSame(vectorProperty, stringProperty));
}

//! Test translation of variants

TEST_F(TestItemUtils, variantTranslation)
{
    // from Variant based on std::string to variant based on QString
    QVariant stdstringVariant = QVariant::fromValue(std::string("abc"));
    QVariant qstringVariant = ModelView::toQtVariant(stdstringVariant);
    QVariant expected("abc");
    EXPECT_FALSE(qstringVariant == stdstringVariant);
    EXPECT_TRUE(qstringVariant == expected);

    // from variant based on QString to variant based on std::string
    qstringVariant = QVariant::fromValue(QString("qwerty"));
    stdstringVariant = ModelView::toCustomVariant(qstringVariant);
    expected = QVariant::fromValue(std::string("qwerty"));
    EXPECT_TRUE(stdstringVariant == expected);

    // Double variant should be unchanged
    QVariant value(42.0);
    EXPECT_TRUE(ModelView::toCustomVariant(value) == QVariant::fromValue(42.0));
    EXPECT_TRUE(ModelView::toQtVariant(value) == QVariant::fromValue(42.0));
}

TEST_F(TestItemUtils, itemCopyNumber)
{
    SessionModel model;

    auto parent = model.insertNewItem("parent");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    const std::string model_a("model_a");
    const std::string model_b("model_b");
    auto child1 = model.insertNewItem(model_a, parent);
    auto child2 = model.insertNewItem(model_a, parent);
    auto child3 = model.insertNewItem(model_b, parent);

    EXPECT_EQ(Utils::CopyNumber(child1), 0);
    EXPECT_EQ(Utils::CopyNumber(child2), 1);
    EXPECT_EQ(Utils::CopyNumber(child3), -1);
}

