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

#include "switch.h"

namespace SwitchSpace
{

#define CORNER_RADIUS 8.0
#define THUMB_RADIUS 14.5
#define SHADOW_ELEVATION 2.0

// -------------------------------------------------
//! The animation class
Animator::Animator(QObject* target, QObject* parent) : QVariantAnimation(parent)
{
    setTargetObject(target);
}

Animator::~Animator()
{
    stop();
}

QObject* Animator::targetObject() const
{
    return target.data();
}

void Animator::setTargetObject(QObject* _target)
{
    if (target.data() == _target)
        return;

    if (isRunning()) {
        qWarning("Animation::setTargetObject: you can't change the target of a running animation");
        return;
    }

    target = _target;
}

void Animator::updateCurrentValue(const QVariant& value)
{
    Q_UNUSED(value);

    if (!target.isNull()) {
        auto update = QEvent(QEvent::StyleAnimationUpdate);
        update.setAccepted(false);
        QCoreApplication::sendEvent(target.data(), &update);
        if (!update.isAccepted())
            stop();
    }
}

void Animator::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if (target.isNull() && oldState == Stopped) {
        qWarning("Animation::updateState: Changing state of an animation without target");
        return;
    }

    QVariantAnimation::updateState(newState, oldState);

    if (!endValue().isValid() && direction() == Forward) {
        qWarning("Animation::updateState (%s): starting an animation without end value",
                 targetObject()->metaObject()->className());
    }
}

void Animator::setup(int duration, QEasingCurve easing)
{
    setDuration(duration);
    setEasingCurve(easing);
}

void Animator::interpolate(const QVariant& _start, const QVariant& end)
{
    setStartValue(_start);
    setEndValue(end);
    start();
}

// -------------------------------------------------
//! Abstract button component (uses state changed as signal)
SelectionControl::SelectionControl(QWidget* parent) : QAbstractButton(parent)
{
    setObjectName("SelectionControl");
    setCheckable(true);
}

SelectionControl::~SelectionControl() {}

void SelectionControl::enterEvent(QEvent* e)
{
    setCursor(Qt::PointingHandCursor);
    QAbstractButton::enterEvent(e);
}

Qt::CheckState SelectionControl::checkState() const
{
    return isChecked() ? Qt::Checked : Qt::Unchecked;
}

void SelectionControl::checkStateSet()
{
    const auto state = checkState();
    emit stateChanged(state);
    toggle(state);
}

void SelectionControl::nextCheckState()
{
    QAbstractButton::nextCheckState();
    SelectionControl::checkStateSet();
}

// -------------------------------------------------
//! The animation class
void Switch::init()
{
    setFont(style.font);
    setObjectName("Switch");

    /* setup animations */
    thumbBrushAnimation = new Animator{this, this};
    trackBrushAnimation = new Animator{this, this};
    thumbPosAniamtion = new Animator{this, this};
    thumbPosAniamtion->setup(style.thumbPosAniamtion.duration, style.thumbPosAniamtion.easing);
    trackBrushAnimation->setup(style.trackBrushAnimation.duration,
                               style.trackBrushAnimation.easing);
    thumbBrushAnimation->setup(style.thumbBrushAnimation.duration,
                               style.thumbBrushAnimation.easing);

    /* set init values */
    trackBrushAnimation->setStartValue(
        colorFromOpacity(style.trackOffBrush, style.trackOffOpacity));
    trackBrushAnimation->setEndValue(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity));
    thumbBrushAnimation->setStartValue(
        colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity));
    thumbBrushAnimation->setEndValue(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity));

    /* set standard palettes */
    auto p = palette();
    p.setColor(QPalette::Active, QPalette::ButtonText, style.textColor);
    p.setColor(QPalette::Disabled, QPalette::ButtonText, style.textColor);
    setPalette(p);
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed));
}

QRect Switch::indicatorRect()
{
    const auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right();
    return ltr(this) ? QRect(0, 0, w, style.height) : QRect(width() - w, 0, w, style.height);
}

QRect Switch::textRect()
{
    const auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right();
    return ltr(this) ? rect().marginsRemoved(QMargins(w, 0, 0, 0))
                     : rect().marginsRemoved(QMargins(0, 0, w, 0));
}

Switch::Switch(QWidget* parent) : SelectionControl(parent)
{
    init();
}

Switch::Switch(const QString& text, QWidget* parent) : Switch(parent)
{
    setText(text);
}

Switch::Switch(const QString& text, const QBrush& brush, QWidget* parent) : Switch(text, parent)
{
    style.thumbOnBrush = brush.color();
    style.trackOnBrush = brush.color();
}

Switch::~Switch() {}

