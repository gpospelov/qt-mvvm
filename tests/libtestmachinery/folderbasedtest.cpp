// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "test_utils.h"
#include "mvvm/utils/fileutils.h"

FolderBasedTest::FolderBasedTest(const std::string& test_dir) : m_test_dir(test_dir)
{
    TestUtils::CreateTestDirectory(m_test_dir);
}

std::string FolderBasedTest::testDir() const
{
    return m_test_dir;
}

//! Return full path to the test folder. Located in CMAKE_BINARY_DIR/test_output/<m_test_dir>.

std::string FolderBasedTest::testPath() const
{
    return TestUtils::TestDirectoryPath(m_test_dir);
}

//! Creates an empty directory in main test folder.
//! Remove recursively previous one with the same name, if exist.

std::string FolderBasedTest::createEmptyDir(const std::string& subdir) const
{
    auto path = ModelView::Utils::join(testPath(), subdir);
    ModelView::Utils::remove_all(path);
    ModelView::Utils::create_directory(path);
    return path;
}

FolderBasedTest::~FolderBasedTest() = default;
