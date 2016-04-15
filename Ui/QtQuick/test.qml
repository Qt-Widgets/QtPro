import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    Rectangle {
        id:simpleButton
        color: "#2FA9E2"
        width: 150
        height: 75
        anchors.centerIn: parent
        opacity: 0.750
        Text {
            id: buttonlable
            text: qsTr("Submit")
            color: "#FFFFFF"
            anchors.centerIn: parent
            font.family: "Open Sans"
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                console.log("Submit!")
            }
            onEntered: {animateOpacity0.start()}
            onExited: {animateOpacity1.start()}
            cursorShape: Qt.PointingHandCursor
        }
        NumberAnimation {
                id: animateOpacity0
                target: simpleButton
                properties: "opacity"
                from: 0.750
                to: 0.950
                duration: 200
           }
        NumberAnimation {
                id: animateOpacity1
                target: simpleButton
                properties: "opacity"
                from: 0.950
                to: 0.750
                duration: 200
           }
    }
}

