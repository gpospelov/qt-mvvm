// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINBARWIDGET_H
#define MAINBARWIDGET_H

#include <QWidget>
class QStackedWidget;
class QHBoxLayout;

//! Main window with button-bar on top and stacked widget at bottom.

class MainBarWidget : public QWidget
{
    Q_OBJECT

public:
    MainBarWidget(QWidget* parent = nullptr);
    ~MainBarWidget();

    void addWidget(QWidget* widget, const QString& title);

    void setCurrentIndex(int index);

private:
    QStackedWidget* stacked_widget{nullptr};
    QHBoxLayout* button_layout{nullptr};
};

#endif // MAINBARWIDGET_H
