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
import bb.cascades 1.0

Page {
    Container {
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }

            Button {
                text: "Add Item"
                onClicked: {
                    // Use ViewController to forward actions to Model
                    _viewController.appendItem("New Item " + Math.random());
                }
            }

            Button {
                text: "Remove First Item"
                onClicked: {
                    // Use ViewController to forward actions to Model
                    _viewController.removeFirstItem();
                }
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            
            Container {
                Label {
                    text: "All items in model"
                }
                ListView {
                    // DataModel bound to ViewModel Q_PROPERTY
                    dataModel: _viewModel.allItems
                }
            }

            Container {
                Label {
                    text: "Items at even indexes in model"
                }
                ListView {
                    // DataModel bound to ViewModel Q_PROPERTY
                    dataModel: _viewModel.evenIndexItems
                }
            }
        }
    }
}
