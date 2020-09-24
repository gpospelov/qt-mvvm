// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <mvvm/model/sessionmodel.h>

//! Main application model.

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif
