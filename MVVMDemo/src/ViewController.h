/*
 * Copyright (c) 2013 Macadamian Technologies Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef VIEWCONTROLLER_H_
#define VIEWCONTROLLER_H_

#include <QObject>
#include "AbstractViewBase.h"

/**
 * Class exposing Q_INVOKABLE functions accessible from qml to forward actions to Model directly
 */
class ViewController : public AbstractViewBase{
    Q_OBJECT
public:
    ViewController();
    virtual ~ViewController();

    Q_INVOKABLE
    void appendItem(QVariant item);

    Q_INVOKABLE
    void removeFirstItem();
};

#endif /* VIEWCONTROLLER_H_ */
