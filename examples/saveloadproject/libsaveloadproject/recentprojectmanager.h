// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef RECENTPROJECTMANAGER_H
#define RECENTPROJECTMANAGER_H

#include <QObject>
#include <memory>

class RecentProjectSettings;

//! Main class to coordinate all activity on user's request to create new project,
//! open existing one, or choose one of recent projects on disk.

class RecentProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit RecentProjectManager(QObject* parent = nullptr);
    ~RecentProjectManager() override;

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    std::unique_ptr<RecentProjectSettings> m_recentProjectSettings;
};

#endif // RECENTPROJECTMANAGER_H

