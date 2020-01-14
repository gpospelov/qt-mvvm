// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUuid>
#include <mvvm/core/uniqueidgenerator.h>

using namespace ModelView;

identifier_type UniqueIdGenerator::generate()
{
    return QUuid::createUuid().toString().toStdString();
}
