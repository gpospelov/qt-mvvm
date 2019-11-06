// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_CORE_EXPORT_H
#define MVVM_CORE_EXPORT_H

#ifdef _WIN32

#ifdef CORE_BUILD_DLL

#define CORE_EXPORT __declspec(dllexport)
#else
#define CORE_EXPORT __declspec(dllimport)
#endif  // CORE_BUILD_DLL

#endif  // _WIN32

#ifndef CORE_EXPORT
#define CORE_EXPORT
#endif

#endif // MVVM_CORE_EXPORT_H
