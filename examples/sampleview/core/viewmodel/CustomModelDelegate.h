// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMMODELDELEGATE_H
#define CUSTOMMODELDELEGATE_H

#include <mvvm/viewmodel/viewmodeldelegate.h>

class ApplicationModels;

/*!
@class CustomModelDelegate
@brief Custom delegate to adjust display/editing of SampleModel.

Given implementation will invoke custom material selector while editing corresponding
properties of LayerItem.
*/

class CustomModelDelegate : public ModelView::ViewModelDelegate
{
public:
    explicit CustomModelDelegate(ApplicationModels* models, QObject* parent = nullptr);

};

#endif
