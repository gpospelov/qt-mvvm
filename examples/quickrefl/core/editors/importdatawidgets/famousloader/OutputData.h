// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/OutputData.h
//! @brief     Defines and implements template class OutputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include <vector>

template <typename T> class OutputData
{
public:
    std::vector<T> data;
    int getRank() const { return 1; }
    OutputData<T>* clone() const { return nullptr; }
};

#endif // OUTPUTDATA_H
