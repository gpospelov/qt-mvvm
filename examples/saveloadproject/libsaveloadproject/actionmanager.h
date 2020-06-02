// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>

class QAction;

//! Actions for MainWindow.
//! Handles application-wise actions to create, open, save, and save-as projects.


class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(QObject* parent = nullptr);

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString &dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void createActions();

    QAction* m_createNewProjectAction{nullptr};
    QAction* m_openExistingProjectAction{nullptr};
    QAction* m_saveCurrentProjectAction{nullptr};
    QAction* m_saveProjectAsAction{nullptr};
};

#endif //  ACTIONMANAGER_H
