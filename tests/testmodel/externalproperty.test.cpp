// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/externalproperty.h"

#include "google_test.h"
#include "mvvm/model/comparators.h"

using namespace ModelView;

class ExternalPropertyTest : public ::testing::Test {
};

TEST_F(ExternalPropertyTest, initialState)
{
    ExternalProperty property;
    EXPECT_FALSE(property.isValid());
    EXPECT_EQ(property.text(), "");
    EXPECT_EQ(property.identifier(), "");
    EXPECT_FALSE(property.color().isValid());
}

TEST_F(ExternalPropertyTest, constructor)
{
    ExternalProperty property("text", QColor(Qt::red), "123");
    EXPECT_TRUE(property.isValid());
    EXPECT_EQ(property.text(), "text");
    EXPECT_EQ(property.color(), QColor("red"));
    EXPECT_EQ(property.identifier(), "123");
}

TEST_F(ExternalPropertyTest, equalityOperators)
{
    ExternalProperty prop1a;
    ExternalProperty prop1b;

    EXPECT_TRUE(prop1a == prop1b);
    EXPECT_FALSE(prop1a < prop1b);

    ExternalProperty prop2a("text", QColor(Qt::red));
    ExternalProperty prop2b("text", QColor(Qt::red));
    EXPECT_TRUE(prop2a == prop2b);
    EXPECT_FALSE(prop2a < prop2b);

    EXPECT_FALSE(prop1a == prop2a);
}

TEST_F(ExternalPropertyTest, variantEquality)
{
    if (Comparators::registered()) {
        ExternalProperty prop1a;
        ExternalProperty prop1b;
        EXPECT_TRUE(QVariant::fromValue(prop1a) == QVariant::fromValue(prop1b));

        ExternalProperty prop2a("text", QColor(Qt::red));
        ExternalProperty prop2b("text", QColor(Qt::red));
        EXPECT_TRUE(QVariant::fromValue(prop2a) == QVariant::fromValue(prop2b));

        EXPECT_FALSE(QVariant::fromValue(prop1a) == QVariant::fromValue(prop2a));
    }
}
