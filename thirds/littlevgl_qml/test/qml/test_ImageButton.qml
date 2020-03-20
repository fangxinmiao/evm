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

        
        ImageButton {
            pressed: 'images/bin/dark/appbar.add.bin'
            released: 'images/bin/light/appbar.add.bin'
        }

        Button {

            Image {
                id: bm
                source: 'images/bin/light/appbar.add.bin'
            }

            onPressed: {
                bm.source =  'images/bin/dark/appbar.add.bin'
            }

            onReleased: {
                bm.source =  'images/bin/light/appbar.add.bin'
            }
        }


        ImageButton {
            pressed: 'images/bin/dark/appbar.acorn.bin'
            released: 'images/bin/light/appbar.acorn.bin'
        }
    }
}