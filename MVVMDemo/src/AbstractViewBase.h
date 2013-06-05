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
#ifndef ABSTRACTVIEWBASE_H_
#define ABSTRACTVIEWBASE_H_

#include <QObject>
#include <QDebug>
#include "Model.h"

/**
 * Base class giving access to Model class (inherited by ViewModel and ViewController)
 */
class AbstractViewBase: public QObject {
Q_OBJECT
public:
    AbstractViewBase();
    virtual ~AbstractViewBase();

    /**
     * Model accessors to be able to change the underlying model this ViewModel represents
     */
    Model* getModel();
    void setModel(Model* model);

protected:
    /**
     * Functions used to connect/disconnect to signals required to update this view correctly when underlying model changes
     *
     * Empty implementation as default one
     */
    virtual void connectModel(Model* model) {
        Q_UNUSED(model);
        qDebug() << "???? connect " << metaObject()->className();
    }

    virtual void disconnectModel(Model* model) {
        Q_UNUSED(model);
        qDebug() << "???? disconnect " << metaObject()->className();
    }


Q_SIGNALS:
    void modelChanged();

private:
    Model* m_model;
};

#endif /* ABSTRACTVIEWBASE_H_ */
