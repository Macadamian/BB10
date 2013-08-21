import bb.cascades 1.0

ParallelAnimation {
    property alias toY: translate.toY
    property real factor: 1.0
    
    id: animateIn
    animations: [
        TranslateTransition {
            id: translate
            toY: 600
            duration: 700 * factor
            easingCurve: StockCurve.BounceOut
        },
        ScaleTransition {
            id: scale
            fromX: 2.0
            fromY: 2.0
            toX: 1.0
            toY: 1.0
            duration: 400 * factor
        }
    ]
    
    function setTarget(id) {
        translate.target = id;
        scale.target = id;
    }
}
