// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QDir>
#include <mvvm/utils/fileutils.h>
#include <stdexcept>
#include <string>

using namespace ModelView;

class FileUtilsTest : public ::testing::Test
{
public:
    ~FileUtilsTest();

    static inline const std::string test_dir = "test_FileUtils";
    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
    std::string testDir() const { return TestUtils::TestDirectoryPath(test_dir); }
};

FileUtilsTest::~FileUtilsTest() = default;

TEST_F(FileUtilsTest, exists)
{
    EXPECT_TRUE(Utils::exists(testDir()));
}

TEST_F(FileUtilsTest, initialState)
{
    QDir dir(QString::fromStdString(testDir()));
    if (dir.exists()) {
        EXPECT_TRUE(Utils::removeRecursively(testDir()) == true);
        EXPECT_TRUE(dir.exists() == false);
    }

    Utils::create_subdir(".", testDir());
    EXPECT_TRUE(Utils::exists(testDir()));

    TestUtils::CreateTestFile(testDir(), "a.txt");
    EXPECT_TRUE(Utils::exists(testDir() + "/a.txt"));
}
