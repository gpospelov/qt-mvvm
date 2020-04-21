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

    std::string projectDir() const { return TestConfig::TestOutputDir() + "/" + "test_FileUtils"; }
};

FileUtilsTest::~FileUtilsTest() = default;

TEST_F(FileUtilsTest, initialState)
{
    QDir dir(QString::fromStdString(projectDir()));
    if (dir.exists()) {
        EXPECT_TRUE(Utils::removeRecursively(projectDir()) == true);
        EXPECT_TRUE(dir.exists() == false);
    }

    Utils::create_subdir(".", projectDir());
    EXPECT_TRUE(Utils::exists(projectDir()));

    TestUtils::CreateTestFile(projectDir(), "a.txt");
    EXPECT_TRUE(Utils::exists(projectDir() + "/a.txt"));
}
