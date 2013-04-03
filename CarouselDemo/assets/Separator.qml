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

/**
 * Separator - A vertical or horizontal line that will fill 
 * the parent's available width or height depending on orientation.
 *
 * Intended usage:
 *
 * Container {
 *      // ... some controls ...
 *
 *      Separator { } // Defaults to 1 pixel horizontal line
 *
 *      // ... more controls ....
 * }
 *
 * The thickness, orientation and color can be set:
 *
 * Separator {
 *     thickness: 1
 *     vertical: true
 *     color: Color.Cyan
 * }
 *
 * The default values for the thickness, vertical and color properties
 * are documented below.
 */
Container {
    /**
     * Thickness in pixels. Defaults to 1.
     */
    property int thickness: 1
    
    /**
     * Color of the separator. Defaults to Color.Black when the
     * theme is Bright, and Color.LightGray when the theme is Dark.
     */
    property alias color: me.background
    
    /**
     * Orientation of the separator. Defaults to true (vertical) when
     * the parent's layout is a LeftToRight or RightToLeft oriented 
     * StackLayout, false (horizontal) otherwise.
     *
     * N.B. Because the parent property is not notifyable, this property
     * will not change automatically if the parent changes.
     */
    property bool vertical: (notifyableParent && notifyableParent.layout) ? notifyableParent.layout.orientation == LayoutOrientation.LeftToRight || notifyableParent.layout.orientation == LayoutOrientation.RightToLeft : false

    /*
     * This is where the magic happens, making this Container a Separator.
     */
    id: me
    background: Application.themeSupport.theme.colorTheme.style == VisualStyle.Bright ? Color.Black : Color.LightGray

    minHeight: vertical ? 0 : thickness
    maxHeight: vertical ? Infinity: thickness
    preferredHeight: vertical ? 0 : thickness // 0 is 'not set'
    verticalAlignment: vertical ? VerticalAlignment.Fill : VerticalAlignment.Top // Top is the vertical alignment's default value
    
    minWidth: vertical ? thickness : 0
    maxWidth: vertical ? thickness : Infinity
    preferredWidth: vertical ? thickness : 0 // 0 is 'not set'
    horizontalAlignment: vertical ? HorizontalAlignment.Left : HorizontalAlignment.Fill // Left is the horizontal alignment's default value
    
    // Hack to shut up "property depends on non-notifyable property". Parent isn't going to change, so we only need its value once anyway.
    property variant notifyableParent
    onCreationCompleted: notifyableParent = parent
}