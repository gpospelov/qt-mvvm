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

namespace
{
int widget_height()
{
    return StyleUtils::SizeOfLetterM().height() * 3;
}
} // namespace

ProjectPaneWidget::ProjectPaneWidget(QWidget* parent)
    : QWidget(parent), m_current_project_title(new QLabel(" ")),
      m_current_project_dir(new QLabel(" "))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(widget_height());

    QPalette palette;
    palette.setColor(QPalette::Window, Qt::darkGreen);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_current_project_title);
    layout->addWidget(m_current_project_dir);
}

QSize ProjectPaneWidget::sizeHint() const
{
    auto characterisic_size = StyleUtils::DockSizeHint();
    return QSize(characterisic_size.width(), widget_height());
}

QSize ProjectPaneWidget::minimumSizeHint() const
{
    auto characterisic_size = StyleUtils::DockMinimumSizeHint();
    return QSize(characterisic_size.width(), widget_height());
}

void ProjectPaneWidget::setCurrentProject(const std::string& project_title,
                                          const std::string& project_dir)
{
    m_current_project_title->setText(QString::fromStdString(project_title));

    auto project_dir_str = QString::fromStdString(project_dir);
    m_current_project_dir->setText(ModelView::Utils::WithTildeHomePath(project_dir_str));
    m_current_project_dir->setToolTip(project_dir_str);
}
