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

#ifndef PUSHBUTTONPAGE_H
#define PUSHBUTTONPAGE_H

#include "listpage.h"
#include "templatepage.h"
#include <DuiApplicationPage>
#include <DuiLayout>
#include <DuiGridLayoutPolicy>

class DuiButton;
class DuiButtonGroup;
class DuiWidget;
class DuiLabel;

class PushButtonPage : public TemplatePage
{
    Q_OBJECT
public:
    PushButtonPage();
    virtual ~PushButtonPage();
    virtual QString timedemoTitle();
    virtual void createContent();
protected:
    virtual void retranslateUi();
private:
    DuiButton *pushButton1;
    DuiButton *pushButton2;
    DuiButton *pushButton3;
};

#endif
