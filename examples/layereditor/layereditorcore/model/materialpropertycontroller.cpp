// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <model/layeritems.h>
#include <model/materialmodel.h>
#include <model/materialpropertycontroller.h>
#include <model/samplemodel.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : m_material_model(material_model), m_sample_model(sample_model)
{
    connect_material_model();
    update_all();
}

MaterialPropertyController::~MaterialPropertyController()
{
    if (m_material_model)
        m_material_model->mapper()->unsubscribe(this);
}

//! Connect with signals of MaterialModel.

void MaterialPropertyController::connect_material_model()
{
    auto on_data_change = [this](SessionItem*, int) { update_all(); };
    m_material_model->mapper()->setOnDataChange(on_data_change, this);

    auto on_item_removed = [this](SessionItem*, TagRow) { update_all(); };
    m_material_model->mapper()->setOnItemRemoved(on_item_removed, this);

    auto on_model_destroyed = [this](SessionModel*) { m_material_model = nullptr; };
    m_material_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void MaterialPropertyController::update_all()
{
    auto layers = Utils::FindItems<LayerItem>(m_sample_model);
    for (auto layer : Utils::FindItems<LayerItem>(m_sample_model)) {
        auto property = layer->property<ExternalProperty>(LayerItem::P_MATERIAL);
        auto updated = m_material_model->material_property(property.identifier());
        if (property != updated)
            layer->setProperty(LayerItem::P_MATERIAL, updated);
    }
}
