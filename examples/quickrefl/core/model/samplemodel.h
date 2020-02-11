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

//! Model to hold layers and multi-layers.
class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

    void create_default_multilayer();
};

#endif //  SAMPLEMODEL_H
