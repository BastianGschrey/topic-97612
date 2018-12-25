import QtQuick 2.8
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import com.powertune 2.0
import QtQuick.Extras 1.4
import QtQml.Models 2.3
import "qrc:/createSquareGaugeScript.js" as CreateSquareGaugeScript


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
        Text { text: name + " " + value }
    }

    ItemSelectionModel{
        id: ism
        model: dataSourceModel

    }

        ComboBox {
            id: cbx_sources
            x: 600
            y: 0
            textRole: "name"
            width: 200;
            model: dataSourceModel
            //onCurrentIndexChanged: text2.text = dataSourceModel.get(currentIndex).value
            Component.onCompleted: currentIndex = 1
        }
        Button {
            id: button
            x: 700
            y: 46
            text: qsTr("Add")
            highlighted: false
            checkable: false
            autoExclusive: false
            checked: false
            onClicked: text2.text = dataSourceModel.data(dataSourceModel.index(cbx_sources.currentIndex,0))



            }



    Text {
            id: text1
            x: 700
            y: 134
            width: 100
            height: 31
            text: cbx_sources.currentIndex.toString()
            font.pixelSize: 12
        }
        Text {
            id: text2
            x: 700
            y: 92
            width: 100
            height: 31
            font.pixelSize: 12
        }


}

