#include "google_test.h"
#include "itemutils.h"
#include "copyitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"

using namespace ModelView;

class TestCopyItemCommand : public ::testing::Test
{
public:
    ~TestCopyItemCommand();
};

TestCopyItemCommand::~TestCopyItemCommand() = default;

TEST_F(TestCopyItemCommand, copyChild)
{
    SessionModel model;

    // parent with children and data
    auto parent = model.insertItem<SessionItem>(model.rootItem(), "", 0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child0 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child0->setData(42.0);
    auto child1 = model.insertItem<SessionItem>(parent, "tag1", -1);
    child1->setData(43.0);

    // making copy of child
    auto command = std::make_unique<CopyItemCommand>(child1, parent, "tag1", 1);
    command->execute();

    // checking that parent has now three children
    auto copy = command->result();
    EXPECT_TRUE(copy != nullptr);
    EXPECT_EQ(parent->childrenCount(), 3);
    std::vector<SessionItem*> expected = {child0, copy, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
    EXPECT_EQ(copy->data().toDouble(), 43.0);

    // undoing command
    command->undo();
    expected = {child0, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
}
