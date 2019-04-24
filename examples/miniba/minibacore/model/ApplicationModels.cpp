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

ApplicationModels::ApplicationModels()
    : m_sample_model(std::make_unique<SampleModel>())
{

}
