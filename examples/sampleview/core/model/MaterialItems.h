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
    static const std::string T_MATERIALS;
    MaterialContainerItem();
};

/*!
@class MaterialBaseItem
@brief Base class with all materials with name and color defined.
*/

class MaterialBaseItem : public ModelView::CompoundItem
{
public:
    static const std::string P_COLOR;
    static const std::string P_NAME;
    static const std::string P_H_X;
    static const std::string P_H_Y;
    static const std::string P_H_Z;

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
    static const std::string P_SLD_REAL;
    static const std::string P_SLD_IMAG;

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
    static const std::string P_DELTA;
    static const std::string P_BETA;

    RefIndexMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double delta, double beta);
};

#endif // MATERIALITEMS_H

