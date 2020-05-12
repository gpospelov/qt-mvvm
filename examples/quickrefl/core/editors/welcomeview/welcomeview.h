// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include <memory>

class ApplicationModels;
class ProjectManagerInterface;

//! Welcome view. Main widget on first tab of MainWindow.

class WelcomeView : public QWidget
{
    Q_OBJECT
public:
    WelcomeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~WelcomeView();

public slots:
    std::string onSelectDirRequest();
    std::string onCreateDirRequest();
    int onSaveChangesRequest();

    void onCreateNewProject();
    void onOpenExistingProject();
    void onSaveCurrentProject();

private:
    void init_project_manager();
    std::unique_ptr<ProjectManagerInterface> m_project_manager;
    ApplicationModels* m_models{nullptr};
};

#endif // WELCOMEVIEW_H
