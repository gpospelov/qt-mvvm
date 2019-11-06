// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/model/uniqueidgenerator.h>
#include <QUuid>

using namespace ModelView;

identifier_type UniqueIdGenerator::generate()
{
    return  QUuid::createUuid().toString().toStdString();
}
