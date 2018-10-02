// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeljson.h"
#include "sessionmodel.h"
#include <QJsonObject>


void ModelJson::write(const SessionModel& model, QJsonObject& json)
{
    json[modelKey.c_str()] = QString::fromStdString(model.modelType());
}
