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

//! @file reflwidgets.h
//! Collection of placeholders for future reflectometry widgets.


//! Material editor.

class MaterialEditor : public QWidget
{
    Q_OBJECT
public:
    MaterialEditor(QWidget* parent = nullptr);
};

//! Layer editor.

class LayerEditor : public QWidget
{
    Q_OBJECT
public:
    LayerEditor(QWidget* parent = nullptr);
};

//! Layer graphics scene.

class LayerCanvas : public QWidget
{
    Q_OBJECT
public:
    LayerCanvas(QWidget* parent = nullptr);
};

//! SLD editor.

class SLDEditor : public QWidget
{
    Q_OBJECT
public:
    SLDEditor(QWidget* parent = nullptr);
};

//! Reflectivity plot.

class ReflPlotWidget : public QWidget
{
    Q_OBJECT
public:
    ReflPlotWidget(QWidget* parent = nullptr);
};

//! Instrument editor.

class InstrumentEditor : public QWidget
{
    Q_OBJECT
public:
    InstrumentEditor(QWidget* parent = nullptr);
};

#endif //  REFLWIDGETS_H
