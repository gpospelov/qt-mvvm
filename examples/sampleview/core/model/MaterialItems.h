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

/*!
@class MaterialContainerItem
@brief Container to hold MaterialItems.
*/

class MaterialContainerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string T_MATERIALS = "T_MATERIALS";
    MaterialContainerItem();
};

/*!
@class MaterialBaseItem
@brief Base class with all materials with name and color defined.
*/

class MaterialBaseItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_H_X = "P_H_X";
    static inline const std::string P_H_Y = "P_H_Y";
    static inline const std::string P_H_Z = "P_H_Z";

protected:
    MaterialBaseItem(const std::string& model_type);

    //! Creates mag. field-related properties.
    //! Should be called from descendants' constructors in order
    //! to preserve view-oriented property sequence.
    void initMagFields();
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

/*!
@class RefIndexMaterialItem
@brief Represents material based on refractive index.
*/

class RefIndexMaterialItem : public MaterialBaseItem
{
public:
    static inline const std::string P_DELTA = "P_DELTA";
    static inline const std::string P_BETA = "P_BETA";

    RefIndexMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double delta, double beta);
};

#endif // MATERIALITEMS_H
