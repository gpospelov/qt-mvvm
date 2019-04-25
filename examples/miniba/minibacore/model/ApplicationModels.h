// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include "global.h"
#include <memory>

class SampleModel;
class MaterialModel;

class CORE_EXPORT ApplicationModels
{
public:
    ApplicationModels();
    ~ApplicationModels();

    SampleModel* sampleModel();
    MaterialModel* materialModel();

private:
    std::unique_ptr<MaterialModel> m_material_model;
    std::unique_ptr<SampleModel> m_sample_model;
};

#endif //  APPLICATIONMODELS_H

