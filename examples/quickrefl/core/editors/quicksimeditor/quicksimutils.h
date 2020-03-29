// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef QUICKSIMUTILS_H
#define QUICKSIMUTILS_H

#include "slice.h"
class MultiLayerItem;

//! Collection of utility funcitons for running quick simulations.
namespace Utils
{

//! Creates multi-slice presentation of internal multilayer structure.
multislice_t CreateMultiSlice(const MultiLayerItem& multilayer);

} // namespace Utils

#endif // QUICKSIMUTILS_H
