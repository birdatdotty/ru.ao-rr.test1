import QtQuick 2.12
import QtQuick.Controls 2.5
import QtWebSockets 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    id:main
    title: qsTr("Scroll")

    WebSocket {
        id: socket
        url: "ws://localhost:3322"
        onTextMessageReceived: {
            myModel.updateData(message);
        }
        onStatusChanged: if (socket.status == WebSocket.Error) {
                             console.log("Error: " + socket.errorString)
                         } else if (socket.status == WebSocket.Open) {
                             socket.sendTextMessage("get")
                         } else if (socket.status == WebSocket.Closed) {
                             console.log("Socket closed")
                         }
        active: false
//        active: true
    }

    function reload() {
        socket.active = true;
        socket.sendTextMessage("get")
    }

    Button {
        text: "обновить";
        width: parent.width;
        onClicked: reload();

    }



    ScrollView {
        x: 0
        y: 50
        width: main.width / 2
        height: main.height - y
        // anchors.fill: parent
        ListView {
            width: parent.width
            model: myModel
            delegate: ItemDelegate {
                text: name_ + " - " + time_
                width: main.width / 2
                onClicked: ta.text = json_
            }
        }
    }
    TextArea {
        id: ta
        x: main.width / 2
        y: 50
        text: ""
    }

}
