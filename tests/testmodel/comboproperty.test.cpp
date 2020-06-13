// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/comparators.h>
#include <stdexcept>

using namespace ModelView;

class ComboPropertyTest : public ::testing::Test
{
public:
    ~ComboPropertyTest();
};

ComboPropertyTest::~ComboPropertyTest() = default;

TEST_F(ComboPropertyTest, initialState)
{
    ComboProperty combo;
    EXPECT_EQ(combo.value(), "");
    EXPECT_EQ(combo.values(), std::vector<std::string>());
    EXPECT_EQ(combo.toolTips(), std::vector<std::string>());
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.stringOfValues(), "");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>());
    EXPECT_EQ(combo.label(), "None");
}

TEST_F(ComboPropertyTest, createFrom)
{
    // from vector of values, first item should be selected
    std::vector<std::string> expected{"a1", "a2"};
    ComboProperty combo = ComboProperty::createFrom(expected);
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // from vector of values, selection provided
    expected = {"b1", "b2", "b3"};
    combo = ComboProperty::createFrom(expected, "b2");
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "b2");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
}

TEST_F(ComboPropertyTest, setValue)
{
    std::vector<std::string> expected{"a1", "a2"};
    ComboProperty combo = ComboProperty::createFrom(expected);

    // setting second value
    combo.setValue("a2");
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "a2");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));

    // setting non-existing value
    EXPECT_THROW(combo.setValue("c0"), std::runtime_error);
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "a2");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
}

TEST_F(ComboPropertyTest, setCurrentIndex)
{
    std::vector<std::string> expected{"c1", "c2", "c3"};
    ComboProperty combo = ComboProperty::createFrom(expected);

    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));
    EXPECT_EQ(combo.values(), expected);

    combo.setCurrentIndex(1);
    EXPECT_EQ(combo.value(), std::string("c2"));
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));

    // setting unexpected index
    EXPECT_THROW(combo.setCurrentIndex(3), std::runtime_error);
    EXPECT_EQ(combo.value(), std::string("c2"));
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
}

TEST_F(ComboPropertyTest, setValues)
{
    // seting values through stream
    std::vector<std::string> expectedValues{"a1", "a2"};
    ComboProperty combo = ComboProperty::createFrom(expectedValues);

    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.value(), std::string("a1"));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // setting values from setter, old values have to be overriden
    std::vector<std::string> newValues{"b1", "b2", "b3"};
    combo.setValues(newValues);
    EXPECT_EQ(combo.value(), std::string("b1"));
    EXPECT_EQ(combo.values(), newValues);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // setting new/old values through setter, old value should be preserved
    newValues = {"c1", "b1", "c2"};
    combo.setValues(newValues);
    EXPECT_EQ(combo.value(), std::string("b1"));
    EXPECT_EQ(combo.values(), newValues);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));

    // setting empty list shouldn't change anything
    std::vector<std::string> empty;
    combo.setValues(empty);
    EXPECT_EQ(combo.value(), std::string("b1"));
    EXPECT_EQ(combo.values(), newValues);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
}

TEST_F(ComboPropertyTest, setSelected)
{
    std::vector<std::string> expectedValues = {"a1", "a2", "a3"};
    ComboProperty combo = ComboProperty::createFrom(expectedValues);

    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>({"a1"}));

    // selecting already selected element, nothing should change
    combo.setSelected(0);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>({"a1"}));

    // deselecting index
    combo.setSelected(0, false);
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.value(), "");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>());
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>());

    // selecting two indeces
    combo.setSelected(1, true);
    combo.setSelected(2, true);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "a2");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1, 2}));
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>({"a2", "a3"}));

    // selecting by name
    combo.setSelected("a2", false);
    combo.setSelected("a1", true);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0, 2}));
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>({"a1", "a3"}));

    // setting current index invalidates selection
    combo.setCurrentIndex(1);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "a2");
    EXPECT_EQ(combo.values(), expectedValues);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
    EXPECT_EQ(combo.selectedValues(), std::vector<std::string>({"a2"}));
}

TEST_F(ComboPropertyTest, fromStream)
{
    ComboProperty combo = ComboProperty() << "a1"
                                          << "a2";
    std::vector<std::string> expected{"a1", "a2"};
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // adding more
    combo << "c0";
    expected = {"a1", "a2", "c0"};
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // setting another index, adding more, state should be preserved
    combo.setCurrentIndex(1);
    combo.setSelected(2, true);
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.value(), "a2");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1, 2}));
    combo << "c1";
    expected = {"a1", "a2", "c0", "c1"};
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 1);
}

TEST_F(ComboPropertyTest, fromVectorStream)
{
    std::vector<std::string> expected{"a1", "a2"};
    ComboProperty combo = ComboProperty::createFrom(expected);
    combo.setSelected(0, true);
    combo.setSelected(1, true);

    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0, 1}));

    // adding from vector stream, old selection state should be preserved
    std::vector<std::string> more{"c1", "c2"};
    combo << more;
    expected = {"a1", "a2", "c1", "c2"};
    EXPECT_EQ(combo.values(), expected);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.value(), "a1");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0, 1}));
}

