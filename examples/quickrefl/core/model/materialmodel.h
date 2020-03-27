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
#include <mvvm/model/tagrow.h>
#include <vector>

namespace ModelView
{
class ExternalProperty;
}

class MaterialBaseItem;
class MaterialContainerItem;
class SLDMaterialItem;

/*!
@class MaterialModel
@brief Model to hold MaterialItems.
*/

class MaterialModel : public ModelView::SessionModel
{
public:
    MaterialModel();
    MaterialModel(std::shared_ptr<ModelView::ItemPool> pool);

    static ModelView::ExternalProperty undefined_material();

    std::vector<ModelView::ExternalProperty>
    material_data(std::string container_id = std::string()) const;

    ModelView::ExternalProperty material_property(const std::string& id,
                                                  std::string container_id = std::string());

    MaterialBaseItem* cloneMaterial(const MaterialBaseItem* item);

    SLDMaterialItem* addDefaultMaterial(const ModelView::TagRow& tagrow = {});

private:
    void init_model();
    MaterialContainerItem* materialContainer();
};

#endif //  MATERIALMODEL_H
