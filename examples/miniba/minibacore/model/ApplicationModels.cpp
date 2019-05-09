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
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

struct ApplicationModels::ApplicationModelsPrivate
{
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsPrivate>())
{
    p_impl->m_material_model = std::make_unique<MaterialModel>();
    p_impl->m_sample_model = std::make_unique<SampleModel>();
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
    Q_UNUSED(name)
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
