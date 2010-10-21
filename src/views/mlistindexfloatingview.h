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

#ifndef MLISTINDEXFLOATINGVIEW_H
#define MLISTINDEXFLOATINGVIEW_H

#include <MWidgetView>
#include "mlistindexmodel.h"
#include "mlistindexstyle.h"

class MListIndex;
class MListIndexFloatingViewPrivate;

class MListIndexFloatingView : public MWidgetView
{
    Q_OBJECT
    M_VIEW(MListIndexModel, MListIndexStyle)

public:
    MListIndexFloatingView(MListIndex *controller);
    virtual ~MListIndexFloatingView();

protected:
    /*! \reimp */
    void setupModel();
    void updateData(const QList<const char *> &modifications);

    void drawBackground(QPainter *painter, const QStyleOptionGraphicsItem *option) const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void cancelEvent(MCancelEvent *event);

    void tapAndHoldGestureEvent(QGestureEvent *event, QTapAndHoldGesture *gesture);
    /*! \reimp_end */

private:
    Q_PRIVATE_SLOT(d_func(), void _q_recalculateListIndexRegion())
    Q_PRIVATE_SLOT(d_func(), void _q_recalculateTooltipOffsets())

    Q_DISABLE_COPY(MListIndexFloatingView)
    Q_DECLARE_PRIVATE(MListIndexFloatingView)
};

#endif // MLISTINDEXFLOATINGVIEW_H