#include <mvvm/model/comboproperty.h>
#include <mvvm/model/comparators.h>
#include "google_test.h"

using namespace ModelView;

class TestComboProperty : public ::testing::Test
{
public:
    ~TestComboProperty();
};

TestComboProperty::~TestComboProperty() = default;

TEST_F(TestComboProperty, initialState)
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

TEST_F(TestComboProperty, createFrom)
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

TEST_F(TestComboProperty, setValue)
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

TEST_F(TestComboProperty, setCurrentIndex)
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

TEST_F(TestComboProperty, setValues)
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

TEST_F(TestComboProperty, setSelected)
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

TEST_F(TestComboProperty, fromStream)
{
    ComboProperty combo = ComboProperty() << "a1" << "a2";
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

TEST_F(TestComboProperty, fromVectorStream)
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

TEST_F(TestComboProperty, setSringOfValues)
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

TEST_F(TestComboProperty, setStringOfSelections)
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

TEST_F(TestComboProperty, comboEquality)
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

//! Check equality of ComboPeroperty's variants.
//! If comparators are not registered, the behavior is undefined.

TEST_F(TestComboProperty, variantEquality)
{
    ComboProperty c1 = ComboProperty() << "a1"
                                       << "a2";
    ComboProperty c2 = ComboProperty() << "a1"
                                       << "a2";

    if (ModelView::Comparators::registered()) {
        EXPECT_TRUE(c1.variant() == c2.variant());

        c2 << "a3";
        c2.setValue("a2");

        EXPECT_TRUE(c1.variant() != c2.variant());
        EXPECT_FALSE(c1.variant() == c2.variant());

        c1 << "a3";
        c1.setValue("a2");

        EXPECT_TRUE(c1.variant() == c2.variant());
        EXPECT_FALSE(c1.variant() != c2.variant());

        c1.setStringOfSelections("0");
        c2.setStringOfSelections("1");
        EXPECT_TRUE(c1.variant() != c2.variant());
        EXPECT_FALSE(c1.variant() == c2.variant());
    }
}
