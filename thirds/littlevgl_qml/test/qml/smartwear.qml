Rectangle {
    id: rect
    x: 0
    y: 0
    width: 800
    height: 600

    style:Style{
        main_color: 'lightblue'
        grad_color: 'white'
    }

    TileView {
        id: tileView
        width: 240
        height: 240
        pageIds: [[0,0], [0,1], [0,2],[1,0], [1,1], [1,2], [1,3], [2,0], [2,1]]

        currentId: [0, 0]

        tw: 239
        th: 239

        Tile {
            id: tile1
            x: 0
            y: 0
            width: tw
            height: tw

            style:Style{
                main_color: 'red'
                grad_color: 'red'
            }

            Button {

                Text {
                    text: "0, 0"
                }

                onClicked: {
                    tileView.currentId = [1, 0]
                }
            }
        }

        Tile {
            x: 0
            y: -tw
            width: tw
            height: tw
            Button {

                Text {
                    text: "0, 1"
                }
            }
        }

        Tile {
            x: 0
            y: -480
            width: tw
            height: tw
            Button {

                Text {
                    text: "0, 2"
                }
            }
        }

        Tile {
            x: -tw
            y: 0
            width: tw
            height: tw
            Button {

                Text {
                    text: "1, 0"
                }
            }
        }

        Tile {

            x: -tw
            y: -tw

            width: tw
            height: tw

            Button {

                Text {
                    text: "1, 1"
                }
            }
        }

        Tile {
            x: -tw
            y: -480

            width: tw
            height: tw

            Button {

                Text {
                    text: "1, 2"
                }
            }
        }

        Tile {

            x: -tw
            y: -720

            width: tw
            height: tw

            Button {

                Text {
                    text: "1, 3"
                }
            }
        }

        Tile {
            x: -tw * 2
            y: 0

            width: tw
            height: tw

            Button {

                Text {
                    text: "2, 0"
                }
            }
        }

        Tile {
            x: -tw * 2
            y: -tw

            width: tw
            height: tw

            Button {

                Text {
                    text: "2, 1"
                }
            }

            onCompleted: {
                tileView.currentId = [2, 1]
            }
        }
    }
}