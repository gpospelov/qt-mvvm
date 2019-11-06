// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialViewDelegate.h"
#include "MaterialViewController.h"
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

MaterialViewDelegate::MaterialViewDelegate(MaterialViewController& controller, QObject* parent)
    : SampleViewDelegate(parent)
    , m_controller(controller)
{}

MaterialViewDelegate::~MaterialViewDelegate() = default;

bool MaterialViewDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
                                   const QStyleOptionViewItem& option, const QModelIndex& index)
{
    bool has_check_role = index.data(Qt::CheckStateRole).isValid();
    auto mouse_event = dynamic_cast<QMouseEvent*>(event);
    auto event_type = mouse_event ? mouse_event->type() : QEvent::None;
    bool mouse_filtered = event_type == QEvent::MouseButtonPress
                          || event_type == QEvent::MouseButtonRelease
                          || event_type == QEvent::MouseMove;

    if (has_check_role && mouse_event && mouse_filtered) {
        if ((mouse_event->buttons() & Qt::LeftButton) && event_type == QEvent::MouseButtonPress) {
            if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
                m_controller.toggleRowSpanSelection(index);
            else
                m_controller.toggleRowSelection(index);
        }
        return true;
    }

    return SampleViewDelegate::editorEvent(event, model, option, index);
}
