import bb.cascades 1.0

Container {
    id: stageContainer
    visible: false
    property alias imageLoc: stageImage.imageSource
    property alias stageName: stageName.text
    background: roundedBox.imagePaint
    layoutProperties: AbsoluteLayoutProperties {
        positionX: 10
        positionY: 200
    }
    contextActions: [
        ActionSet {
            title: "Contact"
            ActionItem {
                title: qsTr("Arrange a Meeting Point")
                imageSource: "asset:///images/Menu Icons/ArrangeMeetingPoint.png"
            }
            ActionItem {
                title: qsTr("Favorite")
                imageSource: "asset:///images/Menu Icons/Favs.png"
            }
            ActionItem {
                title: qsTr("Show on Map")
                imageSource: "asset:///images/Menu Icons/ShowOnMap.png"
            }
        }
    ]
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        Container {
            topPadding: 16
            leftPadding: 16
            bottomPadding: 16
            Container {
                minWidth: 96
                minHeight: 96
                ImageView {
                    id: stageImage
                    minWidth: 96
                    minHeight: 96
                    scalingMethod: ScalingMethod.AspectFit
                }
            }
        }
        Container {
            leftPadding: 16
            rightPadding: 16
            bottomPadding: 8
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Container {
                rightPadding: 8
                Container {
                    bottomPadding: 4
                    Label {
                        id: stageName
                        multiline: true
                        textStyle.fontFamily: "SlatePro-Condensed"
                        textStyle.fontSize: FontSize.Medium
                        textStyle.fontWeight: FontWeight.W500
                    }
                }
                Container {
                    Label {
                        text: "7pm: Alicia Keya\n10pm: Bruno Mars"
                        multiline: true
                        textStyle.fontFamily: "SlatePro-Condensed"
                        textStyle.fontSize: FontSize.Small
                        textStyle.fontWeight: FontWeight.W400
                        content.flags: TextContentFlag.ActiveText
                    }
                }
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
            }
        }
    }
}