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
 
This sample demonstrate the MVVM pattern with BB10 and cascades over QT

-A Model is bound to a ViewModel and ViewController (via AbstractViewBase class).
-The ViewModel exposes DataModels which are updated when the Model emits listContentChanged signal
-The ViewController calls exposed Q_INVOKABLE functions on Model in order to modify it