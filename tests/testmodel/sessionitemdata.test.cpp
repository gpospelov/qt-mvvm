// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/sessionitemdata.h"

#include "google_test.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/mvvm_types.h"
#include <stdexcept>

using namespace ModelView;

//! Test of SessionItemData.

class SessionItemDataTest : public ::testing::Test {
};

//! Initial state of SessionItemData object.

TEST_F(SessionItemDataTest, initialState)
{
    SessionItemData data;
    EXPECT_TRUE(data.roles().empty());
    EXPECT_FALSE(data.data(Qt::DisplayRole).isValid());
}

//! Basic setData, data operations.

TEST_F(SessionItemDataTest, setDataDouble)
{
    SessionItemData data;

    const int role(ItemDataRole::DATA);
    const QVariant variant(42.0);

    // setting variant for role
    EXPECT_TRUE(data.setData(variant, role));
    std::vector<int> expected{role};
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == variant);

    // setting same data twice
    EXPECT_FALSE(data.setData(variant, role));
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == variant);

    // changing the data
    EXPECT_TRUE(data.setData(QVariant(43.0), role));
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == QVariant(43.0));

    // setting invalid variant for the role will remove data
    EXPECT_TRUE(data.setData(QVariant(), role));
    EXPECT_TRUE(data.roles().empty());
    EXPECT_FALSE(data.data(role).isValid());
}

//! Basic setData, data operations.

TEST_F(SessionItemDataTest, setDataComboProperty)
{
    SessionItemData data;
    ComboProperty c1 = ComboProperty::createFrom({"a1", "a2"});
    ComboProperty c2 = ComboProperty::createFrom({"a1", "a2"});
    c1.setValue("a1");
    c2.setValue("a2");

    const int role(ItemDataRole::DATA);

    // setting variant for role
    EXPECT_TRUE(data.setData(QVariant::fromValue(c1), role));
    EXPECT_EQ(data.data(role).value<ComboProperty>(), c1);

    // setting same data twice
    EXPECT_FALSE(data.setData(QVariant::fromValue(c1), role));

    // setting another data
    EXPECT_TRUE(data.setData(QVariant::fromValue(c2), role));
    EXPECT_EQ(data.data(role).value<ComboProperty>(), c2);
}

//! Using different roles.

TEST_F(SessionItemDataTest, differentRoles)
{
    SessionItemData data;

    const int role1(1);
    const int role2 = role1 + 1;

    EXPECT_TRUE(data.setData(QVariant::fromValue(42.0), role1));
    EXPECT_TRUE(data.setData(QVariant::fromValue(std::string("str")), role2));

    std::vector<int> expected{role1, role2};
    EXPECT_EQ(data.roles(), expected);

    EXPECT_TRUE(data.data(role1) == QVariant(42.0));
    EXPECT_TRUE(data.data(role2) == QVariant::fromValue(std::string("str")));
    EXPECT_FALSE(data.data(role2) == QVariant(42.0));
    EXPECT_FALSE(data.data(role1) == QVariant::fromValue(std::string("str")));
}

//! Changing type of variant for role should not be allowed.

TEST_F(SessionItemDataTest, changingRole)
{
    SessionItemData data;

    const int role(1);
    const QVariant variant(42.0);

    // setting variant for role
    EXPECT_TRUE(data.setData(variant, role));
    std::vector<int> expected{role};
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == variant);

    QVariant s = QVariant::fromValue(std::string("str"));
    EXPECT_THROW(data.setData(s, role), std::runtime_error);
}

TEST_F(SessionItemDataTest, rangeLoop)
{
    SessionItemData data;
    const std::vector<double> expected_values = {1.2, 1.3};
    const std::vector<int> expected_roles = {1, 2};

    for (size_t i = 0; i < expected_values.size(); ++i) {
        data.setData(QVariant::fromValue(expected_values[i]), expected_roles[i]);
    }

    std::vector<double> values;
    std::vector<int> roles;

    for (const auto& x : data) {
        values.push_back(x.m_data.value<double>());
        roles.push_back(x.m_role);
    }

    EXPECT_EQ(values, expected_values);
    EXPECT_EQ(roles, expected_roles);
}

TEST_F(SessionItemDataTest, hasRole)
{
    SessionItemData data;
    EXPECT_FALSE(data.hasData(0));
    EXPECT_FALSE(data.hasData(1));

    const int role = 99;
    data.setData(QVariant::fromValue(42), role);
    EXPECT_TRUE(data.hasData(role));
    EXPECT_FALSE(data.hasData(1));

    data.setData(QVariant(), role);
    EXPECT_FALSE(data.hasData(role));
}
