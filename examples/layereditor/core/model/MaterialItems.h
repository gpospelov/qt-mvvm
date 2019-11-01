// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALITEMS_H
#define MATERIALITEMS_H

/*!
@file MaterialItems.h
@brief Collection of materials to populate MaterialModel.
*/

#include "compounditem.h"
class QColor;

/*!
@class MaterialContainerItem
@brief Container to hold MaterialItems.
*/

class MaterialContainerItem : public ModelView::CompoundItem
{
public:
    MaterialContainerItem();
};

/*!
@class MaterialBaseItem
@brief Base class with all materials with name and color defined.
*/

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

/*!
@class SLDMaterialItem
@brief Represents material based on scattering length density.
*/

class SLDMaterialItem : public MaterialBaseItem
{
public:
    static inline const std::string P_SLD_REAL = "P_SLD_REAL";
    static inline const std::string P_SLD_IMAG = "P_SLD_IMAG";

    SLDMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double real, double imag);
};

#endif // MATERIALITEMS_H
