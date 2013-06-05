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
#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <QObject>
#include <bb/cascades/ArrayDataModel>
#include "AbstractViewBase.h"

/**
 * Class intended to be created once per view (qml). The underlying Model object can be replaced/updated when
 * new data is received.
 *
 * NOTE: in order for this view to behave as expected, signals on underlying Model must be connected/disconnected properly
 * when model changes
 */
class ViewModel: public AbstractViewBase {
Q_OBJECT
public:
    ViewModel();
    virtual ~ViewModel();

    /**
     * Exposed property updated when underlying model changes
     */
    Q_PROPERTY(bb::cascades::ArrayDataModel* allItems READ getAllItems CONSTANT)
    bb::cascades::ArrayDataModel* getAllItems();

    Q_PROPERTY(bb::cascades::ArrayDataModel* evenIndexItems READ getEvenIndexItems CONSTANT)
    bb::cascades::ArrayDataModel* getEvenIndexItems();

protected:
    /**
     * Override
     */
    virtual void connectModel(Model* model);

    /**
     * Override
     */
    virtual void disconnectModel(Model* model);

private Q_SLOTS:
    /**
     * Update the m_items DataModel on Model's listChanged signal
     */
    void onModelListContentChanged();

private:
    /**
     * ArrayDataModel containing all items
     */
    bb::cascades::ArrayDataModel* m_allItems;

    /**
     * ArrayDataModel containing only item at even indexes
     */
    bb::cascades::ArrayDataModel* m_evenIndexItems;
};

#endif /* VIEWMODEL_H_ */
