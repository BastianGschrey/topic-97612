import QtQuick 2.0
import QtQuick.Controls 2.4

StackView {
     id: stackView
     anchors.fill: parent
     // Implements back key navigation
     focus: true
     Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                          stackView.pop();
                          event.accepted = true;
                      }

     initialItem: Item {
         width: parent.width
         height: parent.height
         ListView {
             model: pageModel
             anchors.fill: parent
             delegate: Rectangle {
                 height: 10
                 width: 100
                 Text { text: name }
             }
         }
     }
}


