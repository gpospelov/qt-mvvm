// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROFILEHELPER_H
#define PROFILEHELPER_H

#include <utility>
#include <vector>

#include "slice.h"

//! Object that can generate the material profile of a sample as a function of depth.

class ProcessedSample;

class ProfileHelper
{
public:
    ProfileHelper(const multislice_t& sample);
    ~ProfileHelper();

    std::vector<complex_t> calculateProfile(const std::vector<double>& z_values) const;
    std::pair<double, double> defaultLimits() const;

private:
    std::vector<complex_t> m_materialdata;
    std::vector<double> m_zlimits;
    std::vector<double> m_sigmas;
};

#endif // PROFILEHELPER_H