QSize Switch::sizeHint() const
{
    auto h = style.height;
    auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right()
             + fontMetrics().horizontalAdvance(text());

    return QSize(w, h);
}

void Switch::paintEvent(QPaintEvent*)
{
    /* for desktop usage we do not need Radial reaction */

    QPainter p(this);

    const auto _indicatorRect = indicatorRect();
    const auto _textRect = textRect();
    auto trackMargin = style.indicatorMargin;
    trackMargin.setTop(trackMargin.top() + 2);
    trackMargin.setBottom(trackMargin.bottom() + 2);
    QRectF trackRect = _indicatorRect.marginsRemoved(trackMargin);

    if (isEnabled()) {
        p.setOpacity(1.0);
        p.setPen(Qt::NoPen);
        /* draw track */
        p.setBrush(trackBrushAnimation->currentValue().value<QColor>());
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawRoundedRect(trackRect, CORNER_RADIUS, CORNER_RADIUS);
        p.setRenderHint(QPainter::Antialiasing, false);
        /* draw thumb */
        trackRect.setX(trackRect.x() - trackMargin.left() - trackMargin.right() - 2
                       + thumbPosAniamtion->currentValue().toInt());
        auto thumbRect = trackRect;

        if (!shadowPixmap.isNull())
            p.drawPixmap(thumbRect.center() - QPointF(THUMB_RADIUS, THUMB_RADIUS - 1.0),
                         shadowPixmap);
        p.setBrush(thumbBrushAnimation->currentValue().value<QColor>());
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawEllipse(thumbRect.center(), THUMB_RADIUS - SHADOW_ELEVATION - 1.0,
                      THUMB_RADIUS - SHADOW_ELEVATION - 1.0);
        p.setRenderHint(QPainter::Antialiasing, false);

        /* draw text */
        if (text().isEmpty())
            return;
        p.setOpacity(1.0);
        p.setPen(palette().color(QPalette::Active, QPalette::ButtonText));
        p.setFont(font());
        p.drawText(_textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
    } else {
        p.setOpacity(style.trackDisabledOpacity);
        p.setPen(Qt::NoPen);
        // draw track
        p.setBrush(style.trackDisabled);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawRoundedRect(trackRect, CORNER_RADIUS, CORNER_RADIUS);
        p.setRenderHint(QPainter::Antialiasing, false);
        // draw thumb
        p.setOpacity(1.0);
        if (!isChecked())
            trackRect.setX(trackRect.x() - trackMargin.left() - trackMargin.right() - 2);
        else
            trackRect.setX(trackRect.x() + trackMargin.left() + trackMargin.right() + 2);
        auto thumbRect = trackRect;
        if (!shadowPixmap.isNull())
            p.drawPixmap(thumbRect.center() - QPointF(THUMB_RADIUS, THUMB_RADIUS - 1.0),
                         shadowPixmap);
        p.setOpacity(1.0);
        p.setBrush(style.thumbDisabled);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawEllipse(thumbRect.center(), THUMB_RADIUS - SHADOW_ELEVATION - 1.0,
                      THUMB_RADIUS - SHADOW_ELEVATION - 1.0);

        if (text().isEmpty())
            return;
        p.setOpacity(style.disabledTextOpacity);
        p.setPen(palette().color(QPalette::Disabled, QPalette::ButtonText));
        p.setFont(font());
        p.drawText(_textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
    }
}

void Switch::resizeEvent(QResizeEvent* e)
{
    shadowPixmap = SwitchStyle::drawShadowEllipse(THUMB_RADIUS, SHADOW_ELEVATION, QColor(0, 0, 0, 70));
    SelectionControl::resizeEvent(e);
}

void Switch::toggle(Qt::CheckState state)
{
    if (state == Qt::Checked) {
        thumbPosAniamtion->interpolate(
            0, (style.indicatorMargin.left() + style.indicatorMargin.right() + 2) * 2);
        thumbBrushAnimation->interpolate(
            colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity),
            colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity));
        trackBrushAnimation->interpolate(
            colorFromOpacity(style.trackOffBrush, style.trackOffOpacity),
            colorFromOpacity(style.trackOnBrush, style.trackOnOpacity));
    } else { // Qt::Unchecked
        thumbPosAniamtion->interpolate(thumbPosAniamtion->currentValue().toInt(), 0);
        thumbBrushAnimation->interpolate(
            colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity),
            colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity));
        trackBrushAnimation->interpolate(
            colorFromOpacity(style.trackOnBrush, style.trackOnOpacity),
            colorFromOpacity(style.trackOffBrush, style.trackOffOpacity));
    }
}

}; // end SwitchSpace namespace
