// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALPROFILE_H
#define MATERIALPROFILE_H

#include "slice.h"

//! Collection of methods borrowed from BornAgain for material profile calculations.

namespace MaterialProfile
{

//! Calculate average material profile for given multilayer
std::vector<complex_t> CalculateProfile(const multislice_t& multilayer, int n_points, double z_min,
                                        double z_max);

//! Get default z limits for generating a material profile
std::pair<double, double> DefaultMaterialProfileLimits(const multislice_t& multilayer);

//! Generate z values (equidistant) for use in MaterialProfile
std::vector<double> GenerateZValues(int n_points, double z_min, double z_max);

} // namespace MaterialProfile

#endif
