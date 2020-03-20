Rectangle {
    id: rect
    x: 0
    y: 0
    width: 800
    height: 600

    style:Style{
        main_color: 'lightblue'
        grad_color: 'lightblue'
    }

    Rectangle{

        x: 200
        y: 100
        width: 400
        height: 400

        style:Style{
            main_color: 'lightblue'
            grad_color: 'lightblue'
        }

        Image{
            source: 'images/wear/ico_watch_background_011.bin'
        }
        
        Gauge{
            id: g1
            x:45
            y:45
            width:300
            height:300

            min:0
            max:360

            scale: [360, 0,0]

            GaugeValue{
                id:gvsec
                index:0
                value:0
            }

            function animation(){
                var date = new Date();
                var offset = 31;
                var hx = date.getHours();
                var mx = date.getMinutes();
                var sx = date.getSeconds();

                if( hx > 12) hx = hx - 12;

                if( hx <= 6 ) hx = hx * 360 / 12 + 180;
                if( hx > 6 && hx <= 12) hx = hx * 360 / 12 - 180;

                if( sx >= 30 ) sx = sx * 6 - 180;
                else sx = sx * 6 + 180;
                
                if( mx >= 30 ) mx = mx * 6 - 180;
                else mx = mx * 6 + 180;

                hx = hx + date.getMinutes() * 30 / 60;

                print(hx, mx, sx);
                

                gvhour.value = hx;
                gvmin.value = mx;
                gvsec.value = sx;
            }

            timer_id:0

            onCompleted: {
                g1.timer_id = setInterval(g1.animation, 200);
            }
        }


        Gauge{
            x:95
            y:95
            width:200
            height:200

            min:0
            max:360

            needle: ['white']

            scale: [360, 0,0]

            GaugeValue{
                id:gvmin
                index:0
                value:20
            }
        }

        Gauge{
            x:120
            y:120
            width:150
            height:150

            needle: ['yellow']

            min:0
            max:360

            scale: [360, 0,0]

            GaugeValue{
                id:gvhour
                index:0
                value:0
            }
        }
    }
}