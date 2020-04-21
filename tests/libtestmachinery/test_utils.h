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

#include <mvvm/model/customvariants.h>
#include <memory>
#include <QString>

//! @file test_utils.h
//! @brief Collection of utility functions for various unit tests.

class QJsonObject;
class QJsonArray;

namespace ModelView
{
class SessionModel;
}

//! Various common utils for unit tests.

namespace TestUtils
{

//! Creates test directory in main test folder (CMAKE_BINARY_DIR/test_output).
//!  If directory exists, will do nothing.
void CreateTestDirectory(const QString& test_sub_dir);

//! Returns full path to the main test folder in CMAKE_BINARY_DIR.
QString TestDirectoryPath(const QString& test_sub_dir);
std::string TestDirectoryPath(const std::string& test_sub_dir);

//! Returns full path to the file in test directory.
QString TestFileName(const QString& test_sub_dir, const QString& file_name);

void SaveJson(const QJsonObject& object, const QString& fileName);

void SaveJson(const QJsonArray& object, const QString& fileName);

QString JsonToString(const QJsonObject& object);

//! Returns string representing serialized json content of the model.
QString ModelToJsonString(ModelView::SessionModel& model);

QJsonDocument LoadJson(const QString& fileName);

//! Deletes items in the container and cleans container afterwards.

template<typename T>
void clean_items(T& items) {
    for (auto item : items)
        delete item;
    items.clear();
}

//! Creates vector of unique_ptr of given type.

template<typename B, typename D> auto create_row(int ncolumns)
{
    std::vector<std::unique_ptr<B>> result;
    for (int i=0; i<ncolumns; ++i)
        result.emplace_back(std::make_unique<D>());
    return result;
}

//! Creates vector of pointers from vector of unique_ptr.

template<typename T>
auto create_pointers(const std::vector<std::unique_ptr<T>>& vec)
{
    std::vector<T*> result;
    std::transform(vec.begin(), vec.end(), std::back_inserter(result),
                   [](auto& x) { return x.get(); });
    return result;
}

}

#endif
