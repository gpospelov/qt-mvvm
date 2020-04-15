// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/AxisNames.h
//! @brief     Defines namespace AxisNames.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef AXISNAMES_H
#define AXISNAMES_H

#include "IUnitConverter.h"
#include <map>
#include <string>

//! Contains functions to create maps that give the right axis names for different
//! detector types and units
//! @ingroup simulation

namespace AxisNames
{
std::map<AxesUnits, std::string> InitSphericalAxis0();
std::map<AxesUnits, std::string> InitSphericalAxis1();
std::map<AxesUnits, std::string> InitRectangularAxis0();
std::map<AxesUnits, std::string> InitRectangularAxis1();
std::map<AxesUnits, std::string> InitOffSpecAxis0();
std::map<AxesUnits, std::string> InitOffSpecAxis1();
std::map<AxesUnits, std::string> InitSpecAxis();
std::map<AxesUnits, std::string> InitSpecAxisQ();
std::map<AxesUnits, std::string> InitSampleDepthAxis();
} // namespace AxisNames

#endif // AXISNAMES_H
