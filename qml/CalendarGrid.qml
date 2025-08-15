import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: calendarGrid
    spacing: 0
    
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 30
        color: "#e8e8e8"
        border.color: "#d0d0d0"
        border.width: 1
        
        Label {
            id: labelMonth
            anchors.centerIn: parent
            text: qsTr(Qt.formatDate(calendarModel.getDate(), "MMMM yyyy"))
            font.bold: true
            font.pixelSize: 14
            color: "#333333"
        }
        
        Connections {
            target: calendarModel
            onCurrentDateChanged: {
                labelMonth.text = qsTr(Qt.formatDate(calendarModel.getDate(), "MMMM yyyy"))
            }
        }
    }


    RowLayout {
        Layout.fillWidth: true
        spacing: 0
        
        Repeater {
            model: ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"]
            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 25
                color: "#f0f0f0"
                border.color: "#d0d0d0"
                border.width: 1
                
                Label {
                    anchors.centerIn: parent
                    text: modelData
                    font.bold: true
                    font.pixelSize: 11
                    color: "#333333"
                }
            }
        }
    }
    
    // Сетка календаря
    GridView {
        id: calendarView
        Layout.fillWidth: true
        Layout.fillHeight: true
        
        property int cellSize: Math.min(calendarGrid.width / 7, (calendarGrid.height - 30) / 6)
        
        model: calendarModel
        cellWidth: calendarGrid.width / 7
        cellHeight: (calendarGrid.height - 85) / 6
        
        delegate: Rectangle {
            id: cellDelegate
            
            width: calendarView.cellWidth
            height: calendarView.cellHeight
            color: {
                if (!isCurrentMonth) return "#f5f5f5"
                return color
            }
            border.color: {
                if (isToday) return "#56afb1"
                return "#e0e0e0"
            }
            border.width: {
                if (isToday) return 2
                return 1
            }
            
            Rectangle {
                anchors.fill: parent
                anchors.margins: 2
                color: model.color
                opacity: 0.3
                visible: model.averageScore > 0
            }
            
            Label {
                anchors.centerIn: parent
                text: model.dayNumber
                color: isCurrentMonth ? "black" : "gray"
                font.pixelSize: 14
            }
            
            MouseArea {
                anchors.fill: parent
                
                onClicked: {
                    calendarModel.setDate(model.date)
                    metricModel.loadMetricsForDate(model.date)
                    noteModel.loadNotesForDate(model.date)
                    cellDelegate.border.color = "#b05759"
                    cellDelegate.border.width = 2
                    nameDate.text = Qt.formatDate(calendarModel.getDate(), " dd.MM.yyyy ")
                }
            }
        }
    }
}
