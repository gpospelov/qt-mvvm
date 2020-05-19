// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include <QDir>
#include <mvvm/utils/fileutils.h>
#include <stdexcept>
#include <string>

using namespace ModelView;

class FileUtilsTest : public FolderBasedTest
{
public:
    FileUtilsTest() : FolderBasedTest("test_FileUtils") {}
    ~FileUtilsTest();
};

FileUtilsTest::~FileUtilsTest() = default;

TEST_F(FileUtilsTest, exists)
{
    EXPECT_TRUE(Utils::exists(testPath()));
    EXPECT_FALSE(Utils::exists(std::string()));
    EXPECT_FALSE(Utils::exists(std::string("abc")));
}

TEST_F(FileUtilsTest, create_directory)
{
    std::string dirname = testPath() + std::string("/") + "subdir";
    Utils::remove(dirname);

    EXPECT_TRUE(Utils::create_directory(dirname));
    EXPECT_TRUE(Utils::exists(dirname));
}

TEST_F(FileUtilsTest, remove_all)
{
    std::string dirname = testPath() + std::string("/") + "subdir2";
    Utils::create_directory(dirname);

    EXPECT_TRUE(Utils::exists(dirname));
    Utils::remove_all((dirname));
    EXPECT_FALSE(Utils::exists(dirname));
}

TEST_F(FileUtilsTest, base_name)
{
    std::string filename = testPath() + std::string("/testmodel/fileutils.test.cpp");
    std::string base_name = Utils::base_name(filename);

    EXPECT_EQ("fileutils.test", base_name);
}

TEST_F(FileUtilsTest, FindFiles)
{
    TestUtils::CreateTestFile(testPath(), "a.txt");
    TestUtils::CreateTestFile(testPath(), "name0.json");
    TestUtils::CreateTestFile(testPath(), "name1.json");

    auto found_files = Utils::FindFiles(testPath(), ".json");

    ASSERT_EQ(found_files.size(), 2);
    EXPECT_NE(found_files.end(), std::find(found_files.begin(), found_files.end(),
                                           Utils::join(testPath(), "name0.json")));
    EXPECT_NE(found_files.end(), std::find(found_files.begin(), found_files.end(),
                                           Utils::join(testPath(), "name1.json")));
}

TEST_F(FileUtilsTest, parent_path)
{
    // parent path of testPath() is the main test folder
    // "<build>/test_output/test_FileUtils" -> "<build>/test_output/"
    EXPECT_EQ(Utils::parent_path(testPath()), TestUtils::TestOutputDir());

    // "<build>/test_output/test_FileUtils/a.txt" -> "<build>/test_output/test_FileUtils/"
    auto filename = TestUtils::CreateTestFile(testPath(), "a.txt");
    EXPECT_EQ(Utils::parent_path(filename), testPath());
}

TEST_F(FileUtilsTest, is_empty)
{
    // creating new empty directory
    std::string dirname = testPath() + std::string("/") + "subdir_is_empty";
    Utils::remove_all(dirname);
    Utils::create_directory(dirname);

    // it should be empty
    EXPECT_TRUE(Utils::is_empty(dirname));

    // creating file in it, directory should be not empty
    auto filename = TestUtils::CreateTestFile(dirname, "a.txt");
    EXPECT_FALSE(Utils::is_empty(dirname));
    // file itself should be not empty
    EXPECT_FALSE(Utils::is_empty(dirname));

    // creating empty file
    auto empty_filename = TestUtils::CreateEmptyFile(dirname, "a2.txt");
    EXPECT_TRUE(Utils::is_empty(empty_filename));
}
