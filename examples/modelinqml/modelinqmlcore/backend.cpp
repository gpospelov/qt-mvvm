// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <modelinqmlcore/backend.h>
#include <modelinqmlcore/particlemodel.h>
#include <modelinqmlcore/particleviewmodel.h>
#include <modelinqmlcore/tablemodel.h>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

struct BackEnd::BackEndImpl {
    std::unique_ptr<ParticleModel> m_model;
    std::unique_ptr<ParticleViewModel> m_viewModel;
    TableModel* m_tableModel{nullptr};

    BackEndImpl()
        : m_model(std::make_unique<ParticleModel>()),
          m_viewModel(std::make_unique<ParticleViewModel>(m_model.get())),
          m_tableModel(new TableModel)
    {
        m_viewModel->setRootSessionItem(m_model->topItem());
    }
};

BackEnd::BackEnd(QObject* parent) : QObject(parent), p_impl(std::make_unique<BackEndImpl>()) {}

BackEnd::~BackEnd() = default;

TableModel* BackEnd::tableModel() const
{
    return p_impl->m_tableModel;
}

ParticleViewModel* BackEnd::particleViewModel() const
{
    return p_impl->m_viewModel.get();
}
