// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SAMPLEVIEWDELEGATE_H
#define SAMPLEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <memory>

class CellDecoratorInterface;

/*!
@class SampleViewDelegate
@brief Default delegate for the sample view.
*/

class SampleViewDelegate : public QStyledItemDelegate
{
    using decoration_ptr = std::unique_ptr<CellDecoratorInterface>;

public:
    explicit SampleViewDelegate(QObject* parent = nullptr);
    ~SampleViewDelegate() override;

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    void setCellDecorator(decoration_ptr cell_decoration);

private:
    decoration_ptr m_cell_decorator;
};

#endif // SAMPLEVIEWDELEGATE_H
