// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALPROPERTYCONTROLLER_H
#define MATERIALPROPERTYCONTROLLER_H

#include <mvvm/model/sessionmodel.h>

class SampleModel;
class MaterialModel;

/*!
@class MaterialPropertyController
@brief Listens for all changes in material model and updates properties in SampleModel.
*/

class MaterialPropertyController
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
