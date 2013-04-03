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
        titleBar: TitleBar { title: qsTr("Store Demo") }
        Container {
            leftPadding: 30
            topPadding: 30
            rightPadding: 30
            bottomPadding: 30

            Container {
                horizontalAlignment: HorizontalAlignment.Center
                layoutProperties: StackLayoutProperties { spaceQuota: 9 }
                layout: DockLayout { }
                Container {
                    background: Application.themeSupport.theme.colorTheme.style == VisualStyle.Bright ? Color.Black : Color.LightGray
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 401
                    preferredHeight: 401
                    leftPadding: 1
                    topPadding: 1
                    rightPadding: 1
                    bottomPadding: 1

                    Container {
                        preferredWidth: Infinity
                        preferredHeight: Infinity
                        background: Application.themeSupport.theme.colorTheme.style == VisualStyle.Bright ? Color.White : Color.Black

                        CarouselView {
                            dataModel: XmlDataModel { source: "datamodel_store.xml" }
                        }
                    }
                }
            }
            
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                
                Container {
                    layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                    Button {
                        text: qsTr("Buy")
                    }
                    Button {
                        text: qsTr("More Info")
                    }
                }
            }
        }            
    }
}