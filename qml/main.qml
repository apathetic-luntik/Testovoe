import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import CalendarTracker

ApplicationWindow {
    id: window
    visible: true
    // сделать адаптивное окно под разные размеры
    // сделать чтобы первоначально оно появлялось в левом верхнем углу
    // но с 10% отступом от края экрана
    width: 850
    height: 700
    minimumWidth: 850
    minimumHeight: 700
    maximumWidth: 850
    maximumHeight: 700
    title: qsTr("Трекер дневной статистики")
    color: "#f5f5f5"

    RowLayout {

        ColumnLayout {

        spacing: 10

        // Календарь
        Rectangle {
            //сделать выравнивание по 7 дней
            //добавить названия дней недели и название месяца
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            color: "white"
            border.color: "#e0e0e0"
            radius: 5

            CalendarView {
                id: calendarView
                anchors.fill: parent
                anchors.margins: 10
            }
        }

        // Панель управления
        // выравнивание по самому длиному названию дню недели
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            Rectangle {
                width: previous.width + 10
                height: previous.height
                 // сделать так, чтобы был цвет как у всей панели
                color: "#f5f5f5"
            Button {
                id: previous
                text: qsTr("Предыдущий месяц")
                onClicked: calendarModel.previousMonth()
                anchors.centerIn: parent
                anchors.margins: 10
            }
}
            Label {
                id: nameDate
                text: Qt.formatDate(calendarModel.getDate(), "dddd  -  dd.MM.yyyy ")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
            }
            Rectangle {
                width: next.width + 10
                height: next.height
                 // сделать так, чтобы был цвет как у всей панели
                color: "#f5f5f5"
            Button {
                 id: next
                text: qsTr("Следующий месяц")
                onClicked: calendarModel.nextMonth()
                anchors.centerIn: parent
            }
          }
        }

    // График метрик
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 300
        color: "white"
        border.color: "#e0e0e0"
        radius: 5

        MetricChart {
            id: metricChart
            anchors.fill: parent
            anchors.margins: 10
            metricModel: metricModel
        }
    }
}
    ColumnLayout {
         spacing: 10
         anchors.margins: 10
            // Заметки
            Rectangle {
               Layout.fillWidth: true
               Layout.fillHeight: true
               color: "white"
               border.color: "#e0e0e0"
               radius: 5

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10
                    Label {
                        id: nameNote
                        text: qsTr("Заметки")
                        font.bold: true
                        font.pixelSize: 16
                    }

                    ListView {
                        Layout.fillHeight: true
                        model: noteModel
                        ///прикреплять каждую полседующую заметку к низу предыдущей
                        // когда заметок больше чем места, появляется скрол
                        delegate: NoteDelegate {}

                    }

                    RowLayout {
                        anchors.bottom: parent.bottom
                        spacing: 5

                        TextField {
                            id: noteInput
                            placeholderText: qsTr("Введите заметку...")
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

            // Метрики
            Rectangle {
                Layout.fillWidth: true
               Layout.fillHeight: true
                // сделать высоту как половину рабочего окна
               // цвет не отображается и бордера тоже нет
                color: "white"
                border.color: "#e0e0e0"
                radius: 5

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Label {
                        text: qsTr("Метрики")
                        font.bold: true
                        font.pixelSize: 16
                    }

                    ListView {
                       Layout.fillHeight: true
                        model: metricModel
                        delegate: MetricDelegate {}
                    }

                    RowLayout {
                        anchors.bottom: parent.bottom
                        spacing: 5

                        TextField {
                            id: metricNameInput
                            placeholderText: qsTr("Название метрики...")
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
