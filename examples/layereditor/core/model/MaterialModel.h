// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

namespace ModelView
{
class ExternalProperty;
}

/*!
@class MaterialModel
@brief Model to hold MaterialItems.
*/

class MaterialModel : public ModelView::SessionModel
{
public:
    MaterialModel();

    static ModelView::ExternalProperty undefined_material();

    std::vector<ModelView::ExternalProperty> material_data();

    ModelView::ExternalProperty  material_property(const std::string& id);
private:
    void init_model();
};

#endif //  MATERIALMODEL_H
