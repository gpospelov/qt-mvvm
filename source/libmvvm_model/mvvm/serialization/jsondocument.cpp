// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsondocument.h"
#include "mvvm/factories/modelconverterfactory.h"
#include "mvvm/model/sessionmodel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

struct JsonDocument::JsonDocumentImpl {
    std::vector<SessionModel*> models;
    JsonDocumentImpl(std::vector<SessionModel*> models) : models(std::move(models)) {}
};

JsonDocument::JsonDocument(const std::vector<SessionModel*>& models)
    : p_impl(std::make_unique<JsonDocumentImpl>(models))
{
}

//! Saves models on disk.
void JsonDocument::save(const std::string& file_name) const
{
    auto converter = ModelView::CreateModelProjectConverter();
    QJsonArray array;

    for (auto model : p_impl->models)
        array.push_back(converter->to_json(*model));

    QJsonDocument document(array);
    QFile file(QString::fromStdString(file_name));

    if (!file.open(QIODevice::WriteOnly))
        throw std::runtime_error("Error in JsonDocument: can't save the file '" + file_name + "'");

    file.write(document.toJson());

    file.close();
}

//! Loads models from disk. If models have some data already, it will be rewritten.

void JsonDocument::load(const std::string& file_name)
{
    QFile file(QString::fromStdString(file_name));
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Error in JsonDocument: can't read the file '" + file_name + "'");

    auto document = QJsonDocument::fromJson(file.readAll());
    auto array = document.array();
    if (array.size() != static_cast<int>(p_impl->models.size())) {
        std::ostringstream ostr;
        ostr << "Error in JsonDocument: number of application models " << p_impl->models.size()
             << " and number of json models " << array.size() << " doesn't match";
        throw std::runtime_error(ostr.str());
    }

    auto converter = ModelView::CreateModelProjectConverter();
    int index(0);
    for (auto model : p_impl->models) {
        converter->from_json(array.at(index).toObject(), *model);
        ++index;
    }

    file.close();
}

JsonDocument::~JsonDocument() = default;
