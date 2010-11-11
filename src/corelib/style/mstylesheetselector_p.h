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

#ifndef MSTYLESHEETSELECTOR_P_H
#define MSTYLESHEETSELECTOR_P_H

#include "mstylesheetselector.h"
#include "mstylesheetattribute.h"

class MStyleSheetSelectorPrivate
{
public:
    //! Parent class name, represented by this selector.
    MUniqueStringCache::Index parentName;
    //! Parent class object name, represented by this selector.
    MUniqueStringCache::Index parentObjectName;
    //! Object name, represented by this selector.
    MUniqueStringCache::Index objectName;
    //! Class name, represented by this selector.
    MUniqueStringCache::Index className;
    //! Type, represented by this selector.
    MUniqueStringCache::Index classType;
    //! Screen orientation type, represented by this selector.
    MStyleSheetSelector::Orientation screenOrientation;
    //! Object mode, represented by this selector.
    MUniqueStringCache::Index objectMode;
    //! Attribute list of this selector (ClassName#ObjectName.Orientation:Mode).
    MAttributeList attributes;
    //! Name of the css file where the selector was created.
    MUniqueStringCache::Index fileName;
    //! Flags indicating whether this is a special kind of selector.
    MStyleSheetSelector::Flags flags;

    void operator=(const MStyleSheetSelectorPrivate &);
};

#endif //MSTYLESHEETSELECTOR_P_H
