Rectangle {
    id: root
    x: 0
    y: 0
    width: 800
    height: 600

    Container {
        x:0; y:0;
        width: 800
        height: root.height / 2
        layout: "grid"

        style:Style{
            main_color: 'lightblue'
            grad_color: 'white'
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 10
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 20
            style: Style{
                line_color: "red"
                line_width: 2
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 30
            style: Style{
                line_color: "red"
                line_width: 3
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 40
            style: Style{
                line_color: "red"
                line_width: 4
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 50
            style: Style{
                line_color: "red"
                line_width: 5
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 60
            style: Style{
                line_color: "red"
                line_width: 6
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 70
            style: Style{
                line_color: "red"
                line_width: 7
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 80
            style: Style{
                line_color: "red"
                line_width: 8
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 90
            style: Style{
                line_color: "green"
                line_width: 8
            }
        }

        ProgressBar {
            height: 20
            width: 100
            min: 0
            max: 100
            value: 100
            style: Style{
                line_color: "green"
                line_width: 8
            }
        }
    }

    Container {
        x:0; y:root.height / 2;
        width: 800
        height: root.height / 2
        layout: "grid"

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 10
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 20
            style: Style{
                line_color: "red"
                line_width: 2
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 30
            style: Style{
                line_color: "red"
                line_width: 3
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 40
            style: Style{
                line_color: "red"
                line_width: 4
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 50
            style: Style{
                line_color: "red"
                line_width: 5
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 60
            style: Style{
                line_color: "red"
                line_width: 6
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 70
            style: Style{
                line_color: "red"
                line_width: 7
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 80
            style: Style{
                line_color: "red"
                line_width: 8
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 90
            style: Style{
                line_color: "green"
                line_width: 8
            }
        }

        ProgressBar {
            height: 100
            width: 20
            min: 0
            max: 100
            value: 100
            style: Style{
                line_color: "green"
                line_width: 8
            }
        }
    }
}