// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "projectutils.h"
#include "projectinterface.h"
#include "test_utils.h"
#include <mvvm/model/sessionmodel.h>

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public ::testing::Test
{
public:
    ~ProjectUtilsTest();
};

ProjectUtilsTest::~ProjectUtilsTest() = default;

//! Testing helper structure.

TEST_F(ProjectUtilsTest, SuggestFileName)
{
    ModelView::SessionModel model("TestModel");
    EXPECT_EQ(std::string("testmodel.json"), ProjectUtils::SuggestFileName(model));
}

TEST_F(ProjectUtilsTest, CreateUtitledProject)
{
    auto project = ProjectUtils::CreateUtitledProject(nullptr);
    EXPECT_TRUE(project->projectDir().empty());
}
