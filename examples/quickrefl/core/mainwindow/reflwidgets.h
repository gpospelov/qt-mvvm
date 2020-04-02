// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef REFLWIDGETS_H
#define REFLWIDGETS_H

#include <QWidget>

#include "materialeditor.h"

//! @file reflwidgets.h
//! Collection of placeholders for future reflectometry widgets.

//! Layer graphics scene.

class LayerCanvas : public QWidget
{
    Q_OBJECT
public:
    LayerCanvas(QWidget* parent = nullptr);
};

//! SLD editor.

// FIXME Move title and sizeHints on board of SLDViewWidget and get rid of SLDEditor class.
class SLDViewWidget;

class SLDEditor : public QWidget
{
    Q_OBJECT
public:
    SLDEditor(SLDViewWidget* sld_view = nullptr, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
};

//! Instrument editor.

class InstrumentEditor : public QWidget
{
    Q_OBJECT
public:
    InstrumentEditor(QWidget* parent = nullptr);
};

#endif //  REFLWIDGETS_H
