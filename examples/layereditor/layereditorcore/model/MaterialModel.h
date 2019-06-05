// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "sessionmodel.h"

class MaterialContainerItem;

/*!
@class MaterialModel
@brief Model to hold MaterialItems.
*/

class CORE_EXPORT MaterialModel : public ModelView::SessionModel
{
public:
    MaterialModel();

private:
    void init_model();
};

#endif //  MATERIALMODEL_H
