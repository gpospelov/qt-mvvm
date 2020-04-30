// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTINTERFACE_H
#define PROJECTINTERFACE_H

#include <QObject>
#include <string>

//! Interface to manipulate projects on disk.
//! Project represents content of all application models in a folder on disk.

class ProjectInterface : public QObject
{
    Q_OBJECT
public:

    virtual std::string projectDir() const = 0;
    virtual bool save(const std::string& dirname) const = 0;
    virtual bool load(const std::string& dirname) = 0;
    virtual bool isModified() const = 0;
signals:
    void modified();
};

#endif // PROJECTINTERFACE_H
