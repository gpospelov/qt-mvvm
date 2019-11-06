// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
#define MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H

#include <mvvm/viewmodel/abstractviewmodel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only top level items are shown, all property items are filtered out.

class CORE_EXPORT TopItemsViewModel : public AbstractViewModel
{
public:
    TopItemsViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
