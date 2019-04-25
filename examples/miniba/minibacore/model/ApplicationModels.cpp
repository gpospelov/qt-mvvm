// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ApplicationModels.h"
#include "SampleModel.h"
#include "MaterialModel.h"

class ApplicationModels::ApplicationModelsPrivate
{
public:
    ApplicationModelsPrivate() : m_material_model(std::make_unique<MaterialModel>()), m_sample_model(std::make_unique<SampleModel>())
    {

    }
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
};

ApplicationModels::ApplicationModels()
    : p_impl(std::make_unique<ApplicationModelsPrivate>())
{

}

ApplicationModels::~ApplicationModels() = default;

ModelView::SessionModel* ApplicationModels::sampleModel()
{
    return p_impl->m_sample_model.get();
}

ModelView::SessionModel* ApplicationModels::materialModel()
{
    return nullptr;
}
