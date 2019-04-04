// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWMODELDELEGATE_H
#define VIEWMODELDELEGATE_H

#include "global.h"
#include <QStyledItemDelegate>
#include <memory>

class QStandardItem;

namespace ModelView
{

class EditorFactory;

//! Model delegate to provide editing/painting for custom variants.

class CORE_EXPORT ViewModelDelegate : public QStyledItemDelegate
{
public:
    explicit ViewModelDelegate(QObject* parent = nullptr);
    ~ViewModelDelegate() override;

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

public slots:
    void onCustomEditorDataChanged();

private:
    void paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                          const QModelIndex& index, const QString& text) const;

    std::unique_ptr<EditorFactory> m_editor_factory;
};

} // namespace ModelView

#endif // VIEWMODELDELEGATE_H
