// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <mvvm/model/sessionmodel.h>

//! Contains results of quick reflectometry simulations.
// TODO make JobModel part of ApplicationModels

class JobModel : public ModelView::SessionModel
{
public:
    JobModel();

private:
    void init_model();
};

#endif //  JOBMODEL_H
