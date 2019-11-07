// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/editors/customeventfilters.h>
#include <QEvent>

using namespace ModelView;

LostFocusFilter::LostFocusFilter(QObject* parent) : QObject(parent) {}

bool LostFocusFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FocusOut)
        return true;

    return QObject::eventFilter(obj, event);
}
