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
#include "ViewModel.h"
#include <QDebug>

ViewModel::ViewModel() {
    // Initialize DataModel in ViewModel constructor because the instance itself will never change
    m_allItems = new bb::cascades::ArrayDataModel(this);
    m_evenIndexItems = new bb::cascades::ArrayDataModel(this);
}

ViewModel::~ViewModel() {
}

bb::cascades::ArrayDataModel* ViewModel::getAllItems() {
    return m_allItems;
}

bb::cascades::ArrayDataModel* ViewModel::getEvenIndexItems() {
    return m_evenIndexItems;
}

void ViewModel::connectModel(Model* model) {
    if (model) {
        if (!connect(model, SIGNAL(listContentChanged()), this, SLOT(onModelListContentChanged()))) {
            qDebug() << "Unabled to connect to model listChanged signal";
        }
    }
}

void ViewModel::disconnectModel(Model* model) {
    if (model) {
        if (!disconnect(model, SIGNAL(listContentChanged()), this, SLOT(onModelListContentChanged()))) {
            qDebug() << "Unabled to disconnect from model listChanged signal";
        }
    }
}

void ViewModel::onModelListContentChanged() {
    QVariantList modelList = getModel()->getList();
    int modelListSize = modelList.size();

    // TODO: better update logic
    m_allItems->clear();
    m_evenIndexItems->clear();

    if (modelListSize == 0) {
        return;
    }

    int dataModelSize = m_allItems->size();
    qDebug() << QString("modelList has %1 items, DataModel has %2 items").arg(modelListSize).arg(dataModelSize);

    // Append all items in the correct model
    m_allItems->append(modelList);

    // Append even index items in the appropriate model
    for (int i = 0; i < modelListSize; i += 2) {
        QVariant item = modelList.at(i);
        m_evenIndexItems->append(item);
    }
}

