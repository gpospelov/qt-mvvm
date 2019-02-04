// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonutils.h"
#include "sessionmodel.h"
#include "itemmanager.h"
#include "jsonconverterinterfaces.h"
#include <QJsonDocument>
#include <QJsonObject>

std::string ModelView::JsonUtils::ModelToJsonString(const ModelView::SessionModel& model)
{
    QJsonObject json_source;
    model.manager()->converter().model_to_json(model, json_source);
    QJsonDocument document(json_source);
    return QString(document.toJson(QJsonDocument::Indented)).toStdString();

}
