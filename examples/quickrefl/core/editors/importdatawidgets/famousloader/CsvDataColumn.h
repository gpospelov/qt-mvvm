// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvDataColumn.h
//! @brief     Defines classes CsvIntensityColumn and CsvCoordinateColumn
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVDATACOLUMN_H
#define CSVDATACOLUMN_H

#include "CsvNamespace.h"
#include "IUnitConverter.h"

class CsvIntensityColumn
{
public:
    // Constructors:
    CsvIntensityColumn();
    CsvIntensityColumn(const CsvIntensityColumn& toCopy);
    CsvIntensityColumn(int colNum, double multiplier, csv::DataColumn values);

    // Getters:
    int columnNumber() const;
    double multiplier() const;
    csv::DataColumn values() const;

    // Setters:
    void setColNum(int const colNum);
    void setMultiplier(double const multiplier);
    void setValues(csv::DataColumn const values);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {});

private:
    int m_colNum;
    double m_multiplier;
    csv::DataColumn m_values;
};

class CsvCoordinateColumn : public CsvIntensityColumn
{
public:
    // Constructors:
    CsvCoordinateColumn();
    CsvCoordinateColumn(const CsvCoordinateColumn& toCopy);
    CsvCoordinateColumn(int colNum, double multiplier, csv::DataColumn values, AxesUnits units);

    // Getters:
    AxesUnits units() const;
    csv::ColumnType name() const { return m_name; }

    // Setters:
    void setUnits(AxesUnits const units);
    void setName(csv::ColumnType const name);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {},
                     AxesUnits units = AxesUnits::NBINS, csv::ColumnType name = csv::_intensity_);

private:
    AxesUnits m_units;
    csv::ColumnType m_name;
};

#endif // CSVDATACOLUMN_H
