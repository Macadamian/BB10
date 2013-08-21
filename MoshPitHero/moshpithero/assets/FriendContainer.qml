import bb.cascades 1.0

Container {
    id: friendContainer
    visible: false
    property alias imageLoc: friendImage.imageSource
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
                title: qsTr("BBM")
                imageSource: "asset:///images/Menu Icons/ic_bbm.png"
            }
            ActionItem {
                title: qsTr("Call")
                imageSource: "asset:///images/Menu Icons/Call.png"
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
                    id: friendImage
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
                        text: "BFF"
                        multiline: true
                        textStyle.fontFamily: "SlatePro-Condensed"
                        textStyle.fontSize: FontSize.Medium
                        textStyle.fontWeight: FontWeight.W500
                    }
                }
                Container {
                    Label {
                        text: "When did you get here? I'm over at the beer tent!!"
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
            Container {
                topPadding: 4
                rightPadding: 20
                Label {
                    text: "2m"
                    textStyle.fontFamily: "SlatePro-Condensed"
                    textStyle.color: Color.create("#797979")
                    textStyle.fontSize: FontSize.XSmall
                    textStyle.fontWeight: FontWeight.W400
                }
                layoutProperties: StackLayoutProperties {
                    spaceQuota: -1
                }
            }
        }
    }
}