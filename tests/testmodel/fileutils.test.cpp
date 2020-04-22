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

TEST_F(FileUtilsTest, create_directory)
{
    std::string dirname = testDir() + std::string("/") + "subdir";
    EXPECT_TRUE(Utils::create_directory(dirname));
    EXPECT_TRUE(Utils::exists(dirname));
}

TEST_F(FileUtilsTest, remove_all)
{
    std::string dirname = testDir() + std::string("/") + "subdir";
    EXPECT_TRUE(Utils::create_directory(dirname));
    Utils::remove_all((dirname));

    EXPECT_FALSE(Utils::exists(dirname));
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

TEST_F(FileUtilsTest, FindFiles)
{
    TestUtils::CreateTestFile(testDir(), "a.txt");
    TestUtils::CreateTestFile(testDir(), "name0.json");
    TestUtils::CreateTestFile(testDir(), "name1.json");
    ASSERT_EQ(Utils::FindFiles(testDir(), ".json").size(), 2);
    ASSERT_EQ(Utils::FindFiles(testDir(), ".json")[0], testDir() + "/name0.json");
}
