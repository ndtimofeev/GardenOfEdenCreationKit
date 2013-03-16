#ifndef CUSTOMIZABLEITEMDELEGATE_H
#define CUSTOMIZABLEITEMDELEGATE_H

// STL
#include <functional>

// Core
#include <QtCore/QAbstractItemModel>
#include <QtCore/QLocale>
#include <QtCore/QModelIndex>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

// Widgets
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QWidget>

class CustomizableItemDelegate : public QStyledItemDelegate
{
public:
    using ValuePrinter         = std::function<QString ( const QVariant &, const QLocale & )>;
    using EditorHandler        = std::function<QWidget* ( QWidget*, const QStyleOptionViewItem&, const QModelIndex& ) >;
    using DataFromModelHandler = std::function<void ( QWidget*, const QModelIndex& )>;
    using DataToModelHandler   = std::function<void( QWidget*, QAbstractItemModel*, const QModelIndex& )>;

    CustomizableItemDelegate( QObject* parent = nullptr );
    virtual ~CustomizableItemDelegate() override;

    virtual QString      displayText( const QVariant &var, const QLocale &locale ) const override;
    virtual QWidget*     createEditor( QWidget* parent, const QStyleOptionViewItem &o, const QModelIndex &index ) const override;
    virtual void         setEditorData( QWidget* editor, const QModelIndex &index ) const override;
    virtual void         setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex &index ) const override;

    ValuePrinter         valuePrinter() const;
    void                 setValuePrinter( ValuePrinter handler );

    EditorHandler        editorHandler() const;
    void                 setEditorHandler( EditorHandler handler );

    DataFromModelHandler dataFromModelHandler() const;
    void                 setDataFromModelHandler( DataFromModelHandler handler );

    DataToModelHandler   dataToModelHandler() const;
    void                 setDataToModelHandler( DataToModelHandler handler );

private:
    ValuePrinter         valuePrinterStore;
    EditorHandler        editorHandlerStore;
    DataFromModelHandler dataFromModelHandlerStore;
    DataToModelHandler   dataToModelHandlerStore;
};

#endif /* end of include guard: CUSTOMIZABLEITEMDELEGATE_H */
