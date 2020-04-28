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

class ProjectManagerInterface;

//! Welcome view. Main widget on first tab of MainWindow.

class WelcomeView : public QWidget
{
    Q_OBJECT
public:
    WelcomeView(QWidget* parent = nullptr);
    ~WelcomeView();

private:
    std::unique_ptr<ProjectManagerInterface> project_manager;
};

#endif // WELCOMEVIEW_H
