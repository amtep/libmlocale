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

#ifndef DUIOVERLAYVIEW_H
#define DUIOVERLAYVIEW_H

#include <duioverlaystyle.h>
#include "duiscenewindowview.h"

class DuiOverlay;

class DUI_EXPORT DuiOverlayView : public DuiSceneWindowView
{
    Q_OBJECT
    DUI_VIEW(DuiSceneWindowModel, DuiOverlayStyle)

public:
    DuiOverlayView(DuiOverlay *controller);
    virtual ~DuiOverlayView();

private:
    Q_DISABLE_COPY(DuiOverlayView)
#ifdef UNIT_TEST
    friend class Ut_DuiOverlay;
#endif
};

#endif
