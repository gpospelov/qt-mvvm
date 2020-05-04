/*
 * This is nearly complete Material design Switch widget implementation in qtwidgets module.
 * More info: https://material.io/design/components/selection-controls.html#switches
 * Copyright (C) 2018 Iman Ahmadvand
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef SWITCH_H
#define SWITCH_H

#include "style.h"
#include <QtWidgets>

namespace SwitchSpace
{

// -------------------------------------------------
//! The animation class
class Animator : public QVariantAnimation
{
    Q_OBJECT
    Q_PROPERTY(QObject* targetObject READ targetObject WRITE setTargetObject)

public:
    explicit Animator(QObject* target, QObject* parent = nullptr);
    ~Animator();

    QObject* targetObject() const;
    void setTargetObject(QObject* target);

    bool isRunning() const { return state() == Running; }

    void setup(int duration, QEasingCurve easing = QEasingCurve::Linear);
    void interpolate(const QVariant& start, const QVariant& end);

protected:
    void updateCurrentValue(const QVariant& value) override;
    void updateState(QAbstractAnimation::State newState,
                     QAbstractAnimation::State oldState) override;

private:
    QPointer<QObject> target;
};

// -------------------------------------------------
//! Abstract button component (uses state changed as signal)
class SelectionControl : public QAbstractButton
{
    Q_OBJECT

public:
    explicit SelectionControl(QWidget* parent = nullptr);
    ~SelectionControl();

    Qt::CheckState checkState() const;

Q_SIGNALS:
    void stateChanged(int);

protected:
    void enterEvent(QEvent*) override;
    void checkStateSet() override;
    void nextCheckState() override;
    virtual void toggle(Qt::CheckState state) = 0;
};

// -------------------------------------------------
//! The main switch class
class Switch : public SelectionControl
{
    Q_OBJECT

public:
    explicit Switch(QWidget* parent = nullptr);
    explicit Switch(bool state, QWidget* parent = nullptr);
    explicit Switch(const QString& text, QWidget* parent = nullptr);
    Switch(const QString& text, const QBrush&, QWidget* parent = nullptr);
    ~Switch();

    QSize sizeHint() const override;
    void init(bool state = false);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void toggle(Qt::CheckState) override;

    QRect indicatorRect();
    QRect textRect();

    static inline QColor colorFromOpacity(const QColor& c, qreal opacity)
    {
        return QColor(c.red(), c.green(), c.blue(), opacity * 255.0);
    }
    static inline bool ltr(QWidget* w)
    {
        if (w)
            return w->layoutDirection() == Qt::LeftToRight;
        return false;
    }

private:
    SwitchStyle::Switch style;
    QPixmap shadowPixmap;
    QPointer<Animator> thumbBrushAnimation;
    QPointer<Animator> trackBrushAnimation;
    QPointer<Animator> thumbPosAniamtion;
};

}; // namespace SwitchSpace

#endif // SWITCH_H