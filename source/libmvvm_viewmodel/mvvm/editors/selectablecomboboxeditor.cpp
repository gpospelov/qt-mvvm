// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

// ----------------------------------------------------------------------------
// https://stackoverflow.com/questions/8422760/combobox-of-checkboxes
// https://stackoverflow.com/questions/21186779/catch-mouse-button-pressed-signal-from-qcombobox-popup-menu
// https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720
// ----------------------------------------------------------------------------

#include "mvvm/editors/selectablecomboboxeditor.h"
#include "mvvm/editors/customeventfilters.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/utils/containerutils.h"
#include <QAbstractItemView>
#include <QComboBox>
#include <QLineEdit>
#include <QMouseEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>

using namespace ModelView;

//! Provides custom style delegate for QComboBox to allow checkboxes.

class QCheckListStyledItemDelegate : public QStyledItemDelegate {
public:
    QCheckListStyledItemDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override
    {
        auto styleOption = const_cast<QStyleOptionViewItem&>(option);
        styleOption.showDecorationSelected = false;
        QStyledItemDelegate::paint(painter, styleOption, index);
    }
};

// ----------------------------------------------------------------------------

SelectableComboBoxEditor::SelectableComboBoxEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_box(new QComboBox)
    , m_wheelEventFilter(new WheelEventFilter(this))
    , m_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheelEventFilter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), &QLineEdit::selectionChanged, m_box->lineEdit(),
            &QLineEdit::deselect);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);
    setConnected(true);
}

QSize SelectableComboBoxEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize SelectableComboBoxEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool SelectableComboBoxEditor::is_persistent() const
{
    return true;
}

//! Propagate check state from the model to ComboProperty.

void SelectableComboBoxEditor::onModelDataChanged(const QModelIndex& topLeft, const QModelIndex&,
                                                  const QVector<int>& roles)
{
#if QT_VERSION > QT_VERSION_CHECK(5, 9, 0)
    // for older versions this role is always empty
    if (!roles.contains(Qt::CheckStateRole))
        return;
#endif

    auto item = m_model->itemFromIndex(topLeft);
    if (!item)
        return;

    ComboProperty comboProperty = m_data.value<ComboProperty>();
    auto state = item->checkState() == Qt::Checked ? true : false;
    comboProperty.setSelected(topLeft.row(), state);

    updateBoxLabel();
    setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void SelectableComboBoxEditor::onClickedList(const QModelIndex& index)
{
    if (auto item = m_model->itemFromIndex(index)) {
        auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

//! Handles mouse clicks on QComboBox elements.

bool SelectableComboBoxEditor::eventFilter(QObject* obj, QEvent* event)
{
    if (isClickToSelect(obj, event)) {
        // Handles mouse clicks on QListView when it is expanded from QComboBox
        // 1) Prevents list from closing while selecting items.
        // 2) Correctly calculates underlying model index when mouse is over check box style
        // element.
        const auto mouseEvent = static_cast<const QMouseEvent*>(event);
        auto index = m_box->view()->indexAt(mouseEvent->pos());
        onClickedList(index);
        return true;
    }
    else if (isClickToExpand(obj, event)) {
        // Expands box when clicking on None/Multiple label
        m_box->showPopup();
        return true;
    }
    else {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void SelectableComboBoxEditor::update_components()
{
    if (!m_data.canConvert<ComboProperty>())
        return;

    ComboProperty property = m_data.value<ComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.values();
    auto selectedIndices = property.selectedIndices();

    for (size_t i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(QString::fromStdString(labels[i]));
        m_model->invisibleRootItem()->appendRow(item);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckable(true);

        auto state = Utils::Contains(selectedIndices, i) ? Qt::Checked : Qt::Unchecked;
        item->setData(state, Qt::CheckStateRole);
    }

    setConnected(true);
    updateBoxLabel();
}

void SelectableComboBoxEditor::setConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_model, &QStandardItemModel::dataChanged, this,
                &SelectableComboBoxEditor::onModelDataChanged);
    }
    else {
        disconnect(m_model, &QStandardItemModel::dataChanged, this,
                   &SelectableComboBoxEditor::onModelDataChanged);
    }
}

//! Update text on QComboBox with the label provided by combo property.

void SelectableComboBoxEditor::updateBoxLabel()
{
    ComboProperty combo = m_data.value<ComboProperty>();
    m_box->setCurrentText(QString::fromStdString(combo.label()));
}

bool SelectableComboBoxEditor::isClickToSelect(QObject* obj, QEvent* event) const
{
    return obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease;
}

bool SelectableComboBoxEditor::isClickToExpand(QObject* obj, QEvent* event) const
{
    return obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease;
}
