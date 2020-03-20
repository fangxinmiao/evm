Rectangle {
    id: root
    x: 0
    y: 0
    width: 800
    height: 600

    style:Style{
        main_color: 'lightblue'
        grad_color: 'green'
    }

    ScrollArea{
        x: 0; y:0;
        width: 800
        height:600

        Chart {
            type: "Line"
            lineWidth: 5
            lineCounts: [0, 0]
            ChartSeries {
                data: [0,25,0,50,0,75,0,100,0]
                color: "red"
            }

            ChartSeries {
                data: [25,0,50,0,75,0,100,0]
                color: "blue"
            }
        }

        Chart {
            type: "Point"
            lineWidth: 10
            yRange: [0, 200]
            lineCounts: [1, 1]
            ChartSeries {
                data: [10,15,20,25,30,50,80,100,120]
                color: "red"
            }
        }

        Chart {
            type: "Bar"
            yRange: [0, 200]
            ChartSeries {
                data: [10,15,20,25,30,50,80,100,120]
                color: "green"
            }
        }

        Chart {
            type: "Area"
            ChartSeries {
                data: [0,25,0,50,0,75,0,100,0]
                color: "red"
            }
        }

        Chart {
            type: "VLine"
            ChartSeries {
                data: [0,25,0,50,0,75,0,100,0]
                color: "red"
            }
        }
    }
}