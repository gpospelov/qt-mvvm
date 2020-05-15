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
    EXPECT_FALSE(Utils::exists(std::string()));
    EXPECT_FALSE(Utils::exists(std::string("abc")));
}

TEST_F(FileUtilsTest, create_directory)
{
    std::string dirname = testDir() + std::string("/") + "subdir";
    Utils::remove(dirname);

    EXPECT_TRUE(Utils::create_directory(dirname));
    EXPECT_TRUE(Utils::exists(dirname));
}

TEST_F(FileUtilsTest, remove_all)
{
    std::string dirname = testDir() + std::string("/") + "subdir2";
    Utils::create_directory(dirname);

    EXPECT_TRUE(Utils::exists(dirname));
    Utils::remove_all((dirname));
    EXPECT_FALSE(Utils::exists(dirname));
}

TEST_F(FileUtilsTest, base_name)
{
    std::string filename = testDir() + std::string("/testmodel/fileutils.test.cpp");
    std::string base_name = Utils::base_name(filename);

    EXPECT_EQ("fileutils.test", base_name);
}

#include <QDebug>
TEST_F(FileUtilsTest, FindFiles)
{
    TestUtils::CreateTestFile(testDir(), "a.txt");
    TestUtils::CreateTestFile(testDir(), "name0.json");
    TestUtils::CreateTestFile(testDir(), "name1.json");
    ASSERT_EQ(Utils::FindFiles(testDir(), ".json").size(), 2);
    qDebug() << "AAA" << QString::fromStdString(Utils::FindFiles(testDir(), ".json")[0]);
    EXPECT_EQ(Utils::FindFiles(testDir(), ".json")[0], Utils::join(testDir(), "name0.json"));
}

TEST_F(FileUtilsTest, parent_path)
{
    // parent path of testDir() is the main test folder
    // "<build>/test_output/test_FileUtils" -> "<build>/test_output/"
    EXPECT_EQ(Utils::parent_path(testDir()), TestUtils::TestOutputDir());

    // "<build>/test_output/test_FileUtils/a.txt" -> "<build>/test_output/test_FileUtils/"
    auto filename = TestUtils::CreateTestFile(testDir(), "a.txt");
    EXPECT_EQ(Utils::parent_path(filename), testDir());
}
