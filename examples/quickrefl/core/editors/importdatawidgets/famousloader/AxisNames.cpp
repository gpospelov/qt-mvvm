// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/AxisNames.cpp
//! @brief     Implements functions in namespace AxisNames.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AxisNames.h"
#include <map>

namespace AxisNames
{
// For spherical detectors in GISAS simulations
std::map<AxesUnits, std::string> InitSphericalAxis0()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "X [nbins]";
    result[AxesUnits::RADIANS] = "phi_f [rad]";
    result[AxesUnits::DEGREES] = "phi_f [deg]";
    result[AxesUnits::QSPACE] = "Qy [1/nm]";
    result[AxesUnits::QXQY] = "Qx [1/nm]";
    return result;
}
std::map<AxesUnits, std::string> InitSphericalAxis1()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "Y [nbins]";
    result[AxesUnits::RADIANS] = "alpha_f [rad]";
    result[AxesUnits::DEGREES] = "alpha_f [deg]";
    result[AxesUnits::QSPACE] = "Qz [1/nm]";
    result[AxesUnits::QXQY] = "Qy [1/nm]";
    return result;
}
// For rectangular detectors in GISAS simulations
std::map<AxesUnits, std::string> InitRectangularAxis0()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "X [nbins]";
    result[AxesUnits::RADIANS] = "phi_f [rad]";
    result[AxesUnits::DEGREES] = "phi_f [deg]";
    result[AxesUnits::MM] = "X [mm]";
    result[AxesUnits::QSPACE] = "Qy [1/nm]";
    result[AxesUnits::QXQY] = "Qx [1/nm]";
    return result;
}
std::map<AxesUnits, std::string> InitRectangularAxis1()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "Y [nbins]";
    result[AxesUnits::RADIANS] = "alpha_f [rad]";
    result[AxesUnits::DEGREES] = "alpha_f [deg]";
    result[AxesUnits::MM] = "Y [mm]";
    result[AxesUnits::QSPACE] = "Qz [1/nm]";
    result[AxesUnits::QXQY] = "Qy [1/nm]";
    return result;
}
// For off-specular simulations (both spherical and rectangular detectors)
// Currently 'mm' is not supported for the y-axis
std::map<AxesUnits, std::string> InitOffSpecAxis0()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "X [nbins]";
    result[AxesUnits::RADIANS] = "alpha_i [rad]";
    result[AxesUnits::DEGREES] = "alpha_i [deg]";
    return result;
}
std::map<AxesUnits, std::string> InitOffSpecAxis1()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "Y [nbins]";
    result[AxesUnits::RADIANS] = "alpha_f [rad]";
    result[AxesUnits::DEGREES] = "alpha_f [deg]";
    return result;
}

std::map<AxesUnits, std::string> InitSpecAxis()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "X [nbins]";
    result[AxesUnits::RADIANS] = "alpha_i [rad]";
    result[AxesUnits::DEGREES] = "alpha_i [deg]";
    result[AxesUnits::QSPACE] = "Q [1/nm]";
    result[AxesUnits::RQ4] = "Q [1/nm]";
    return result;
}

std::map<AxesUnits, std::string> InitSpecAxisQ()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "X [nbins]";
    result[AxesUnits::QSPACE] = "Q [1/nm]";
    result[AxesUnits::RQ4] = "Q [1/nm]";
    return result;
}

// corner case: axis corresponding to the position
// across sample is accepts only bins and nanometers,
// but the units specified in dedicated unit
// converter correspond to inclination angular axis.
// For this reason depth axis map returns always
// nanometers except for bins.
std::map<AxesUnits, std::string> InitSampleDepthAxis()
{
    std::map<AxesUnits, std::string> result;
    result[AxesUnits::NBINS] = "Y [nbins]";
    result[AxesUnits::RADIANS] = "Position [nm]";
    result[AxesUnits::DEGREES] = "Position [nm]";
    result[AxesUnits::QSPACE] = "Position [nm]";
    return result;
}

} // namespace AxisNames
