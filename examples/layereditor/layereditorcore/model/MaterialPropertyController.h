// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALPROPERTYCONTROLLER_H
#define MATERIALPROPERTYCONTROLLER_H

#include "sessionmodel.h"

class SampleModel;
class MaterialModel;

/*!
@class MaterialPropertyController
@brief Listens for all changes in material model and updates properties in SampleModel.
*/

class CORE_EXPORT MaterialPropertyController
{
public:
    MaterialPropertyController(MaterialModel* material_model, SampleModel* sample_model);
    ~MaterialPropertyController();

private:
    void connect_material_model();
    void update_all();
    MaterialModel* m_material_model;
    SampleModel* m_sample_model;
};

#endif //  MATERIALPROPERTYCONTROLLER_H
