// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/copyitemcommand.h"

#include "google_test.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include <stdexcept>

using namespace ModelView;

class CopyItemCommandTest : public ::testing::Test {
};

TEST_F(CopyItemCommandTest, copyChild)
{
    SessionModel model;

    // parent with children and data
    auto parent = model.insertItem<SessionItem>(model.rootItem(), {"", 0});
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child0 = model.insertItem<SessionItem>(parent, "tag1");
    child0->setData(42.0);
    auto child1 = model.insertItem<SessionItem>(parent, "tag1");
    child1->setData(43.0);

    // making copy of child
    auto command = std::make_unique<CopyItemCommand>(child1, parent, TagRow{"tag1", 1});
    command->execute();

    // checking that parent has now three children
    auto copy = std::get<SessionItem*>(command->result());
    EXPECT_FALSE(command->isObsolete());
    EXPECT_TRUE(copy != nullptr);
    EXPECT_EQ(parent->childrenCount(), 3);
    std::vector<SessionItem*> expected = {child0, copy, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
    EXPECT_EQ(copy->data<double>(), 43.0);

    // undoing command
    command->undo();
    expected = {child0, child1};
    EXPECT_EQ(parent->getItems("tag1"), expected);
    EXPECT_FALSE(command->isObsolete());
}

//! Attempt to copy item to invalid tag

TEST_F(CopyItemCommandTest, invalidCopyAttempt)
{
    SessionModel model;

    // parent with children and data
    auto parent = model.insertItem<CompoundItem>(model.rootItem());
    parent->addProperty("thickness", 42.0);
    parent->registerTag(TagInfo::universalTag("tag1"), /*set_as_default*/ true);

    auto child0 = model.insertItem<SessionItem>(parent);
    child0->setData(42.0);

    // making copy of child
    auto command = std::make_unique<CopyItemCommand>(child0, parent, TagRow{"thickness", 0});
    EXPECT_THROW(command->execute(), std::runtime_error);

    // checking that parent has now three children
    // FIXME revise command behavior in the case of invalid operation
    // Exception or catch?
    // EXPECT_TRUE(command->isObsolete());
//    EXPECT_EQ(std::get<SessionItem*>(command->result()), nullptr);

    // undoing of obsolete command is not possible
    EXPECT_THROW(command->undo(), std::runtime_error);
}
