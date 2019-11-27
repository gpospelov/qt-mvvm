// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/widgets/propertyflatview.h>
#include <mvvm/editors/defaulteditorfactory.h>
#include <mvvm/editors/customeditor.h>
#include <mvvm/viewmodel/viewlabelitem.h>

using namespace ModelView;

struct PropertyFlatView::PropertyFlatViewImpl {
    std::unique_ptr<AbstractViewModel> view_model;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    std::unique_ptr<DefaultEditorFactory> editor_factory;
    QGridLayout* grid_layout{nullptr};
    PropertyFlatViewImpl()
        : m_delegate(std::make_unique<ViewModelDelegate>()), editor_factory(std::make_unique<DefaultEditorFactory>()), grid_layout(new QGridLayout)
    {
    }

    std::unique_ptr<QWidget> create_widget(const QModelIndex& index) {
        auto view_item = view_model->itemFromIndex(index);
        if (dynamic_cast<ViewLabelItem*>(view_item)) {
            return std::make_unique<QLabel>(view_item->data(Qt::DisplayRole).toString());
        } else {
            return editor_factory->createEditor(index);
        }
    }

    void update_layout()
    {
        for (int col = 0; col < view_model->columnCount(); ++col) {
            for (int row = 0; row < view_model->rowCount(); ++row) {
                auto index = view_model->index(row, col);
                grid_layout->addWidget(create_widget(index).release(), row, col);



            }
        }
    }
};

PropertyFlatView::PropertyFlatView(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<PropertyFlatViewImpl>())
{
    auto main_layout = new QVBoxLayout;
    main_layout->setMargin(0);
    main_layout->setSpacing(0);

    p_impl->grid_layout->setSpacing(6);
    main_layout->addLayout(p_impl->grid_layout);
    main_layout->addStretch(1);

    setLayout(main_layout);
}

PropertyFlatView::~PropertyFlatView() = default;

void PropertyFlatView::setItem(SessionItem* item)
{
    p_impl->view_model = Utils::CreatePropertyViewModel(item->model());
    p_impl->view_model->setRootSessionItem(item);
    p_impl->update_layout();
}
