// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef APPMODELS_H
#define APPMODELS_H

#include <memory>

class ViewItemsModel;

/*!
@class ApplicationModels
@brief Container class to hold all SessionModel's used during GUI session.
*/
class ApplicationModels
{
public:
    ApplicationModels();
    ~ApplicationModels();

    ViewItemsModel* viewItemsModel();

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

#endif //  APPMODELS_H
