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
#ifndef MODEL_H_
#define MODEL_H_

#include <QObject>
#include <QVariantList>

/**
 * Reference to the model containing data fetched from API calls/DB/etc
 */
class Model: public QObject {
Q_OBJECT

public:
    Model();
    virtual ~Model();

    QVariantList getList();

    void appendItem(QVariant item);

    void removeFirstItem();

Q_SIGNALS:
    void listContentChanged();

private:
    QVariantList m_list;
};

#endif /* MODEL_H_ */
