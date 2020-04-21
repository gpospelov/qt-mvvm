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
#include "test_utils.h"
#include <mvvm/model/sessionmodel.h>

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public ::testing::Test
{
public:
    ~ProjectUtilsTest();

    static inline const std::string test_dir = "test_ProjectUtils";

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }

    std::string testDirectory() const { return TestUtils::TestDirectoryPath(test_dir); }
};

ProjectUtilsTest::~ProjectUtilsTest() = default;

//! Testing helper structure.

TEST_F(ProjectUtilsTest, SuggestFileName)
{
    ModelView::SessionModel model("TestModel");
    EXPECT_EQ(std::string("testmodel.json"), ProjectUtils::SuggestFileName(model));
}

TEST_F(ProjectUtilsTest, FindFiles)
{
    TestUtils::CreateTestFile(testDirectory(), "a.txt");
    TestUtils::CreateTestFile(testDirectory(), "name0.json");
    TestUtils::CreateTestFile(testDirectory(), "name1.json");
    ASSERT_EQ(ProjectUtils::FindFiles(testDirectory(), ".json").size(), 2);
    ASSERT_EQ(ProjectUtils::FindFiles(testDirectory(), ".json")[0],
              testDirectory() + "/name0.json");
}
