import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

ApplicationWindow {
    id:root
    width: 1600
    height: 1200
    visible: true
    title: qsTr("Car Dashboard By Aksh")
    color: "#000000"

    //background
    background: Image{
        anchors.fill:parent
        source: "../icons/Background.png"
    }

    // Base Layer

    Image {
        anchors.centerIn: parent
        sourceSize: Qt.size(1492,717)
        source: "../icons/Base.svg"



        Image{
            id:topNavigation
            anchors{
                bottom:navigation_car.top
                bottomMargin: 50
                horizontalCenter: parent.horizontalCenter
            }

            source: "../icons/Top Navigation.svg"

            RowLayout{
                anchors.centerIn: parent
                spacing: 60
                MyButton{
                    setIcon: isGlow ? "../icons/light/bxs_music.svg" : "../icons/bxs_music.svg"
                    onClicked: isGlow = !isGlow
                }
                MyButton{
                    setIcon: isGlow ? "../icons/light/ep_menu.svg" :  "../icons/ep_menu.svg"
                    onClicked: isGlow = !isGlow
                }
                MyButton{
                    isGlow : true
                    setIcon: isGlow ? "../icons/light/Car_Icon.svg" : "../icons/Car_icon.svg"
                    onClicked: isGlow = !isGlow
                }

                MyButton{
                    setIcon: isGlow ? "../icons/light/eva_phone-call-fill.svg" :  "../icons/eva_phone-call-fill.svg"
                    onClicked: isGlow = !isGlow
                }
                MyButton{
                    setIcon: isGlow ? "../icons/light/clarity_settings-solid.svg" :  "../icons/clarity_settings-solid.svg"
                    onClicked: isGlow = !isGlow
                }
            }
        }


        SideGauge {
            id:leftGauge
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: parent.width / 11
            }
            property bool accelerating
            width: 400
            height: 400
            value: backend.speed
            maximumValue: 255
            Component.onCompleted: forceActiveFocus()
            Behavior on value { NumberAnimation { duration: 1000 }}

            Keys.onSpacePressed: accelerating = true
            Keys.onReturnPressed: rightGauge.accelerating = true
            Keys.onReleased: function(event) {
                if (event.key === Qt.Key_Space) {
                    accelerating = false;
                    event.accepted = true;
                }else if(event.key === Qt.Key_Return){
                    rightGauge.accelerating = false;
                    event.accepted = true;
                }
            }
        }
        
        Item {
            id: leftBorder
            width: leftGauge.width * 0.5
            height: leftGauge.height * 1.1
            anchors.left: leftGauge.left
            anchors.bottom: leftGauge.bottom
            anchors.leftMargin: -70
            anchors.bottomMargin: -160

            property real level: backend.pedal

            Behavior on level {
                NumberAnimation {
                    duration: 400
                    easing.type: Easing.OutCubic
                }
            }

            Image {
                id: leftMaskImage
                anchors.fill: parent
                source: "../img/Vector 1.svg"
                fillMode: Image.PreserveAspectFit
     
                smooth: true
                mipmap: true
                visible: false
            }

            Rectangle {
                id: leftPedalBase
                anchors.fill: parent
                color: "white"
                visible: false
            }

            OpacityMask {
                id: baseMask
                anchors.fill: parent
                source: leftPedalBase
                maskSource: leftMaskImage
            }

            Item {
        id: fillContainer
        width: parent.width
        height: parent.height
        anchors.fill: parent
        visible: false
        clip: true

        Rectangle {
            id: leftPedalFill
            width: parent.width
            height: parent.height * Math.min(Math.pow(Math.max(0, Math.min(leftBorder.level / 140, 1)), 0.75) * 0.92, 1.0)
            anchors.bottom: parent.bottom
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#8aa11c" }
                GradientStop { position: 1.0; color: "#3fc7de" }
            }
        }
    }
            OpacityMask {
                anchors.fill: parent
                source: fillContainer
                maskSource: leftMaskImage
            }

        }

        Image {
            id:navigation_car
            visible: false
            anchors.centerIn: parent
            source: "../icons/Navigation.png"
        }

    Rectangle {
        id: driveModeBadge
        width: 150
        height: 40
        radius: height / 2
        color: "#0B1624"
        border.width: 1
        border.color: {
        switch (backend.driveMode) {
        case "ECO":
            return "#7CFC00"
        case "COMFORT":
            return "#D8DDE6"
        case "SPORT":
            return "#FF6A3D"
        case "SNOW":
            return "#7FDBFF"
        default:
            return "#B8FF01"
        }
    }
    

    anchors.horizontalCenter: speedLimit.horizontalCenter
    anchors.bottom: speedLimit.top
    anchors.bottomMargin: 12

    Label {
        anchors.centerIn: parent
        text: backend.driveMode ? backend.driveMode : "ECO"
        color: driveModeBadge.border.color
        font.pixelSize: 18
        font.family: "Inter"
        font.bold: true
        font.capitalization: Font.AllUppercase
    }
}

        RowLayout{
    id:speedLimit
    spacing: 20
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 26.50 + 65

    Label{
        text: "P"
        font.pixelSize: 32
        font.family: "Inter"
        font.bold: Font.Normal
        font.capitalization: Font.AllUppercase
        opacity: backend.gear === "P" ? 1.0 : 0.2
        color: "#FFFFFF"
    }

    Label{
        text: "R"
        font.pixelSize: 32
        font.family: "Inter"
        font.bold: Font.Normal
        font.capitalization: Font.AllUppercase
        opacity: backend.gear === "R" ? 1.0 : 0.2
        color: "#FFFFFF"
    }

    Label{
        text: "N"
        font.pixelSize: 32
        font.family: "Inter"
        font.bold: Font.Normal
        font.capitalization: Font.AllUppercase
        opacity: backend.gear === "N" ? 1.0 : 0.2
        color: "#FFFFFF"
    }

    Label{
        text: "D"
        font.pixelSize: 32
        font.family: "Inter"
        font.bold: Font.Normal
        font.capitalization: Font.AllUppercase
        opacity: backend.gear === "D" ? 1.0 : 0.2
        color: "#FFFFFF"
    }
}

        Image {
            anchors{
                bottom: car.top
                bottomMargin: 60
                horizontalCenter:car.horizontalCenter
            }
            source: "../img/Model 3.png"
        }

        Image {
            anchors{
                bottom: car.top
                bottomMargin: -60
                horizontalCenter:car.horizontalCenter
            }
            source: "../icons/Headlights.svg"
        }

        Image {
            id:car
            anchors{
                bottom: speedLimit.top
                bottomMargin: 70
                horizontalCenter:speedLimit.horizontalCenter
            }
            source: "../icons/Car.svg"
        }

        // IMGonline.com.ua  ==> Compress Image With


        /*
          Left Road
        */

        Image {
            id: leftRoad
            width: 127
            height: 397
            anchors{
                left: speedLimit.left
                leftMargin: 100
                bottom: parent.bottom
                bottomMargin: 26.50 + 50
            }

            source: "../icons/Vector 2.svg"
        }

        RowLayout{
            spacing: 20

            anchors{
                left: parent.left
                leftMargin: 250
                bottom: parent.bottom
                bottomMargin: 26.50 + 65
            }

            RowLayout{
                spacing: 1
                Layout.topMargin: 10
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 31.25 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 62.5 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 93.75 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 125.25 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 156.5 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 187.75 ? leftGauge.speedColor : "#01E6DC"
                }
                Rectangle{
                    width: 20
                    height: 15
                    color: leftGauge.value.toFixed(0) > 219 ? leftGauge.speedColor : "#01E6DC"
                }
            }

            Label{
                text: (leftGauge.value / 1.609).toFixed(0) + " MPH"
                font.pixelSize: 32
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                color: "#FFFFFF"
            }
        }

        /*
          Right Road
        */

        Image {
            id: rightRoad
            width: 127
            height: 397
            anchors{
                right: speedLimit.right
                rightMargin: 100
                bottom: parent.bottom
                bottomMargin: 26.50 + 50
            }

            source: "../icons/Vector 1.svg"
        }


        SideGauge {
            id:rightGauge
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: parent.width /11
            }
            property bool accelerating
            width: 400
            height: 400
            value: backend.rpm
            unitText: "RPM"
            maximumValue: 8000
            Behavior on value { NumberAnimation { duration: 1000 }}
        }

        Item {
            id: rightBorder
            width: rightGauge.width * 0.5
            height: rightGauge.height * 1.1
            anchors.right: rightGauge.right
            anchors.bottom: rightGauge.bottom
            anchors.rightMargin: -70
            anchors.bottomMargin: -160

            property real level: backend.brake

            Behavior on level {
            NumberAnimation {
                duration: 400
                easing.type: Easing.OutCubic
                }
            }

            Image {
                id: rightMaskImage
                anchors.fill: parent
                source: "../img/Vector 1.svg"
                fillMode: Image.PreserveAspectFit
                mirror: true
                smooth: true
                mipmap: true
                visible: false
            }

            Rectangle {
                id: rightBrakeBase
                anchors.fill: parent
                color: "white"
                visible: false
            }

            OpacityMask {
                anchors.fill: parent
                source: rightBrakeBase
                maskSource: rightMaskImage
            }

            Item {
                id: rightFillContainer
                anchors.fill: parent
                clip: true
                visible: false

                Rectangle {
                    id: rightBrakeFill
                    width: parent.width
                    height: parent.height * Math.min(Math.pow(Math.max(0, Math.min(rightBorder.level / 140, 1)), 0.75) * 0.92, 1.0)
                    anchors.bottom: parent.bottom
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#8aa11c" }
                        GradientStop { position: 1.0; color: "#3fc7de" }
                    }
                }
            }

            OpacityMask {
                anchors.fill: parent
                source: rightFillContainer
                maskSource: rightMaskImage
            }
        }
    } 
}