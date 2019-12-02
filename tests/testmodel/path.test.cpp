// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <memory>
#include <mvvm/model/path.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>

using namespace ModelView;

class PathTest : public ::testing::Test
{
public:
    ~PathTest();
};

PathTest::~PathTest() = default;

TEST_F(PathTest, initialState)
{
    Path path;
    EXPECT_TRUE(path.str().empty());
}

TEST_F(PathTest, append)
{
    Path path;
    path.append(1);
    EXPECT_EQ(path.str(), "1");

    path.append(2);
    EXPECT_EQ(path.str(), "1,2");

    path.prepend(3);
    EXPECT_EQ(path.str(), "3,1,2");
}

TEST_F(PathTest, fromVector)
{
    Path path = Path::fromVector({1, 2, 3});
    EXPECT_EQ(path.str(), "1,2,3");
}

TEST_F(PathTest, fromString)
{
    Path path = Path::fromString("3,2,3");
    EXPECT_EQ(path.str(), "3,2,3");
}

TEST_F(PathTest, pathFromItem)
{
    SessionModel model;

    // unexisting path
    EXPECT_TRUE(model.pathFromItem(nullptr).str().empty());
    // yet another unexisting path
    std::unique_ptr<SessionItem> xx(new SessionItem);
    EXPECT_TRUE(model.pathFromItem(xx.get()).str().empty());

    // three children beneeth root item
    SessionItem* item0 = model.insertItem<SessionItem>();
    item0->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    SessionItem* item1 = model.insertItem<SessionItem>();
    item1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    SessionItem* item2 = model.insertItem<SessionItem>();
    item2->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    EXPECT_EQ(model.pathFromItem(item0).str(), "0");
    EXPECT_EQ(model.pathFromItem(item1).str(), "1");
    EXPECT_EQ(model.pathFromItem(item2).str(), "2");

    // adding granchildren to item0
    SessionItem* child00 = model.insertItem<SessionItem>(item0);
    SessionItem* child01 = model.insertItem<SessionItem>(item0);

    EXPECT_EQ(model.pathFromItem(child00).str(), "0,0");
    EXPECT_EQ(model.pathFromItem(child01).str(), "0,1");

    // adding grandchildren to item2
    SessionItem* child20 = model.insertItem<SessionItem>(item2);
    child20->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    SessionItem* child200 = model.insertItem<SessionItem>(child20);
    SessionItem* child201 = model.insertItem<SessionItem>(child20);

    EXPECT_EQ(model.pathFromItem(child200).str(), "2,0,0");
    EXPECT_EQ(model.pathFromItem(child201).str(), "2,0,1");
}

TEST_F(PathTest, itemFromPath)
{
    SessionModel model;

    // access to non-existing item
    Path non_existing;
    non_existing.append(8);
    EXPECT_EQ(model.itemFromPath(non_existing), nullptr);

    SessionItem* item0 = model.insertItem<SessionItem>();
    item0->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    SessionItem* item1 = model.insertItem<SessionItem>();
    item1->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    SessionItem* item2 = model.insertItem<SessionItem>();
    item2->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    EXPECT_EQ(model.itemFromPath(Path::fromVector({0})), item0);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({1})), item1);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2})), item2);

    SessionItem* child20 = model.insertItem<SessionItem>(item2);
    child20->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    SessionItem* child200 = model.insertItem<SessionItem>(child20);
    SessionItem* child201 = model.insertItem<SessionItem>(child20);

    EXPECT_EQ(model.itemFromPath(Path::fromVector({2, 0})), child20);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2, 0, 0})), child200);
    EXPECT_EQ(model.itemFromPath(Path::fromVector({2, 0, 1})), child201);
}
