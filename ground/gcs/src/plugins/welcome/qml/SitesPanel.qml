// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item {
    id: container
    width: 100
    height: 62

    signal clicked(string url)

    Text {
        id: header
        text: qsTr("Websites")
        width: parent.width
        color: "#44515c"
        font {
            pointSize: 14
            weight: Font.Bold
        }
    }

    ListModel {
        id: sitesModel
        ListElement { link: "" }
        ListElement { link: "https://github.com/SantyPilot/SantyPilot" }
        ListElement { link: "https://github.com/SantyPilot/SantyPilot-doc" }
        function title(index){
            if (title["text"] === undefined) {
            title.text = [
                qsTr("Home"),
                qsTr("Code"),
                qsTr("Doc")
               ]
             }
              return title.text[index]
       }
    }

    ListView {
        id: view
        width: 839
        anchors.topMargin: 30
        anchors { top: parent.top; bottom: parent.bottom }
        orientation: ListView.Horizontal
        model: sitesModel
        spacing: 40  // Need dynamic spacing

        delegate: Text {
            text: view.model.title(index)
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font {
                pointSize: 12
                weight: Font.Bold
            }

            color: mouseArea.containsMouse ? "#224d81" : "black"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    console.log(link)
                    container.clicked(link)
                }
            }
        }
    }
}
