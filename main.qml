import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import net.flipback.qmlcomponents 1.0

ApplicationWindow {
    title: qsTr("Mr Promodoro")
    width: 320
    height: 340
    visible: true

    Pomodoro {
        id: pomodoro
        onTick: txTime.text = pomodoro.time
    }

    Text {
        id: txTime
        x: 13
        y: 12
        width: 298
        height: 168
        text: pomodoro.time
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        transformOrigin: Item.Center
        font.pixelSize: 50
    }


    Button {
        id: btStart
        x: 13
        y: 232
        width: 143
        height: 101
        text: qsTr("Start")
        onClicked: { pomodoro.start() }
    }

    Button {
        id: btStop
        x: 168
        y: 232
        width: 143
        height: 101
        text: qsTr("Stop")
        onClicked: { pomodoro.stop() }
    }
}
