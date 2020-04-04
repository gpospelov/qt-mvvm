// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IUnitConverter.h
//! @brief     Defines interface IUnitConverter and possible axis units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IUNITCONVERTER_H
#define IUNITCONVERTER_H

struct AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE, QXQY, RQ4 };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

#endif // IUNITCONVERTER_H