TEST_F(ComboPropertyTest, setSringOfValues)
{
    std::vector<std::string> expectedValues = {"a1", "a2"};
    ComboProperty combo = ComboProperty::createFrom(expectedValues);

    EXPECT_EQ(combo.stringOfValues(), std::string("a1;a2"));
    EXPECT_EQ(combo.value(), std::string("a1"));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // setting string of values, current value should change
    std::string stringOfValues("b1;b2;b3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.value(), std::string("b1"));
    EXPECT_EQ(combo.values(), std::vector<std::string>({"b1", "b2", "b3"}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));

    // setting new string of values, containing current value. Current values should remain.
    stringOfValues = std::string("c1;b1;c3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.value(), std::string("b1"));
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1}));
}

TEST_F(ComboPropertyTest, setStringOfSelections)
{
    ComboProperty combo;
    EXPECT_EQ(combo.stringOfSelections(), "");

    // checking the content of stringOfSelections
    combo.setValues(std::vector<std::string>({"a1", "a2", "a3"}));
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0");

    combo.setSelected(2, true);
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0, 2}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0,2");

    // setting string of selections
    combo.setStringOfSelections("");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({}));
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.stringOfSelections(), "");

    combo.setStringOfSelections("1,2");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({1, 2}));
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.stringOfSelections(), "1,2");

    combo.setStringOfSelections("0,42");
    EXPECT_EQ(combo.selectedIndices(), std::vector<int>({0}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0");
}

TEST_F(ComboPropertyTest, comboEqualityDiffIndex)
{
    ComboProperty c1 = ComboProperty::createFrom({"a1", "a2"});
    ComboProperty c2 = ComboProperty::createFrom({"a1", "a2"});

    c1.setValue("a1");
    c2.setValue("a2");
    EXPECT_TRUE(c1 != c2);

    c2.setValue("a1");
    EXPECT_TRUE(c1 == c2);
}

TEST_F(ComboPropertyTest, comboEqualityDiffList)
{
    ComboProperty c1;
    ComboProperty c2;
    EXPECT_TRUE(c1 == c2);

    c1 << "a1"
       << "a2";
    c2 << "a1"
       << "a2";
    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 != c2);

    c2 << "a3";
    EXPECT_TRUE(c1 != c2);
    EXPECT_FALSE(c1 == c2);
    c2.setValue("a2");
    EXPECT_TRUE(c1 != c2);
    EXPECT_FALSE(c1 == c2);

    c1 << "a3";
    c1.setValue("a2");
    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 != c2);

    // with selection indices
    c1 = ComboProperty() << "a1"
                         << "a2"
                         << "a3";
    c2 = ComboProperty() << "a1"
                         << "a2"
                         << "a3";
    EXPECT_TRUE(c1 == c2);

    c2.setSelected(0, false);
    c2.setSelected(2, true);
    EXPECT_TRUE(c1 != c2);

    c1.setStringOfSelections("2");
    c2.setStringOfSelections("2");
    EXPECT_TRUE(c1 == c2);
}

//! Check equality of ComboProperty's variants.
//! If comparators are not registered, the behavior is undefined.

TEST_F(ComboPropertyTest, variantEqualityDiffLists)
{
    if (ModelView::Comparators::registered()) {
        ComboProperty c1 = ComboProperty() << "a1"
                                           << "a2";
        ComboProperty c2 = ComboProperty() << "a1"
                                           << "a2";

        EXPECT_TRUE(QVariant::fromValue(c1) == QVariant::fromValue(c2));

        c2 << "a3";
        c2.setValue("a2");

        EXPECT_TRUE(QVariant::fromValue(c1) != QVariant::fromValue(c2));
        EXPECT_FALSE(QVariant::fromValue(c1) == QVariant::fromValue(c2));

        c1 << "a3";
        c1.setValue("a2");

        EXPECT_TRUE(QVariant::fromValue(c1) == QVariant::fromValue(c2));
        EXPECT_FALSE(QVariant::fromValue(c1) != QVariant::fromValue(c2));

        c1.setStringOfSelections("0");
        c2.setStringOfSelections("1");
        EXPECT_TRUE(QVariant::fromValue(c1) != QVariant::fromValue(c2));
        EXPECT_FALSE(QVariant::fromValue(c1) == QVariant::fromValue(c2));
    }
}

//! Check equality of ComboProperty's variants when only selected item differs.

TEST_F(ComboPropertyTest, variantEqualityDiffIndex)
{
    if (ModelView::Comparators::registered()) {
        ComboProperty c1 = ComboProperty::createFrom({"a1", "a2"});
        ComboProperty c2 = ComboProperty::createFrom({"a1", "a2"});

        c1.setValue("a1");
        c2.setValue("a2");

        EXPECT_FALSE(QVariant::fromValue(c1) == QVariant::fromValue(c2));
        EXPECT_TRUE(QVariant::fromValue(c1) != QVariant::fromValue(c2));

        c2.setValue("a1");
        EXPECT_TRUE(QVariant::fromValue(c1) == QVariant::fromValue(c2));
        EXPECT_FALSE(QVariant::fromValue(c1) != QVariant::fromValue(c2));
    }

    if (ModelView::Comparators::registered()) {
        ComboProperty c1 = ComboProperty::createFrom({"a1", "a2"});
        ComboProperty c2 = ComboProperty::createFrom({"a1", "a2"});

        c1.setValue("a1");
        c2.setValue("a2");

        std::vector<QVariant> variants = {QVariant::fromValue(c1), QVariant::fromValue(c2)};

        EXPECT_FALSE(variants[0] == variants[1]);
        EXPECT_TRUE(variants[0] != variants[1]);
    }
}
