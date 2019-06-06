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

#include "sessionmodel.h"

/*!
@class SampleModel
@brief Main application model.
*/

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif
