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

class QMainWindow;
class QAction;
class QMenuBar;
class QToolBar;

//! Actions for MainWindow. Equips toolbar and menubar with actions to create, open, save,
//! and save-as projects. It doesn't have logic and simply forwards requests further.

class ActionManager : public QObject
{
    Q_OBJECT

public:
    ActionManager(QMainWindow* mainwindow = nullptr);

signals:
    void createNewProjectRequest();
    void openExistingProjectRequest(const QString& dirname);
    void saveCurrentProjectRequest();
    void saveProjectAsRequest();

private:
    void createActions();
    void setupMenus(QMenuBar* menubar);
    void setupToolBar(QToolBar* toolbar);

    QMainWindow* m_mainWindow{nullptr};

    QAction* m_createNewProjectAction{nullptr};
    QAction* m_openExistingProjectAction{nullptr};
    QAction* m_saveCurrentProjectAction{nullptr};
    QAction* m_saveProjectAsAction{nullptr};
};

#endif //  ACTIONMANAGER_H
