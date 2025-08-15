import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("Трекер дневной статистики")
    color: "#f5f5f5"
    
    // Компактные размеры для двухколоночной верстки
    width: 800
    height: 600
    minimumWidth: 600
    minimumHeight: 500
    
    // Двухколоночная верстка
    RowLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 10
        
        // Колонка 1: Календарь + панель управления + график
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.5
            
            // Календарь
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height * 0.5
                color: "white"
                border.color: "#e0e0e0"
                radius: 5
                
                CalendarGrid {
                    id: calendarView
                    anchors.fill: parent
                    anchors.margins: 5
                }
            }
            
            // Панель управления
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                color: "#f0f0f0"
                border.color: "#e0e0e0"
                radius: 5
                
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    
                    Button {
                        text: "←"
                        onClicked: calendarModel.previousMonth()
                    }
                    
                    Label {
                        text: Qt.formatDate(calendarModel.getDate(), "dd.MM.yyyy")
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                    }
                    
                    Button {
                        text: "→"
                        onClicked: calendarModel.nextMonth()
                    }
                }
            }
            
            // График метрик
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                border.color: "#e0e0e0"
                radius: 5
                
                MetricChart {
                    id: metricChart
                    anchors.fill: parent
                    anchors.margins: 5
                    metricModel: metricModel
                }
            }
        }
        
        // Колонка 2: Заметки и метрики (ровно по половине)
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.5
            
            // Заметки (ровно 50% высоты)
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: parent.height * 0.5
                color: "white"
                border.color: "#e0e0e0"
                radius: 5
                
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    
                    Text {
                        text: qsTr("Заметки")
                        font.bold: true
                        font.pixelSize: 14
                        horizontalAlignment: Text.AlignHCenter
                    }
                    
                    ListView {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        model: noteModel
                        delegate: NoteDelegate {}
                    }
                    
                    RowLayout {
                        Layout.fillWidth: true
                        
                        TextField {
                            id: noteInput
                            placeholderText: qsTr("Новая заметка...")
                            Layout.fillWidth: true
                        }
                        Button {
                            text: qsTr("Добавить")
                            onClicked: {
                                noteModel.addNote(noteInput.text, calendarModel.getDate())
                                noteInput.text = ""
                            }
                        }
                    }
                }
            }
            
            // Метрики (ровно 50% высоты)
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: parent.height * 0.5
                color: "white"
                border.color: "#e0e0e0"
                radius: 5
                
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    
                    Text {
                        text: qsTr("Метрики")
                        font.bold: true
                        font.pixelSize: 14
                        horizontalAlignment: Text.AlignHCenter
                    }
                    
                    ListView {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        model: metricModel
                        delegate: MetricDelegate {}
                    }
                    
                    RowLayout {
                        Layout.fillWidth: true
                        
                        TextField {
                            id: metricNameInput
                            placeholderText: qsTr("Название метрики...")
                            Layout.fillWidth: true
                        }
                        SpinBox {
                            id: metricValueInput
                            from: 1
                            to: 10
                            value: 5
                        }
                        Button {
                            text: qsTr("Добавить")
                            onClicked: {
                                metricModel.addMetric(metricNameInput.text, metricValueInput.value, calendarModel.getDate())
                                metricNameInput.text = ""
                                metricValueInput.value = 5
                            }
                        }
                    }
                }
            }
        }
    }
}
