import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    property int metricId: model.id
    property string metricName: model.name
    property int metricValue: model.value
    
    width: parent.width
    height: 60
    color: "white"
    border.color: "#e0e0e0"
    border.width: 1
    radius: 5
    
    RowLayout {

        Layout.fillWidth: true
        Layout.fillHeight: true
        anchors.margins: 10

        Label {

            text: model.name
            Layout.fillWidth: true
            font.pixelSize: 14
        }
        
        SpinBox {
            id: valueSpinBox
            from: 1
            to: 10
            value: model.value
            onValueChanged: {
                if (value !== model.value) {
                    metricModel.updateMetric(model.id, value)
                }
            }
        }
        
        //сделать, чтобы только крестик был, без большой кнопки
        Button {
            text: "×"
            onClicked: metricModel.deleteMetric(model.id)
        }
    }
}
