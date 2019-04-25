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

ApplicationModels::ApplicationModels()
    : m_material_model(new MaterialModel), m_sample_model(new SampleModel)
{

}

ApplicationModels::~ApplicationModels() = default;

SampleModel* ApplicationModels::sampleModel()
{
    return m_sample_model.get();
}

MaterialModel* ApplicationModels::materialModel()
{
    return m_material_model.get();
}
