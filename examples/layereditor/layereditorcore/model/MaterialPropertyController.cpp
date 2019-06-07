// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialPropertyController.h"

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : m_material_model(material_model), m_sample_model(m_sample_model)
{
    update_all();
}
