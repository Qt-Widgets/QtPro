import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    Rectangle {
        id:flatButton
        color: "#2FA9E2"
        width: 150
        height: 75
        anchors.centerIn: parent
        opacity: 0.750
        Text {
            id: buttonlable
            text: qsTr("Submit")
            color: "#FFFFFF"
            x: (flatButton.width/3)+5
            y: flatButton.height/3
            font.family: "Open Sans"
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onPressed: {
                console.log("Submit !")
                animatey0.start()
            }
            onReleased: {
                animatey1.start()
            }

            onEntered: {
                animateOpacity0.start()
            }
            onExited: {
                animateOpacity1.start()
            }
            cursorShape: Qt.PointingHandCursor
        }
        NumberAnimation {
                id: animateOpacity0
                target: flatButton
                properties: "opacity"
                from: 0.750
                to: 0.950
                duration: 200
           }
        NumberAnimation {

                id: animateOpacity1
                target: flatButton
                properties: "opacity"
                from: 0.950
                to: 0.750
                duration: 200
           }
        NumberAnimation {
            id:animatey0
            target: buttonlable
            properties: "y"
            from:buttonlable.y
            to:buttonlable.y+3
            duration: 80
        }
        NumberAnimation {
            id:animatey1
            target: buttonlable
            properties: "y"
            from:buttonlable.y
            to:buttonlable.y-3
            duration: 80
        }
    }
}
