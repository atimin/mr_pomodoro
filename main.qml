/*  Mr. Pomodoro - a little timer to work more effectively. 
 * Copyright (C) 2015 Timin Aleksey
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import net.flipback.qmlcomponents 1.0

ApplicationWindow {
    title: qsTr("Mr. Pomodoro")
    width: 320
    height: 340
    visible: true

    Pomodoro {
        id: pomodoro
        onTick: txTime.text = pomodoro.time
        onStarted: { txState.text = pomodoro.stateName; }
        onStopped: { txState.text = pomodoro.stateName; }
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

    Text {
        id: txState
        x: 33
        y: 199
        text: qsTr("Text")
        font.pixelSize: 12
    }
}
