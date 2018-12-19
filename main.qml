import QtQuick 2.8
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import com.powertune 2.0
import QtQuick.Extras 1.4


ApplicationWindow  {
    visible: true
    width: 800
    height: 480
    minimumWidth: 800
    minimumHeight: 480
    title: qsTr("PowerTune 2.0")
    color: "grey"


    ListView {
        id: listviewMain
        width: 100; height: 800

        model: dataSourceModel
        delegate: mydelegate
        }

    Component {
        id: mydelegate
        Text { text: name + value }
    }

    ComboBox {
        id: cbx_sources
        x: 600
        y: 0
        currentIndex: 1
        textRole: "name"
        width: 200; height: 20
        model: dataSourceModel
    }

    Button {
        id: button
        x: 600
        y: 26
        text: qsTr("Add")
        highlighted: false
        checkable: false
        autoExclusive: false
        checked: false
    }

    Text {
        id: text1
        x: 600
        y: 100
        width: 100
        height: 31
        text: cbx_sources.currentIndex.toString()
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 600
        y: 137
        width: 100
        height: 31

        //text: dataSourceModel.get(cbx_sources.currentIndex).value

        text: dataSourceModel.get(cbx_sources.currentIndex).value

        font.pixelSize: 12
    }

    Connections {
        target: button
        onClicked: debug()
    }



    function debug(){
console.log(dataSourceModel.get(cbx_sources.currentIndex));
}


}


