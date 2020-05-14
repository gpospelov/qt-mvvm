// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvReader.cpp
//! @brief     Implements class CsvReader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "importfile.h"

#include <fstream>
#include <iostream>

namespace DataImportLogic
{

//! The constructor
ImportFile::ImportFile(std::string path_to_file) : m_filepath(path_to_file)
{
    loadFile();
    generateThumbnail();
}

//! Generate the thumbnail
void ImportFile::loadFile()
{
    m_file.clear();
    std::ifstream file(m_filepath);
    std::string line;
    while (getline(file, line)) {
        m_file.push_back(line);
        ;
    };
    file.close();
}

//! Retrieve the path
const std::string& ImportFile::path() const
{
    return m_filepath;
}

//! The getter for the thumbnail text
const std::vector<std::string>& ImportFile::thumbnail() const
{
    return m_thumbnail;
}

//! The getter for the thumbnail text
const std::vector<std::string>& ImportFile::file() const
{
    return m_file;
}

//! Generate the thumbnail
void ImportFile::generateThumbnail()
{
    int size = (m_thumbnail_length < m_file.size()) ? (m_thumbnail_length) : (m_file.size());
    m_thumbnail.clear();
    m_thumbnail.resize(size);
    std::ifstream file(m_filepath);
    for (int i = 0; i < size; ++i) {
        getline(file, m_thumbnail[i]);
    };
    file.close();
}

//! Return a precise line
const std::string& ImportFile::line(int line_number) const
{
    return m_file.at(line_number);
}

} // namespace DataImportLogic
