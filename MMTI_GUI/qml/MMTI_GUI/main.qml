// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 800
    height: 600
    Text {
        x: 11
        y: 11
        text: qsTr("MMTI TP1")
        anchors.verticalCenterOffset: -280
        anchors.horizontalCenterOffset: -355
        anchors.centerIn: parent
    }
    MouseArea {
        width: 89
        height: 36
        anchors.rightMargin: 711
        anchors.bottomMargin: 564
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Image {
        id: imOri
        x: 11
        y: 51
        width: 350
        height: 350
        source: img_ori

        property alias src_name: imOri.source
    }

    Image {
        id: imEnd
        x: 440
        y: 51
        width: 350
        height: 350
        source: img_fin
    }

    Item {
        id: b_apply
        x: 370
        y: 195
        width: 61
        height: 62
    }
}
