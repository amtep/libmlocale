/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
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

#ifndef MLISTINDEXFLOATINGVIEW_P_H
#define MLISTINDEXFLOATINGVIEW_P_H

#include "private/mwidgetview_p.h"
#include "mlistindexfloatingview.h"

class MApplicationPage;
class MLabel;
class MListIndex;
class MListIndexFloatingView;
class MPannableViewport;
class MListIndexTooltip;

class QGraphicsLinearLayout;
class QPropertyAnimation;

class MListIndexFloatingViewPrivate : public MWidgetViewPrivate
{
public:
    MListIndexFloatingViewPrivate();
    virtual ~MListIndexFloatingViewPrivate();

    void initLayout();
    void configureController();

    void updateLayout();

    void attachToContainer();

    MListIndexTooltip *tooltip();

    void updateTooltipPosition(const QPointF &pos);
    void updateTooltipData();

    void scrollToGroupHeader(int y);

    void _q_recalculateListIndexRegion();
    void _q_listParentChanged();
    void _q_recalculateTooltipOffsets();

private:
    Q_DECLARE_PUBLIC(MListIndexFloatingView)
    MListIndex *controller;

    MApplicationPage *container;
    QRectF containerRect;

    MListIndexTooltip *tooltipWidget;
    QModelIndex currentScrollToIndex;

    qreal tooltipVerticalOffset;
};

#endif // MLISTINDEXFLOATINGVIEW_P_H