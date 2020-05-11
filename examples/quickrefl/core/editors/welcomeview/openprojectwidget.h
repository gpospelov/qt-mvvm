// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef OPENPROJECTWIDGET_H
#define OPENPROJECTWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class QPushButton;

//! Widget with buttons to create new project or open existing one.
//! Occupies right part of WelcomeView.

class OpenProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenProjectWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    QBoxLayout* createButtonLayout();

    QPushButton* new_project_button{nullptr};
    QPushButton* open_project_button{nullptr};
};

#endif // OPENPROJECTWIDGET_H
