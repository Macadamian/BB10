import bb.cascades 1.0
import lighthouse.app 1.0

Container {
    id: starContainer
    visible: false
    property alias imageLoc: starImage.imageSource
    background: roundedBox.imagePaint
    layoutProperties: AbsoluteLayoutProperties {
        positionX: 10
        positionY: 200
    }
    contextActions: [
        ActionSet {
            title: "Contact"
            ActionItem {
                title: qsTr("Show on Map")
                imageSource: "asset:///images/Menu Icons/ShowOnMap.png"
            }
            ActionItem {
                title: qsTr("Guide me There")
                imageSource: "asset:///images/Menu Icons/GuideMeThere.png"
            }
            ActionItem {
                title: qsTr("Reply")
                imageSource: "asset:///images/Menu Icons/Reply.png"
            }
            ActionItem {
                title: qsTr("Check out the Music")
                imageSource: "asset:///images/Menu Icons/AppWorld.png"
                onTriggered: {
                    invokeBBWorld.invoke("bb.action.OPEN");
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeBBWorld
                        invokeTargetId: "sys.appworld"
                        invokeActionId: "bb.action.OPEN"
                        uri: "appworld://search/Alicia%20Keys"
                    }
                ]
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
                    id: starImage
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
                        text: "Alicia Keys"
                        multiline: true
                        textStyle.fontFamily: "SlatePro-Condensed"
                        textStyle.fontSize: FontSize.Medium
                        textStyle.fontWeight: FontWeight.W500
                    }
                }
                Container {
                    Label {
                        text: "I'll be performing at #BBLive Orlando. Make sure you dont miss it!!!"
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