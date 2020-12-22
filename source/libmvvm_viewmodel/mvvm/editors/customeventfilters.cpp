// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/customeventfilters.h"
#include <QAbstractSpinBox>
#include <QComboBox>
#include <QEvent>

using namespace ModelView;

LostFocusFilter::LostFocusFilter(QObject* parent) : QObject(parent) {}

bool LostFocusFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FocusOut)
        return true;

    return QObject::eventFilter(obj, event);
}

// ----------------------------------------------------------------------------

WheelEventFilter::WheelEventFilter(QObject* parent) : QObject(parent) {}

bool WheelEventFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (auto spinBox = qobject_cast<QAbstractSpinBox*>(obj); spinBox) {
        if (event->type() == QEvent::Wheel) {
            if (spinBox->focusPolicy() == Qt::WheelFocus) {
                event->accept();
                return false;
            }
            else {
                event->ignore();
                return true;
            }
        }
        else if (event->type() == QEvent::FocusIn) {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        }
        else if (event->type() == QEvent::FocusOut) {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else if (auto comboBox = qobject_cast<QComboBox*>(obj); comboBox) {
        if (event->type() == QEvent::Wheel) {
            event->ignore();
            return true;
        }
        else {
            event->accept();
            return false;
        }
    }
    return QObject::eventFilter(obj, event);
}
