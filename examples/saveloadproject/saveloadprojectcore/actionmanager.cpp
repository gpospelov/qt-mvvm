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
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>

ActionManager::ActionManager(QMainWindow* mainwindow)
    : QObject(mainwindow), m_mainWindow(mainwindow)
{
    createActions();
    setupMenus(m_mainWindow->menuBar());
    setupToolBar(m_mainWindow->addToolBar("toolbar"));
}

//! Creates application-wise actions to create, open, save, and save-as projects.

void ActionManager::createActions()
{
    m_createNewProjectAction = new QAction("&New Project", this);
    m_createNewProjectAction->setShortcuts(QKeySequence::New);
    m_createNewProjectAction->setStatusTip("Create a new project");
    connect(m_createNewProjectAction, &QAction::triggered, this,
            &ActionManager::createNewProjectRequest);

    m_openExistingProjectAction = new QAction("&Open Project", this);
    m_openExistingProjectAction->setShortcuts(QKeySequence::Open);
    m_openExistingProjectAction->setStatusTip("Open an existing project");
    connect(m_openExistingProjectAction, &QAction::triggered,
            [this]() { openExistingProjectRequest({}); });

    m_saveCurrentProjectAction = new QAction("&Save Project", this);
    m_saveCurrentProjectAction->setShortcuts(QKeySequence::Save);
    m_saveCurrentProjectAction->setStatusTip("Save project");
    m_saveCurrentProjectAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveCurrentProjectAction, &QAction::triggered, this,
            &ActionManager::saveCurrentProjectRequest);

    m_saveProjectAsAction = new QAction("Save &As...", this);
    m_saveProjectAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveProjectAsAction->setStatusTip("Save project under different name");
    connect(m_saveProjectAsAction, &QAction::triggered, this, &ActionManager::saveProjectAsRequest);
}

//! Equips menu with actions.

void ActionManager::setupMenus(QMenuBar* menubar)
{
    auto fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(m_createNewProjectAction);
    fileMenu->addAction(m_openExistingProjectAction);

    fileMenu->addSeparator();
    fileMenu->addAction(m_saveCurrentProjectAction);
    fileMenu->addAction(m_saveProjectAsAction);
}

void ActionManager::setupToolBar(QToolBar* toolbar)
{
    toolbar->addAction(m_createNewProjectAction);
    toolbar->addSeparator();
    toolbar->addAction(m_openExistingProjectAction);
}
