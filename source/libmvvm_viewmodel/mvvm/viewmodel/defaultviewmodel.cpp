// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

DefaultViewModel::DefaultViewModel(SessionModel* model, QObject* parent)
  : AbstractViewModel(std::make_unique<DefaultViewModelController>(this), parent)
{
    setSessionModel(model);
}
