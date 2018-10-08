#include <gtest/gtest.h>
#include "sessionitemdata.h"

//! Test of SessionItemData.

class TestSessionItemData : public ::testing::Test
{
public:
    ~TestSessionItemData();
};

TestSessionItemData::~TestSessionItemData() = default;

//! Initial state of SessionItemData object.

TEST_F(TestSessionItemData, initialState)
{
    SessionItemData data;
    EXPECT_TRUE(data.roles().empty());
    EXPECT_FALSE(data.data(Qt::DisplayRole).isValid());
}

//! Basic setData, data operations.

TEST_F(TestSessionItemData, setData)
{
    SessionItemData data;

    const int role = Qt::UserRole + 1;
    const QVariant variant(42.0);

    // setting variant for role
    EXPECT_TRUE(data.setData(variant, role));
    std::vector<int> expected {role};
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

    // setting invalid variant for the role
    EXPECT_TRUE(data.setData(QVariant(), role));
    EXPECT_TRUE(data.roles().empty());
    EXPECT_FALSE(data.data(role).isValid());
}

//! Using different roles.

TEST_F(TestSessionItemData, differentRoles)
{
    SessionItemData data;

    const int role1 = Qt::UserRole + 1;
    const int role2 = role1 + 1;

    EXPECT_TRUE(data.setData(QVariant::fromValue(42.0), role1));
    EXPECT_TRUE(data.setData(QVariant::fromValue(std::string("str")), role2));

    std::vector<int> expected {role1, role2};
    EXPECT_EQ(data.roles(), expected);

    EXPECT_TRUE(data.data(role1) == QVariant(42.0));
    EXPECT_TRUE(data.data(role2) == QVariant::fromValue(std::string("str")));
    EXPECT_FALSE(data.data(role2) == QVariant(42.0));
    EXPECT_FALSE(data.data(role1) == QVariant::fromValue(std::string("str")));
}

//! Changing type of variant for role should be allowed.

TEST_F(TestSessionItemData, changingRole)
{
    SessionItemData data;

    const int role = Qt::UserRole + 1;
    const QVariant variant(42.0);

    // setting variant for role
    EXPECT_TRUE(data.setData(variant, role));
    std::vector<int> expected {role};
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == variant);

    QVariant s = QVariant::fromValue(std::string("str"));
    EXPECT_TRUE(data.setData(s, role));
    EXPECT_TRUE(data.data(role) == s);
}

//! Edit role is treated as edit role.

TEST_F(TestSessionItemData, editRole)
{
    SessionItemData data;

    const int role = Qt::DisplayRole;
    const QVariant variant(42.0);

    // setting displayRole, accessing editRole
    EXPECT_TRUE(data.setData(variant, role));
    std::vector<int> expected {role};
    EXPECT_EQ(data.roles(), expected);
    EXPECT_TRUE(data.data(role) == variant);
    EXPECT_TRUE(data.data(Qt::EditRole) == variant);

    // setting editRole, accessing displayRole
    EXPECT_FALSE(data.setData(variant, Qt::EditRole));
    EXPECT_TRUE(data.setData(QVariant::fromValue(std::string("str")), Qt::EditRole));
    EXPECT_TRUE(data.data(Qt::DisplayRole) == QVariant::fromValue(std::string("str")));
    EXPECT_EQ(data.roles(), expected);
}
