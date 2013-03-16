#ifndef VALIDATOR_H
#define VALIDATOR_H

// STL
#include <initializer_list>

// Core
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>

// Gui
#include <QtGui/QValidator>

class PipeValidator : public QValidator
{
public:
    PipeValidator( const std::initializer_list<QValidator*> &pipe, QObject* parent = nullptr );
    virtual ~PipeValidator() override;

    virtual void  fixup( QString &input ) const;
    virtual State validate( QString &input, int &pos ) const;

private:
    QList<QValidator*> pipeStore;
};

class Invalidator : public QValidator
{
public:
    Invalidator( QObject* parent = nullptr );
    virtual ~Invalidator();

    virtual void  fixup( QString &input ) const;
    virtual State validate( QString &input, int &pos ) const;
};

#endif /* end of include guard: VALIDATOR_H */
