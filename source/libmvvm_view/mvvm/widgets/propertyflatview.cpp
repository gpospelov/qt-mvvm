// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/propertyflatview.h"
#include "mvvm/editors/customeditor.h"
#include "mvvm/editors/defaulteditorfactory.h"
#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/viewmodel/standardviewitems.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include "mvvm/widgets/layoututils.h"
#include <QDataWidgetMapper>
#include <QGridLayout>
#include <QLabel>

using namespace ModelView;

struct PropertyFlatView::PropertyFlatViewImpl {
    std::unique_ptr<ViewModel> view_model;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    std::unique_ptr<DefaultEditorFactory> editor_factory;
    std::vector<std::unique_ptr<QDataWidgetMapper>> widget_mappers;
    std::map<ViewItem*, QWidget*> item_to_widget;

    QGridLayout* grid_layout{nullptr};
    PropertyFlatViewImpl()
        : m_delegate(std::make_unique<ViewModelDelegate>())
        , editor_factory(std::make_unique<DefaultEditorFactory>())
        , grid_layout(new QGridLayout)
    {
    }

    //! Creates label for given index.

    std::unique_ptr<QLabel> create_label(ViewItem* view_item)
    {
        auto result = std::make_unique<QLabel>(view_item->data(Qt::DisplayRole).toString());
        result->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
        result->setEnabled(view_item->item()->isEnabled());
        return result;
    }

    //! Creates custom editor for given index.

    std::unique_ptr<CustomEditor> create_editor(const QModelIndex& index)
    {
        auto editor = editor_factory->createEditor(index);
        m_delegate->setEditorData(editor.get(), index);
        connect(editor.get(), &CustomEditor::dataChanged, m_delegate.get(),
                &ViewModelDelegate::onCustomEditorDataChanged);
        editor->setEnabled(view_model->sessionItemFromIndex(index)->isEnabled());
        return editor;
    }

    //! Connect model.

    void connect_model()
    {
        auto on_data_change = [this](const QModelIndex& topLeft, const QModelIndex&,
                                     const QVector<int>& roles) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
            QVector<int> expected_roles = {Qt::ForegroundRole};
#else
            QVector<int> expected_roles = {Qt::TextColorRole};
#endif
            if (roles == expected_roles) {
                auto view_item = view_model->viewItemFromIndex(topLeft);
                auto it = item_to_widget.find(view_item);
                if (it != item_to_widget.end())
                    it->second->setEnabled(view_item->item()->isEnabled());
            }
        };
        connect(view_model.get(), &ViewModel::dataChanged, on_data_change);

        auto on_row_inserted = [this](const QModelIndex&, int, int) { update_grid_layout(); };
        connect(view_model.get(), &ViewModel::rowsInserted, on_row_inserted);

        auto on_row_removed = [this](const QModelIndex&, int, int) { update_grid_layout(); };
        connect(view_model.get(), &ViewModel::rowsRemoved, on_row_removed);
    }

    //! Creates widget for given index to appear in grid layout.

    std::unique_ptr<QWidget> create_widget(const QModelIndex& index)
    {
        auto view_item = view_model->viewItemFromIndex(index);
        if (auto label_item = dynamic_cast<ViewLabelItem*>(view_item); label_item)
            return create_label(label_item);

        return create_editor(index);
    }

    //! Creates row of widget mappers. Each widget mapper will serve all editors in a column.

    void update_mappers()
    {
        widget_mappers.clear();
        for (int row = 0; row < view_model->rowCount(); ++row) {
            auto mapper = std::make_unique<QDataWidgetMapper>();
            mapper->setModel(view_model.get());
            mapper->setItemDelegate(m_delegate.get());
            mapper->setRootIndex(QModelIndex());
            mapper->setCurrentModelIndex(view_model->index(row, 0));
            widget_mappers.emplace_back(std::move(mapper));
        }
    }

    //! Updates grid layout with all editors corresponding to the model.

    void update_grid_layout()
    {
        LayoutUtils::clearGridLayout(grid_layout, true);

        update_mappers();
        item_to_widget.clear();
        for (int row = 0; row < view_model->rowCount(); ++row) {
            for (int col = 0; col < view_model->columnCount(); ++col) {
                auto index = view_model->index(row, col);
                auto widget = create_widget(index);
                item_to_widget[view_model->viewItemFromIndex(index)] = widget.get();
                widget_mappers[static_cast<size_t>(row)]->addMapping(widget.get(), col);
                grid_layout->addWidget(widget.release(), row, col);
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
    p_impl->view_model = Factory::CreatePropertyFlatViewModel(item->model());
    p_impl->view_model->setRootSessionItem(item);
    p_impl->connect_model();
    p_impl->update_grid_layout();
}
