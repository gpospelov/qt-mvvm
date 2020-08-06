// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONDOCUMENT_H
#define MVVM_SERIALIZATION_JSONDOCUMENT_H

#include <initializer_list>
#include <memory>
#include <mvvm/interfaces/modeldocumentinterface.h>

namespace ModelView
{

class SessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.

class MVVM_MODEL_EXPORT JsonDocument : public ModelDocumentInterface
{
public:
    JsonDocument(std::initializer_list<SessionModel*> models);
    ~JsonDocument() override;

    void save(const std::string& file_name) const override;
    void load(const std::string& file_name) override;

private:
    struct JsonDocumentImpl;
    std::unique_ptr<JsonDocumentImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_ITEMBACKUPSTRATEGY_H
