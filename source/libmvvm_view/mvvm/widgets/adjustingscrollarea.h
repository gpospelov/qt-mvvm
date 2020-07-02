// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H
#define MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H

#include <QScrollArea>

//! Modification of standard scroll area, which makes widget with dynamic layout occupy the whole
//! available space.

class AdjustingScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    AdjustingScrollArea(QWidget* parent = 0);
    void setWidget(QWidget* w);

    QSize sizeHint() const;

private:
    bool eventFilter(QObject* obj, QEvent* ev);
};

#endif // MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H
