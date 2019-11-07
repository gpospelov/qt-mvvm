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
#include <QString>

class QJsonObject;
class QJsonArray;

namespace ModelView
{
class SessionModel;
}

//! Various common utils for unit tests.

namespace TestUtils
{

//! Creates test directory in CMAKE_BINARY_DIR. If directory exists, will do nothing.
void CreateTestDirectory(const QString& test_sub_dir);

//! Returns full path to the test directory in CMAKE_BINARY_DIR.
QString TestDirectoryPath(const QString& test_sub_dir);

//! Returns full path to the file in test directory.
QString TestFileName(const QString& test_sub_dir, const QString& file_name);

void SaveJson(const QJsonObject& object, const QString& fileName);

void SaveJson(const QJsonArray& object, const QString& fileName);

QString JsonToString(const QJsonObject& object);

//! Returns string representing serialized json content of the model.
QString ModelToJsonString(ModelView::SessionModel& model);

QJsonDocument LoadJson(const QString& fileName);

template<typename T>
void clean_items(T& items) {
    for (auto item : items)
        delete item;
    items.clear();
}


}

#endif
