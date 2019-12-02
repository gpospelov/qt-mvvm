// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <mvvm/utils/fileutils.h>
#include <stdexcept>
#include <string>

using namespace ModelView;

class FileUtilsTest : public ::testing::Test
{
public:
    ~FileUtilsTest();

    //! Helper function to create test file in a given directory (directory should exist).
    void createTestFile(const std::string& dirname, const std::string& fileName)
    {
        std::string filename = dirname.empty() ? fileName : dirname + "/" + fileName;

        QFile file(QString::fromStdString(filename));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw std::runtime_error("TestFileUtils::createTestFile() -> Error. "
                                     "Can't create file");

        QTextStream out(&file);
        out << "Test file " << 42 << "\n";
        file.close();
    }
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

    createTestFile(projectDir(), "a.txt");
    EXPECT_TRUE(Utils::exists(projectDir() + "/a.txt"));
}
