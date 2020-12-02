// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

//! Testing various undo/redo scenario.

class UndoScenarioTest : public ::testing::Test
{
public:
    ~UndoScenarioTest();
};

UndoScenarioTest::~UndoScenarioTest() = default;

TEST_F(UndoScenarioTest, initialState)
{
    EXPECT_EQ(1, 1);
}
