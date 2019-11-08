// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ApplicationModels.h"
#include "MaterialModel.h"
#include "MaterialPropertyController.h"
#include "SampleModel.h"
#include <mvvm/model/sessionitem.h>
#include <mvvm/serialization/jsondocument.h>

using namespace ModelView;

struct ApplicationModels::ApplicationModelsImpl {
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
    std::unique_ptr<MaterialPropertyController> m_property_controller;
    std::unique_ptr<JsonDocument> m_document;

    ApplicationModelsImpl()
    {
        m_material_model = std::make_unique<MaterialModel>();
        m_sample_model = std::make_unique<SampleModel>();
        m_property_controller = std::make_unique<MaterialPropertyController>(m_material_model.get(),
                                                                             m_sample_model.get());
        m_document = std::make_unique<JsonDocument>(
            std::initializer_list<SessionModel*>{m_material_model.get(), m_sample_model.get()});
    }
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsImpl>())
{
    std::unique_ptr<JsonDocument> m_document;
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
    p_impl->m_document->load(name.toStdString());
}

void ApplicationModels::writeToFile(const QString& name)
{
    p_impl->m_document->save(name.toStdString());
}
