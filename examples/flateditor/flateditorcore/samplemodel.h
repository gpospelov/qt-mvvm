// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_SAMPLEMODEL_H
#define FLATEDITORCORE_SAMPLEMODEL_H

#include "mvvm/model/sessionmodel.h"

//! Main application model.

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();

private:
    void populateModel();
};

#endif // FLATEDITORCORE_SAMPLEMODEL_H
