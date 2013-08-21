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
#include "Model.h"

Model::Model() {
}

Model::~Model() {
}

QVariantList Model::getList() {
    return m_list;
}

void Model::appendItem(QVariant item) {
    m_list.append(item);
    // Emit listContentChanged to notify the ViewModel
    emit listContentChanged();
}

void Model::removeFirstItem() {
    if (m_list.size() > 0) {
        m_list.removeFirst();
        // Emit listContentChanged to notify the ViewModel
        emit listContentChanged();
    }
}
