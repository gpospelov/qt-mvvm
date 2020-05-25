// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectpanewidget.h"
#include "styleutils.h"
#include <QLabel>
#include <QVBoxLayout>
#include <mvvm/widgets/widgetutils.h>

ProjectPaneWidget::ProjectPaneWidget(QWidget* parent)
    : QWidget(parent), m_current_project_title(new QLabel("Untitled")),
      m_current_project_dir(new QLabel("~/development/projects/Untitled"))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(StyleUtils::SizeOfLetterM().height()*5);

    QPalette palette;
    palette.setColor(QPalette::Window, Qt::darkGreen);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_current_project_title);
    layout->addWidget(m_current_project_dir);
}

// QSize ProjectPaneWidget::sizeHint() const
//{

//}

// QSize ProjectPaneWidget::minimumSizeHint() const
//{

//}

void ProjectPaneWidget::setCurrentProject(const std::string& project_title,
                                          const std::string& project_dir)
{
    m_current_project_title->setText(QString::fromStdString(project_title));

    auto project_dir_str = QString::fromStdString(project_dir);
    m_current_project_dir->setText(ModelView::Utils::WithTildeHomePath(project_dir_str));
    m_current_project_dir->setToolTip(project_dir_str);
}
