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

#include "compounditem.h"

class CORE_EXPORT MaterialBaseItem : public ModelView::CompoundItem
{
public:
    static const std::string P_NAME;
    MaterialBaseItem(const std::string& model_type);
protected:
    void register_name();
};

class CORE_EXPORT SLDMaterialItem : public MaterialBaseItem
{
public:    
    static const std::string P_SLD_REAL;
    static const std::string P_SLD_IMAG;

    SLDMaterialItem();
};

#endif // MATERIALITEMS_H

