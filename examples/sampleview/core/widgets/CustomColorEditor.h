// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMCOLOREDITOR_H
#define CUSTOMCOLOREDITOR_H

#include <QColorDialog>

/*!
@class CustomColorEditor
@brief QColorDialog with additional functionality for QStyledItemDelegate.
*/

class CustomColorEditor : public QColorDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor userColor READ userColor WRITE setUserColor NOTIFY userColorChanged USER true)

public:
    explicit CustomColorEditor(QWidget* parent = nullptr);

    QColor userColor() const;
    void setUserColor(const QColor& color);

signals:
    void userColorChanged(const QColor& color);
};

#endif // CUSTOMCOLOREDITOR_H
