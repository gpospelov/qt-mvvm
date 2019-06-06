// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ApplicationModels.h"
#include "MaterialModel.h"
#include "SampleModel.h"
#include "item_constants.h"
#include "jsonmodel.h"
#include "sessionitem.h"
#include "itempool.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

using namespace ModelView;

struct ApplicationModels::ApplicationModelsPrivate
{
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsPrivate>())
{
    p_impl->m_item_pool = std::make_shared<ItemPool>();
    p_impl->m_material_model = std::make_unique<MaterialModel>();
    p_impl->m_sample_model = std::make_unique<SampleModel>();

    // use common pool for both models
    p_impl->m_material_model->setItemPool(p_impl->m_item_pool);
    p_impl->m_sample_model->setItemPool(p_impl->m_item_pool);
}

ApplicationModels::~ApplicationModels() = default;

MaterialModel* ApplicationModels::materialModel()
{
    return p_impl->m_material_model.get();
}

SampleModel* ApplicationModels::sampleModel()
{
    return p_impl->m_sample_model.get();
}

void ApplicationModels::readFromFile(const QString& name)
{
    QFile jsonFile(name);

    if (!jsonFile.open(QIODevice::ReadOnly))
        throw std::runtime_error("readFromFile() -> Can't read file");

    auto document = QJsonDocument::fromJson(jsonFile.readAll());

    auto array = document.array();
    if (array.size() != 2)
        throw std::runtime_error("readFromFile() -> Unexpected amount of files");

    ModelView::JsonModel converter;

    p_impl->m_material_model->clear();
    converter.json_to_model(array.at(0).toObject(), *p_impl->m_material_model);

    p_impl->m_sample_model->clear();
    converter.json_to_model(array.at(1).toObject(), *p_impl->m_sample_model);
}

void ApplicationModels::writeToFile(const QString& name)
{
    ModelView::JsonModel converter;

    auto object = std::make_unique<QJsonObject>();
    converter.model_to_json(*p_impl->m_material_model, *object);

    QJsonArray array;
    array.push_back(*object);

    object = std::make_unique<QJsonObject>();
    converter.model_to_json(*p_impl->m_sample_model, *object);
    array.push_back(*object);

    QJsonDocument document(array);

    QFile saveFile(name);

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("writeToFile -> Can't save file");

    saveFile.write(document.toJson());
}
