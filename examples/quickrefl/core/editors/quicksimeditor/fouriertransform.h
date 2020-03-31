// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include <complex>
#include <mvvm/utils/mathconstants.h>
#include <vector>

using signal_t = std::vector<std::complex<double>>;

//! Implementation of fourier transformation for vector with complex numbers.
//! Taken from C++ STL Cookbook by Jacek Galowicz.

signal_t fourier_transform(const signal_t& signal, bool back_transform = false);

#endif // FOURIERTRANSFORM_H
