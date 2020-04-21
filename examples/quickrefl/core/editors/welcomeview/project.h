// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECT_H
#define PROJECT_H

#include "projectinterface.h"

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.

class Project : public ProjectInterface
{
    Q_OBJECT
public:

    bool save(const std::string& dirname) const override;

    bool load(const std::string& dirname) override;
};

#endif // PROJECT_H
