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


    ListView{
           anchors.fill: parent
           model: dataSourceModel
           delegate: Text {
               width: 100
               height: 31
               text: JSON.stringify(all).value
         }
       }


}
