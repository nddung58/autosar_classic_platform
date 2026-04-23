import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {
    id: gauge
    width: 300
    height: 300

    property real minimumValue: 0
    property real maximumValue: 250
    property real value: 0
    property string speedColor: "yellow"
    property string unitText: "km/h"

    property real outerRadius: Math.min(width, height) / 2
    property real arcAngle: 180
    property real arcRadius: 90

    property real minimumValueAngle: -155
    property real maximumValueAngle: 155
    property real labelStepSize: 2

    function clamp(v, minV, maxV) {
        return Math.max(minV, Math.min(maxV, v))
    }

    function valueToAngle(v) {
        var t = (clamp(v, minimumValue, maximumValue) - minimumValue) / (maximumValue - minimumValue)
        return minimumValueAngle + t * (maximumValueAngle - minimumValueAngle)
    }

    function degreesToRadians(degrees) {
        return degrees * (Math.PI / 180)
    }

    function angleForPaint(v) {
        return valueToAngle(v) - 90
    }

    Item {
        id: backgroundLayer
        anchors.fill: parent

        Image {
            sourceSize: Qt.size(16, 17)
            source: "../img/maxLimit.svg"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.top
            anchors.bottomMargin: -outerRadius * 0.01
        }

        Canvas {
            id: thinArc
            anchors.fill: parent

            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()

                var startAngle = angleForPaint(gauge.minimumValue)
                var endAngle = angleForPaint(gauge.maximumValue)

                var gradient = ctx.createLinearGradient(0, 0, gauge.outerRadius * 2, 0)
                gradient.addColorStop(0, "#B8FF01")
                gradient.addColorStop(1, "#B8FF01")

                ctx.beginPath()
                ctx.lineWidth = 1.5
                ctx.strokeStyle = gradient
                ctx.arc(gauge.outerRadius,
                        gauge.outerRadius,
                        gauge.outerRadius - 57,
                        degreesToRadians(startAngle),
                        degreesToRadians(endAngle))
                ctx.stroke()
            }
        }

        Canvas {
            id: baseArc
            anchors.fill: parent

            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()

                var startAngle = angleForPaint(gauge.minimumValue)
                var endAngle = angleForPaint(gauge.maximumValue)

                var gradient = ctx.createLinearGradient(0, 0, gauge.outerRadius * 2, 0)
                gradient.addColorStop(0, "#163546")
                gradient.addColorStop(1, "#163546")

                ctx.beginPath()
                ctx.lineWidth = gauge.outerRadius * 0.15
                ctx.strokeStyle = gradient
                ctx.arc(gauge.outerRadius,
                        gauge.outerRadius,
                        gauge.outerRadius - 75,
                        degreesToRadians(startAngle),
                        degreesToRadians(endAngle))
                ctx.stroke()
            }
        }

        Canvas {
            id: valueArc
            anchors.fill: parent

            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()

                var startAngle = angleForPaint(gauge.minimumValue)
                var endAngle = angleForPaint(gauge.value)

                var gradient = ctx.createLinearGradient(0, 0, gauge.outerRadius * 2, 0)
                gradient.addColorStop(0.00, "#6369FF")
                gradient.addColorStop(0.33, "#63FFFF")
                gradient.addColorStop(0.66, "#FFFF00")
                gradient.addColorStop(1.00, "#FF0000")

                ctx.beginPath()
                ctx.lineWidth = gauge.outerRadius * 0.15
                ctx.strokeStyle = gradient
                ctx.arc(gauge.outerRadius,
                        gauge.outerRadius,
                        gauge.outerRadius - 75,
                        degreesToRadians(startAngle),
                        degreesToRadians(endAngle))
                ctx.stroke()
            }
        }

        onWidthChanged: {
            thinArc.requestPaint()
            baseArc.requestPaint()
            valueArc.requestPaint()
        }
        onHeightChanged: {
            thinArc.requestPaint()
            baseArc.requestPaint()
            valueArc.requestPaint()
        }
    }

    Repeater {
        model: Math.floor((maximumValue - minimumValue) / labelStepSize) + 1

        delegate: Rectangle {
            required property int index

            width: outerRadius * 0.008
            height: outerRadius * 0.05
            radius: width / 2
            antialiasing: true
            smooth: true

            property real tickValue: minimumValue + index * labelStepSize
            property real tickAngle: valueToAngle(tickValue)

            color: tickValue <= gauge.value ? "white" : "darkGray"

            anchors.centerIn: parent

            transform: [
                Rotation {
                    origin.x: 0
                    origin.y: outerRadius - outerRadius * 0.225
                    angle: tickAngle
                },
                Translate {
                    x: 0
                    y: -(outerRadius - outerRadius * 0.25)
                }
            ]
        }
    }

    Item {
    id: needleContainer
    width: outerRadius * 1.4
    height: outerRadius * 1.4
    anchors.centerIn: parent
    rotation: valueToAngle(gauge.value)
    transformOrigin: Item.Center
    z: 20

    Behavior on rotation {
        NumberAnimation {
            duration: 120
            easing.type: Easing.OutCubic
        }
    }

    Item {
        id: needlePivot
        width: outerRadius * 0.08
        height: outerRadius * 0.72
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -outerRadius * 0.8  

        Image {
            id: needle
            source: "../img/Rectangle 4.svg"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: outerRadius * 0.025
            height: outerRadius * 0.36
            fillMode: Image.PreserveAspectFit
            asynchronous: true
            antialiasing: true
            smooth: true
        }

        Glow {
            anchors.fill: needle
            radius: 3
            samples: 12
            color: "white"
            source: needle
        }
    }
}

    Item {
        id: foreground
        anchors.fill: parent

        Image {
            anchors.centerIn: parent
            source: "../img/Ellipse 1.svg"

            Image {
                sourceSize: Qt.size(203, 203)
                anchors.centerIn: parent
                source: "../img/Subtract.svg"

                Image {
                    z: 2
                    sourceSize: Qt.size(147, 147)
                    anchors.centerIn: parent
                    source: "../img/Ellipse 6.svg"

                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 0

                        Label {
                            text: Number(gauge.value).toFixed(0)
                            font.pixelSize: 65
                            font.family: "Inter"
                            color: "#FFFFFF"
                            font.weight: Font.DemiBold
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Label {
                            text: gauge.unitText
                            font.pixelSize: 18
                            font.family: "Inter"
                            color: "#FFFFFF"
                            opacity: 0.4
                            font.weight: Font.Normal
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }
    }

    onValueChanged: valueArc.requestPaint()
    Component.onCompleted: {
        thinArc.requestPaint()
        baseArc.requestPaint()
        valueArc.requestPaint()
    }
}