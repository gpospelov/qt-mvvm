// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <mvvm/model/sessionmodel.h>

/*!
@class SampleModel
@brief Model to hold layers and multi-layers.
*/

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif //  SAMPLEMODEL_H
