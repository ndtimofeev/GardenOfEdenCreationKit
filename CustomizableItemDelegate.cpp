// Definition
#include <CustomizableItemDelegate.h>

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

CustomizableItemDelegate::CustomizableItemDelegate( QObject* parent ) :
    QStyledItemDelegate( parent ),
    valuePrinterStore( nullptr ),
    editorHandlerStore( nullptr ),
    dataFromModelHandlerStore( nullptr ),
    dataToModelHandlerStore( nullptr )
{
    // body
}

CustomizableItemDelegate::~CustomizableItemDelegate()
{
    // body
}

CustomizableItemDelegate::ValuePrinter CustomizableItemDelegate::valuePrinter() const
{
    return this->valuePrinterStore;
}

CustomizableItemDelegate::DataFromModelHandler CustomizableItemDelegate::dataFromModelHandler() const
{
    return this->dataFromModelHandlerStore;
}

CustomizableItemDelegate::DataToModelHandler CustomizableItemDelegate::dataToModelHandler() const
{
    return this->dataToModelHandlerStore;
}

CustomizableItemDelegate::EditorHandler CustomizableItemDelegate::editorHandler() const
{
    return this->editorHandlerStore;
}

QString CustomizableItemDelegate::displayText( const QVariant &var, const QLocale &locale ) const
{
    return this->valuePrinterStore
        ? this->valuePrinterStore( var, locale )
        : this->QStyledItemDelegate::displayText( var, locale );
}

QWidget* CustomizableItemDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem &o, const QModelIndex &index ) const
{
    return this->editorHandlerStore
        ? this->editorHandlerStore( parent, o, index )
        : this->QStyledItemDelegate::createEditor( parent, o, index );
}

void CustomizableItemDelegate::setValuePrinter( ValuePrinter handler )
{
    this->valuePrinterStore = handler;
}

void CustomizableItemDelegate::setDataFromModelHandler( DataFromModelHandler handler )
{
    this->dataFromModelHandlerStore = handler;
}

void CustomizableItemDelegate::setDataToModelHandler( DataToModelHandler handler )
{
    this->dataToModelHandlerStore = handler;
}

void CustomizableItemDelegate::setEditorHandler( EditorHandler handler )
{
    this->editorHandlerStore = handler;
}

void CustomizableItemDelegate::setEditorData( QWidget* editor, const QModelIndex &index ) const
{
    if ( this->dataFromModelHandlerStore )
        this->dataFromModelHandlerStore( editor, index );
    else
        this->QStyledItemDelegate::setEditorData( editor, index );
}

void CustomizableItemDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex &index ) const
{
    if ( this->dataToModelHandlerStore )
        this->dataToModelHandlerStore( editor, model, index );
    else
        this->QStyledItemDelegate::setModelData( editor, model, index );
}
