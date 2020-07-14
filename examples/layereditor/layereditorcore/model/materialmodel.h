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
#include <mvvm/model/compounditem.h>
#include <vector>

class QColor;

namespace ModelView
{
class ExternalProperty;
}

//! Container to hold MaterialItems.

class MaterialContainerItem : public ModelView::CompoundItem
{
public:
    MaterialContainerItem();
};

//! Base class with all materials with name and color defined.

class MaterialBaseItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_COLOR = "P_COLOR";
    MaterialBaseItem(const std::string& model_type);

protected:
    void register_name();
    void register_color();
};

//! Represents material based on scattering length density.

class SLDMaterialItem : public MaterialBaseItem
{
public:
    static inline const std::string P_SLD_REAL = "P_SLD_REAL";
    static inline const std::string P_SLD_IMAG = "P_SLD_IMAG";

    SLDMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double real, double imag);
};

//! Model to hold MaterialItems.

class MaterialModel : public ModelView::SessionModel
{
public:
    MaterialModel();

    static ModelView::ExternalProperty undefined_material();

    std::vector<ModelView::ExternalProperty> material_data();

    ModelView::ExternalProperty material_property(const std::string& id);

private:
    void init_model();
};

#endif //  MATERIALMODEL_H
