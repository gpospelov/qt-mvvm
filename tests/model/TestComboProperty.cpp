#include "google_test.h"
#include "comboproperty.h"
#include "comparators.h"

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
    EXPECT_EQ(combo.getValue(), "");
    EXPECT_EQ(combo.getValues(), QStringList());
    EXPECT_EQ(combo.toolTips(), QStringList());
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.stringOfValues(), "");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>());
}

TEST_F(TestComboProperty, factoryMethods)
{
    // initialization from list sets values only, no index selected
    QStringList expected = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty::fromList(expected);
    EXPECT_EQ(combo.getValues(), expected);
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.getValue(), "");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>());
}

TEST_F(TestComboProperty, setValues)
{
    // seting values through stream
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;
    EXPECT_EQ(combo.getValues(), expectedValues);
    EXPECT_EQ(combo.getValue(), QString("a1"));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));

    // setting values from setter, old values have to be overriden
    QStringList newValues = QStringList() << "b1" << "b2" << "b3";
    combo.setValues(newValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.getValues(), newValues);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));

    // setting new/old values through setter, old value should be preserved
    newValues = QStringList() << "c1" << "b1" << "c2";
    combo.setValues(newValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.getValues(), newValues);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({1}));
}

TEST_F(TestComboProperty, setCurrentIndex)
{
    ComboProperty combo;
    EXPECT_EQ(combo.currentIndex(), -1);

    combo << "c1" << "c2";
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));

    combo.setValue("c2");
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({1}));

    combo.setCurrentIndex(0);
    EXPECT_EQ(combo.getValue(), QString("c1"));
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));
}

TEST_F(TestComboProperty, stringOfValues)
{
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;

    EXPECT_EQ(combo.stringOfValues(), QString("a1;a2"));
    EXPECT_EQ(combo.getValue(), QString("a1"));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));

    // setting string of values, current value should change
    QString stringOfValues("b1;b2;b3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));

    // setting new string of values, containing current value. Current values should remain.
    stringOfValues = QString("c1;b1;c3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({1}));
}

TEST_F(TestComboProperty, selectedIndices)
{
    QStringList expectedValues = QStringList() << "a1" << "a2" << "a3";
    ComboProperty combo = ComboProperty() << expectedValues;

    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.getValue(), "a1");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));
    EXPECT_EQ(combo.selectedValues(), QStringList({"a1"}));

    // selecting already selected element, nothing should change
    combo.setSelected(0);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.getValue(), "a1");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));
    EXPECT_EQ(combo.selectedValues(), QStringList({"a1"}));

    // deselecting index
    combo.setSelected(0, false);
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.getValue(), "");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>());
    EXPECT_EQ(combo.selectedValues(), QStringList());

    // selecting two indeces
    combo.setSelected(1, true);
    combo.setSelected(2, true);
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.getValue(), "a2");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({1, 2}));
    EXPECT_EQ(combo.selectedValues(), QStringList({"a2", "a3"}));

    // selecting by name
    combo.setSelected("a2", false);
    combo.setSelected("a1", true);
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.getValue(), "a1");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0, 2}));
    EXPECT_EQ(combo.selectedValues(), QStringList({"a1", "a3"}));
}

TEST_F(TestComboProperty, stringOfSelections)
{
    ComboProperty combo;
    EXPECT_EQ(combo.stringOfSelections(), "");

    // checking the content of stringOfSelections
    combo.setValues(QStringList({"a1","a2","a3"}));
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0");

    combo.setSelected(2, true);
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0, 2}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0,2");

    // setting string of selections
    combo.setStringOfSelections("");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({}));
    EXPECT_EQ(combo.currentIndex(), -1);
    EXPECT_EQ(combo.stringOfSelections(), "");

    combo.setStringOfSelections("1,2");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({1, 2}));
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.stringOfSelections(), "1,2");

    combo.setStringOfSelections("0,42");
    EXPECT_EQ(combo.selectedIndices(), QVector<int>({0}));
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.stringOfSelections(), "0");
}

TEST_F(TestComboProperty, comboEquality)
{
    ComboProperty c1;
    ComboProperty c2;
    EXPECT_TRUE(c1 == c2);

    c1 << "a1" << "a2";
    c2 << "a1" << "a2";
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
    c1 = ComboProperty() << "a1" << "a2" << "a3";
    c2 = ComboProperty() << "a1" << "a2" << "a3";
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
    ComboProperty c1 = ComboProperty() << "a1" << "a2";
    ComboProperty c2 = ComboProperty() << "a1" << "a2";

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

//TEST_F(TestComboProperty, comboXML)
//{
//    // Writing combo to XML
//    ComboProperty combo = ComboProperty() << "a1" << "a2" << "a3";
//    combo.setStringOfSelections("0,2");

//    QString expected = "<Parameter ParType=\"ComboProperty\" ParRole=\"0\" ParValue=\"0,2\" "
//                       "ParExt=\"a1;a2;a3\"/>";
//    EXPECT_EQ(TestUtils::propertyToXML(combo), expected);

//    // reading from XML
//    ComboProperty combo_property = propertyFromXML(expected);
//    EXPECT_EQ(combo_property.getValue(), QString("a1"));
//    EXPECT_EQ(combo_property.stringOfValues(), QString("a1;a2;a3"));
//    EXPECT_EQ(combo_property.stringOfSelections(), QString("0,2"));
//    EXPECT_TRUE(combo_property == combo);
//}
