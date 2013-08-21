import bb.cascades 1.0
import lighthouse.app 1.0

Page {
    ScrollView {

        Container {
            Label {
                text: "Phone"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "Call"
                    onClicked: {
                        invokeTel.invoke("bb.action.DIAL");
                    }
                }
                Label {
                    text: "Tel: " + "<a href=\"tel:343423\">343343</a>"
                    textFormat: TextFormat.Html
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeTel
                        mimeType: "application/vnd.blackberry.phone.startcall"
                        uri: "tel:10000132"
                    }
                ]
            }

            Label {
                text: "Email"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "Compose email"
                    onClicked: {
                        invokeMail.invoke("bb.action.COMPOSE");
                    }
                }
                Label {
                    text: "Email: " + "<a href=\"mailto:address@domain.com?subject=lighthouse\">me@me.com</a>"
                    textFormat: TextFormat.Html
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeMail
                        uri: "mailto:address@domain.com?subject=lighthouse"
                    }
                ]
            }

            Label {
                text: "Text"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "Text"
                    onClicked: {
                        invokeText.invoke("bb.action.SENDTEXT");
                    }
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeText
                        invokeTargetId: "sys.pim.text_messaging.composer"
                        mimeType: "application/text_messaging"
                    }
                ]
            }
            Label {
                text: "BBM"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "BBM"
                    onClicked: {
                        invokeBBM.invoke("bb.action.BBMCHAT");
                    }
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeBBM
                        invokeTargetId: "sys.bbm.sharehandler"
                    }
                ]
            }

            Label {
                text: "Twitter"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "Twitter"
                    onClicked: {
                        invokeTwitter.invoke("bb.action.SHARE");
                    }
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeTwitter
                        invokeTargetId: "Twitter"
                        invokeActionId: "bb.action.SHARE"
                        uri: "http://www.google.com"
                    }
                ]
            }

            Label {
                text: "BBWorld"
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    text: "BBWorld"
                    onClicked: {
                        invokeBBWorld.invoke("bb.action.OPEN");
                    }
                }
                Label {
                    text: "BB World: " + "<a href=\"appworld://search/pgatour\">BlackBerry</a>"
                    textFormat: TextFormat.Html
                }
                attachedObjects: [
                    InvocationWrapper {
                        id: invokeBBWorld
                        invokeTargetId: "sys.appworld"
                        invokeActionId: "bb.action.OPEN"
                        uri: "appworld://search/pgatour"
                    }
                ]
            }

            Label {
                text: "Hub"
            }

            Container {
                TextField {
                    id: title
                    hintText: "Title"
                    text: "title"
                }
                TextField {
                    id: body
                    hintText: "Body"
                    text: "body"
                }
                Button {
                    text: "Fire the Notification!"
                    onClicked: {
                        alert.title = title.text;
                        alert.body = body.text;
                        alert.category = "vibrate";
                        alert.notify();
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                }
                Button {
                    text: "Kill the Notification!"
                    onClicked: {
                        alert.clearEffects();
                        alert.deleteFromInbox();
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                }
            }

            Label {
            	text: "Calendar"
            }
            TextField {
                id: subjectField
            }

            DateTimePicker {
                id: startTimeField
                title: qsTr ("Start")
            }

            DateTimePicker {
                id: endTimeField
                title: qsTr ("End")
            }

            Container {
                Button {
                    text: "Create event"
                    onClicked: {
                        var a = {};
                        calendar.createEvent();
                    }
                }
            }

            attachedObjects: [
                Notification {
                    id: alert
                },
                Calendar {
                    id: calendar
                    subject: subjectField.text
                    startTime: startTimeField.value
                    endTime: endTimeField.value
                }
            ]
        }
    }
}