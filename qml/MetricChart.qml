import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    property var metricModel: null

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 15

        // Заголовок графика
        Text {
            Layout.fillWidth: true
            text: "График метрик"
            font.pixelSize: 16
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        // Контейнер для графика
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            border.color: "#cccccc"
            border.width: 1

            // Пустой график с размеченной осью Y
            Rectangle {
                id: emptyChart
                anchors.fill: parent
                anchors.margins: 10
                color: "transparent"
                visible: !metricModel || metricModel.count === 0

                // Ось Y
                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 1
                    color: "#666666"
                }

                // Ось X
                Rectangle {
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    height: 1
                    color: "#666666"
                }

                // Метки оси Y (0-10)
                Repeater {
                    model: 11
                    Rectangle {
                        x: -30
                        y: parent.height * (10 - index) / 10 - 7
                        width: 20
                        height: 14
                        color: "transparent"

                        Text {
                            anchors.centerIn: parent
                            text: index
                            font.pixelSize: 10
                            color: "#666666"
                        }
                    }
                }

                // Сетка
                Repeater {
                    model: 10
                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        y: parent.height * index / 10
                        height: 1
                        color: "#eeeeee"
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "Нет метрик"
                    font.pixelSize: 14
                    color: "#999999"
                }
            }

            // График с метриками
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                visible: metricModel && metricModel.count > 0

                Repeater {
                    model: metricModel ? metricModel.count : 0
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        height: 4
                        property var metricData: metricModel.get(index)

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 5

                            Text {
                                text: metricData.name
                                Layout.preferredWidth: parent.width * 0.3
                                font.pixelSize: 14
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 25
                                color: {
                                    var value = metricData.value
                                    if (value <= 2) return "#ff4444"
                                    else if (value <= 4) return "#ff8800"
                                    else if (value <= 6) return "#ffaa00"
                                    else if (value <= 8) return "#88ff00"
                                    else return "#00ff00"
                                }

                                Rectangle {
                                    width: parent.width * (metricData.value / 10)
                                    height: parent.height
                                    color: Qt.darker(parent.color, 1.2)
                                }
                            }

                            Text {
                                text: metricData.value
                                Layout.preferredWidth: 30
                                horizontalAlignment: Text.AlignRight
                                font.pixelSize: 14
                            }
                        }
                    }
                }
            }
        }
    }
}
