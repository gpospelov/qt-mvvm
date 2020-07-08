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

#include <mvvm/signals/modellistener.h>

class SampleModel;
class MaterialModel;

//! Listens for all changes in material model and updates properties in SampleModel.

class MaterialPropertyController : public ModelView::ModelListener<MaterialModel>
{
public:
    MaterialPropertyController(MaterialModel* material_model, SampleModel* sample_model);

private:
    void update_all();

    MaterialModel* m_material_model;
    SampleModel* m_sample_model;
};

#endif //  MATERIALPROPERTYCONTROLLER_H
