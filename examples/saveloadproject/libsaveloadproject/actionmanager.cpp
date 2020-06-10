// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "actionmanager.h"
#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QMenuBar>

ActionManager::ActionManager(QMainWindow* mainwindow)
    : QObject(mainwindow), m_mainWindow(mainwindow)
{
    createActions();
    createMenus(m_mainWindow->menuBar());
}

void ActionManager::createMenus(QMenuBar* menubar)
{
    auto fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(m_createNewProjectAction);
    fileMenu->addAction(m_openExistingProjectAction);

    fileMenu->addSeparator();
    fileMenu->addAction(m_saveCurrentProjectAction);
    fileMenu->addAction(m_saveProjectAsAction);
}

void ActionManager::onCreateNewProject()
{
    qDebug() << "ActionManager::onCreateNewProject()";
    createNewProjectRequest();
}

void ActionManager::onOpenExistingProject(const QString& dirname)
{
    qDebug() << "ActionManager::onOpenExistingProject()" << dirname;
    openExistingProjectRequest(dirname);
}

void ActionManager::onSaveCurrentProject()
{
    qDebug() << "ActionManager::onSaveCurrentProject()";
    saveCurrentProjectRequest();
}

void ActionManager::onSaveProjectAs()
{
    qDebug() << "ActionManager::onSaveProjectAs()";
    saveProjectAsRequest();
}

//! Creates application-wise actions to create, open, save, and save-as projects.

void ActionManager::createActions()
{
    m_createNewProjectAction = new QAction("&New Project", this);
    m_createNewProjectAction->setShortcuts(QKeySequence::New);
    m_createNewProjectAction->setStatusTip("Create a new project");
    connect(m_createNewProjectAction, &QAction::triggered, this,
            &ActionManager::onCreateNewProject);

    m_openExistingProjectAction = new QAction("&Open Project", this);
    m_openExistingProjectAction->setShortcuts(QKeySequence::Open);
    m_openExistingProjectAction->setStatusTip("Open an existing project");
    connect(m_openExistingProjectAction, &QAction::triggered,
            [this]() { onOpenExistingProject(); });

    m_saveCurrentProjectAction = new QAction("&Save Project", this);
    m_saveCurrentProjectAction->setShortcuts(QKeySequence::Save);
    m_saveCurrentProjectAction->setStatusTip("Save project");
    m_saveCurrentProjectAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveCurrentProjectAction, &QAction::triggered, this,
            &ActionManager::onSaveCurrentProject);

    m_saveProjectAsAction = new QAction("Save &As...", this);
    m_saveProjectAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveProjectAsAction->setStatusTip("Save project under different name");
    connect(m_saveProjectAsAction, &QAction::triggered, this, &ActionManager::onSaveProjectAs);
}
