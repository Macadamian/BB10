import bb.cascades 1.0
import lighthouse.app 1.0

Page {
    // Main Container
    Container {
        id: rootContainer
        objectName: "rootContainer"
        layout: AbsoluteLayout {

        }
        ForeignWindowControl {
            id: myForeignWindow
            objectName: "myForeignWindow"
            preferredHeight: 1280
            preferredWidth: 768
            onTouch: {
                rootContainer.reset();
            }
        }
        function reset() {
            _lightHouse.showCocos();
            tweetContainer.visible = false;
            friendContainer.visible = false;
            stageContainer.visible = false;
            starContainer.visible = false;
        }
        TweetContainer{
            id: tweetContainer
            
        }
        function tweetBox(s, t) {
            s = s.replace('app/native/assets/', '');
            console.log(s);
            tweetContainer.imageLoc = s;
            tweetContainer.tweetLabel = t;
            tweetContainer.visible = true;
            _lightHouse.hideCocos();
        }
        FriendContainer {
            id: friendContainer
        }
        function friendBox(s) {
            s = s.replace('app/native/assets/', '');
            console.log(s);
            friendContainer.imageLoc = s;
            friendContainer.visible = true;
            _lightHouse.hideCocos();
        }
        StageContainer {
            id: stageContainer
        }
        function stageBox(s, t) {
            s = s.replace('app/native/assets/', '');
            console.log(s);
            stageContainer.imageLoc = s;
            stageContainer.stageName = t;
            stageContainer.visible = true;
            _lightHouse.hideCocos();
        }
        StarContainer {
            id: starContainer
        }
        function starBox(s) {
            s = s.replace('app/native/assets/', '');
            console.log(s);
            starContainer.imageLoc = s;
            starContainer.visible = true;
            _lightHouse.hideCocos();
        }
        onCreationCompleted: {
            _lightHouse.tweet.connect(tweetBox);
            _lightHouse.buddy.connect(friendBox);
            _lightHouse.star.connect(starBox);
            _lightHouse.stage.connect(stageBox);
            _lightHouse.reset.connect(reset);
        }
        attachedObjects: [
            ImagePaintDefinition {
                id: roundedBox 
                imageSource: "asset:///images/rounded_box.amd"
            }
        ]
    } 
    onCreationCompleted: {
        addAction(searchAction, ActionBarPlacement.OnBar);
        addAction(cameraAction, ActionBarPlacement.OnBar);
    }
    attachedObjects: [
        ActionItem {
            id: searchAction
            title: qsTr("Search")
            ActionBar.placement: ActionBarPlacement.OnBar
            imageSource: "asset:///images/Menu Icons/ic_search.png"
        },
        ActionItem {
            id: cameraAction
            title: qsTr("Camera")
            ActionBar.placement: ActionBarPlacement.OnBar
            imageSource: "asset:///images/Menu Icons/camera.png"
            onTriggered: {
                camera.invoke();
            }
        },
        InvocationWrapper {
            id: camera
            invokeTargetId: "sys.camera.card"
            invokeActionId: "bb.action.CAPTURE"
        }
    ]
}// Page
