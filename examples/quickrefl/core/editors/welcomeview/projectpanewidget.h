// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTPANEWIDGET_H
#define PROJECTPANEWIDGET_H

#include <QWidget>

class QLabel;

//! Holds project name and project dir. Part of RecentProjectsWidget.

class ProjectPaneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectPaneWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void setCurrentProject(const std::string& project_title, const std::string& project_dir);

private:
    QLabel* m_current_project_title{nullptr};
    QLabel* m_current_project_dir{nullptr};
};

#endif // PROJECTPANEWIDGET_H
