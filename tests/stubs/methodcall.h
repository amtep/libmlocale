/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libdui.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef STUBMETHOD_H
#define STUBMETHOD_H

class MethodCall
{
public:
    MethodCall(const QString &name, QList<ParameterBase *> params, ParameterBase *returnValue)
        : _name(name),
          _params(params),
          _returnValue(returnValue) {
    }

    virtual ~MethodCall() {
        foreach(ParameterBase * p, _params) {
            delete p;
        }
    }

    QString name() {
        return _name;
    }

    QList<ParameterBase *> params() {
        return _params;
    }

    template <typename T>
    T parameter(int number) {
        if (number >= _params.count()) {
            qDebug() << "MethodCall::" << __func__ << ": method " << _name << " does not have parameter #" << number
                     << ". Check your test code.";
        }
        Parameter<T>* param = dynamic_cast<Parameter<T>* >(_params[number]);
        if (!param) {
            qDebug() << "MethodCall::" << __func__ << ": failed dynamic_cast, check that parameter type matches parameter number";
        }
        return param->data;
    }

    template <typename T>
    T returnValue() {
        Parameter<T>* value = dynamic_cast<Parameter<T>*>(_returnValue);

        if (!value) {
            qDebug() << "MethodCall::" << __func__ << ": failed dynamic_cast, check that type matches return value";
        }
        return value->data;
    }

    bool returnValueExists() {
        return (_returnValue != NULL);
    }

private:
    QString _name;
    QList<ParameterBase *> _params;
    ParameterBase *_returnValue;

};

#endif
