// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTMANAGERINTERFACE_H
#define PROJECTMANAGERINTERFACE_H

#include <QObject>
#include <memory>

class ApplicationModelsInterface;

//! Interface class for ProjectManager.
//! Responsible for handling new/save/save-as/close project logic, where project mean collection
//! of serialized application models in project directory.

class ProjectManagerInterface : public QObject
{
    Q_OBJECT
public:

    virtual void createNewProject() = 0;

    virtual void saveCurrentProject() = 0;

    virtual void saveProjectAs() = 0;

    virtual void openExistingProject() = 0;
};

#endif // PROJECTMANAGERINTERFACE_H
