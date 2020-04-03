// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvNamespace.cpp
//! @brief     Implements functions of namespace csv
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvNamespace.h"
#include <fstream>
#include <sstream>

bool csv::isAscii(QString filename)
{
    return true;
    // TODO
    // This function needs to be defined properly (if at all)
    // motivation: ° and Å characters are problematic.
    char c;
    size_t count = 0;
    size_t count_bad = 0;
    std::ifstream is(filename.toStdString());
    while (is.get(c) && count < 1000) {
        count++;
        if (size_t(c) > 255)
            count_bad++;
    }
    is.close();
    double acceptance_threshold = 0.1 * double(count);
    // std::cout << count << "; " << count_bad << std::endl;
    return static_cast<double>(count_bad) <= acceptance_threshold;
}
