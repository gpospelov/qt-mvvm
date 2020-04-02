// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialprofile.h"
#include "profilehelper.h"

std::vector<complex_t> MaterialProfile::CalculateProfile(const multislice_t& multilayer,
                                                         int n_points, double z_min, double z_max)
{
    ProfileHelper helper(multilayer);
    std::vector<double> z_values = GenerateZValues(n_points, z_min, z_max);
    return helper.calculateProfile(z_values);
}

std::pair<double, double>
MaterialProfile::DefaultMaterialProfileLimits(const multislice_t& multilayer)
{
    ProfileHelper helper(multilayer);
    return helper.defaultLimits();
}

std::vector<double> MaterialProfile::GenerateZValues(int n_points, double z_min, double z_max)
{
    std::vector<double> result;
    if (n_points < 1)
        return result;
    double step = n_points > 1 ? (z_max - z_min) / (n_points - 1) : 0.0;
    for (int i = 0; i < n_points; ++i) {
        result.push_back(z_min + i * step);
    }
    return result;
}
