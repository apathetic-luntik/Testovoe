import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridView {
    //чтобы было всегда по 7 в ряд
    id: calendarView
    property int cellSize: Math.min(width / 7, height / 6)

    model: calendarModel
    cellWidth: cellSize
    cellHeight: cellSize
    
    delegate: Rectangle {
        id: cellDelegate
        
        width: calendarView.cellSize
        height: calendarView.cellSize
        color: {
            if (!isCurrentMonth) return "#f5f5f5"
            return color
        }
        border.color:
        {
           if (isToday) return "#56afb1"
           return "#e0e0e0"
        }
        border.width: {
            if (isToday) return 3
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
                cellDelegate.border.width = 3
                nameDate.text = Qt.formatDate(calendarModel.getDate(), "dddd  -  dd.MM.yyyy ")

            }
        }
    }
}
