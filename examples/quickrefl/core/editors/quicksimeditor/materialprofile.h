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

//! Collection of methods borrowed from BornAgain for material profile calculations.

namespace MaterialProfile
{

//! Layer parameters. Data structure to feed simulation with input parameters.
struct Slice {
    double sld_real{0.0};
    double thickness{0.0};
    double top_sigma{0.0};
};

} // namespace MaterialProfile

#endif
