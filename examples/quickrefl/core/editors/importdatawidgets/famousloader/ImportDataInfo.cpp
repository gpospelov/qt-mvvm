// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/ImportDataInfo.cpp
//! @brief     Implements ImportDataInfo helper struct
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ImportDataInfo.h"
#include "AxisNames.h"
#include "OutputData.h"

namespace {
std::vector<AxesUnits> specularUnits()
{
    std::vector<AxesUnits> result;
    const auto units_map = AxisNames::InitSpecAxis();
    for (auto& pair: units_map)
        result.push_back(pair.first);
    return result;
}

// map: data rank --> available units
std::map<size_t, std::vector<AxesUnits>> available_units = {{1u, specularUnits()},
                                                            {2u, {AxesUnits::NBINS}}};
}

ImportDataInfo::ImportDataInfo()
{
}

ImportDataInfo::ImportDataInfo(ImportDataInfo&& other)
    : m_data(std::move(other.m_data))
    , m_units(other.m_units)
{
}

ImportDataInfo::ImportDataInfo(std::unique_ptr<OutputData<double>> data, AxesUnits units)
    : m_data(std::move(data))
    , m_units(units)
{
    checkValidity();
}

ImportDataInfo::ImportDataInfo(std::unique_ptr<OutputData<double>> data, const QString& units_label)
    : m_data(std::move(data))
    , m_units(AxesUnits::DEFAULT)
{
    checkValidity();
}

ImportDataInfo::~ImportDataInfo() = default;

ImportDataInfo::operator bool() const
{
    return static_cast<bool>(m_data);
}

std::unique_ptr<OutputData<double> > ImportDataInfo::intensityData() const &
{
    if (!m_data)
        return nullptr;
    return std::unique_ptr<OutputData<double>>(m_data->clone());
}

std::unique_ptr<OutputData<double> > ImportDataInfo::intensityData() &&
{
    return std::move(m_data);
}

size_t ImportDataInfo::dataRank() const
{
    if (!m_data)
        return 0;
    return m_data->getRank();
}

QString ImportDataInfo::unitsLabel() const
{
    return "Undefined";
//    return JobItemUtils::nameFromAxesUnits(m_units);
}

QString ImportDataInfo::axisLabel(size_t axis_index) const
{
    if (!m_data)
        return "";

    const size_t rank = m_data->getRank();
    if (rank == 2)
        return axis_index == 0 ? "X [nbins]" : "Y [nbins]";
    else if (rank == 1) {
        if (axis_index > 0)
            return "Signal [a.u.]";

        auto label_map = AxisNames::InitSpecAxis();
        return QString::fromStdString(label_map[m_units]);
    }
    throw std::runtime_error("Error in ImportDataInfo::axisLabel: unsupported data type");
}

void ImportDataInfo::checkValidity()
{
    if (!m_data)
        return;
    auto iter = available_units.find(m_data->getRank());
    if (iter == available_units.end())
        throw std::runtime_error("Error in ImportDataInfo constructor: unsupported data type");
    for (auto& value: iter->second)
        if (m_units == value)
            return;

    throw std::runtime_error("Error in ImportDataInfo constructor: inacceptable units passed.");
}
