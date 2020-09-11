// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/jsondocument.h>
#include <mvvm/serialization/jsonmodelconverter.h>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace ModelView;

struct JsonDocument::JsonDocumentImpl {
    std::vector<SessionModel*> models;
    JsonDocumentImpl(const std::initializer_list<ModelView::SessionModel*>& models) : models(models)
    {
    }
};

JsonDocument::JsonDocument(std::initializer_list<ModelView::SessionModel*> models)
    : p_impl(std::make_unique<JsonDocumentImpl>(models))
{
}

//! Saves models on disk.
void JsonDocument::save(const std::string& file_name) const
{
    ModelView::JsonModelConverter converter;
    QJsonArray array;

    for (auto model : p_impl->models) {
        QJsonObject object;
        converter.to_json(*model, object);
        array.push_back(object);
    }

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

    ModelView::JsonModelConverter converter;
    int index(0);
    for (auto model : p_impl->models) {
        converter.from_json(array.at(index).toObject(), *model);
        ++index;
    }

    file.close();
}

JsonDocument::~JsonDocument() = default;
