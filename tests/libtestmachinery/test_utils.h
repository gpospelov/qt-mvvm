// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QString>
#include <memory>
#include "mvvm/model/customvariants.h"

//! @file test_utils.h
//! @brief Collection of utility functions for various unit tests.

class QJsonObject;
class QJsonArray;

namespace ModelView {
class SessionModel;
}

//! Various common utils for unit tests.

namespace TestUtils {

//! Returns full path to the main test folder, as defined by CMake at compile time.
//! Shoud point to CMAKE_BINARY_DIR/test_output
std::string TestOutputDir();

//! Creates test directory in main test folder and returns full path.
//! If directory exists, will do nothing.
std::string CreateTestDirectory(const std::string& test_sub_dir);

//! Returns full path to the main test folder in CMAKE_BINARY_DIR.
std::string TestDirectoryPath(const std::string& test_sub_dir);

//! Returns full path to the file in test directory.
std::string TestFileName(const std::string& test_sub_dir, const std::string& file_name);

void SaveJson(const QJsonObject& object, const std::string& fileName);

void SaveJson(const QJsonArray& object, const std::string& fileName);

QString JsonToString(const QJsonObject& object);

//! Returns string representing serialized json content of the model.
QString ModelToJsonString(ModelView::SessionModel& model);

QJsonDocument LoadJson(const std::string& fileName);

//! Helper function to create test file in a given directory (directory should exist).
//! Returns full path of the file.
std::string CreateTestFile(const std::string& dirname, const std::string& fileName);

//! Helper function to create empty file in a given directory (directory should exist).
//! Returns full path of the file.
std::string CreateEmptyFile(const std::string& dirname, const std::string& fileName);

//! Deletes items in the container and cleans container afterwards.

template <typename T> void clean_items(T& items)
{
    for (auto item : items)
        delete item;
    items.clear();
}

//! Creates vector of unique_ptr of given type.

template <typename B, typename D> auto create_row(int ncolumns)
{
    std::vector<std::unique_ptr<B>> result;
    for (int i = 0; i < ncolumns; ++i)
        result.emplace_back(std::make_unique<D>());
    return result;
}

//! Creates vector of pointers from vector of unique_ptr.

template <typename T> auto create_pointers(const std::vector<std::unique_ptr<T>>& vec)
{
    std::vector<T*> result;
    std::transform(vec.begin(), vec.end(), std::back_inserter(result),
                   [](auto& x) { return x.get(); });
    return result;
}

//! Creates vector of T from argument list. Used in EXPECT_EQ macros for convenience.

template <typename T, typename... Args> std::vector<T> toVector(Args&&... args)
{
    std::vector<T> v;
    (v.push_back(T(args)), ...);
    return v;
}

} // namespace TestUtils

#endif
