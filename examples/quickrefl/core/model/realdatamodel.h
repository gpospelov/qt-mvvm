// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef REALDATAMODEL_H
#define REALDATAMODEL_H

#include <mvvm/model/sessionmodel.h>

//! The model to store imported reflectometry data.

class RealDataModel : public ModelView::SessionModel
{
public:
    RealDataModel();
};

#endif //  REALDATAMODEL_H
