import bb.cascades 1.0

Container {
    id: tweetContainer
    visible: false
    property alias imageLoc: tweetImage.imageSource
    property alias tweetLabel: tweetLabel.text
    background: roundedBox.imagePaint
    layoutProperties: AbsoluteLayoutProperties {
        positionX: 10
        positionY: 200
    }
    contextActions: [
        ActionSet {
            title: "Tweet"
            ActionItem {
                title: qsTr("Reply")
                imageSource: "asset:///images/Menu Icons/Reply.png"
            }
            ActionItem {
                title: qsTr("Retweet")
                imageSource: "asset:///images/Menu Icons/Retweet.png"
            }
            ActionItem {
                title: qsTr("Favorite")
                imageSource: "asset:///images/Menu Icons/Favs.png"
            }
            ActionItem {
                title: qsTr("Share")
                imageSource: "asset:///images/Menu Icons/ic_share.png"
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
                    id: tweetImage
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
                        text: "BB10 Fan"
                        multiline: true
                        textStyle.fontFamily: "SlatePro-Condensed"
                        textStyle.fontSize: FontSize.Medium
                        textStyle.fontWeight: FontWeight.W500
                    }
                }
                Container {
                    Label {
                        id: tweetLabel
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