// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "applicationmodels.h"
#include "jobmodel.h"
#include "layeritems.h"
#include "materialmodel.h"
#include "materialpropertycontroller.h"
#include "realdatamodel.h"
#include "samplemodel.h"
#include "sldelementmodel.h"
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itempool.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/serialization/jsondocument.h>

using namespace ModelView;

struct ApplicationModels::ApplicationModelsImpl {
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
    std::unique_ptr<SLDElementModel> m_sld_view_model;
    std::unique_ptr<JobModel> m_job_model;
    std::unique_ptr<RealDataModel> m_realdata_model;
    std::unique_ptr<MaterialPropertyController> m_property_controller;
    std::unique_ptr<JsonDocument> m_document;
    std::shared_ptr<ItemPool> item_pool;

    ApplicationModelsImpl()
    {
        item_pool = std::make_shared<ItemPool>();
        m_material_model = std::make_unique<MaterialModel>(item_pool);
        m_sample_model = std::make_unique<SampleModel>(item_pool);
        m_sld_view_model = std::make_unique<SLDElementModel>();
        m_job_model = std::make_unique<JobModel>();
        m_realdata_model = std::make_unique<RealDataModel>();
        m_property_controller = std::make_unique<MaterialPropertyController>(m_material_model.get(),
                                                                             m_sample_model.get());
        m_document = std::make_unique<JsonDocument>(
            std::initializer_list<SessionModel*>{m_material_model.get(), m_sample_model.get()});

        m_sample_model->create_default_multilayer();
        update_material_properties();
    }

    //! Runs through all layers and assign materials.
    //! Expecting 3 materials existing by default (air, default, Si) to assign to our 3 layers.

    void update_material_properties()
    {
        auto multilayer = Utils::TopItem<MultiLayerItem>(m_sample_model.get());
        auto layers = multilayer->items<LayerItem>(MultiLayerItem::T_LAYERS);
        size_t index(0);
        for (const auto& material_property : m_material_model->material_data()) {
            if (index < layers.size())
                layers[index]->setProperty(LayerItem::P_MATERIAL, material_property);
            ++index;
        }
    }
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsImpl>()) {}

ApplicationModels::~ApplicationModels() = default;

MaterialModel* ApplicationModels::materialModel()
{
    return p_impl->m_material_model.get();
}

SampleModel* ApplicationModels::sampleModel()
{
    return p_impl->m_sample_model.get();
}

SLDElementModel* ApplicationModels::sldViewModel()
{
    return p_impl->m_sld_view_model.get();
}

JobModel* ApplicationModels::jobModel()
{
    return p_impl->m_job_model.get();
}

RealDataModel* ApplicationModels::realDataModel()
{
    return p_impl->m_realdata_model.get();
}

void ApplicationModels::readFromFile(const QString& name)
{
    p_impl->m_document->load(name.toStdString());
}

void ApplicationModels::writeToFile(const QString& name)
{
    p_impl->m_document->save(name.toStdString());
}
