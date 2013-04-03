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

Tab {
    Page {
        id: page
        titleBar: TitleBar { } // Title when carousel's content is changed
        CarouselView {
            preferredWidth: Infinity
            preferredHeight: Infinity
            dataModel: XmlDataModel { source: "datamodel_full.xml" }
            onVisibleItemDataChanged: visibleItemData && visibleItemData.title ? page.titleBar.title = visibleItemData.title.toString() : "" // need toString() here or else titleBar is blank?
            listItemComponents: ListItemComponent {
                type: "page"

                ScrollView {
                    id: scrollview

                    Container {
                        leftPadding: 30
                        topPadding: 30
                        rightPadding: 30
                        bottomPadding: 30
                        minHeight: scrollview.ListItem.view.layoutFrame.height
                        preferredWidth: scrollview.ListItem.view.layoutFrame.width

                        ImageView {
                            imageSource: ListItemData.imgsrc
                            horizontalAlignment: HorizontalAlignment.Center
                        }

                        Separator {
                            thickness: 30
                            color: Color.Transparent
                        }

                        Label {
                            text: ListItemData.body
                            horizontalAlignment: HorizontalAlignment.Center
                            multiline: true
                            textFormat: TextFormat.Html
                        }
                    }
                }
            }
        }
    }
}