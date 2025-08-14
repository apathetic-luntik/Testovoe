import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    property int noteId: model.id
    property string noteText: model.text
    
    width: parent.width
    height: 50
    color: "white"
    border.color: "#e0e0e0"
    border.width: 1
    radius: 5
    
    RowLayout {

        anchors.margins: 10
        Layout.fillWidth: true
        Layout.fillHeight: true
        TextField {
            id: noteTextField
            Layout.fillWidth: true
            text: model.text
            onEditingFinished: {
                if (text !== model.text) {
                    noteModel.updateNote(model.id, text)
                }
            }
        }
        
        //крестик сделать полупрозрачным и вверху заметки
        Button {
            text: "×"
            onClicked: noteModel.deleteNote(model.id)
        }
    }
}
