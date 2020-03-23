Rectangle {
    id: rect
    x: 0
    y: 0
    width: 240
    height: 320

    style:Style{
        main_color: 'lightblue'
        grad_color: 'lightblue'
    }

    Rectangle{

        x: 60
        y: 100
        width: 160
        height: 160

        style:Style{
            main_color: 'lightblue'
            grad_color: 'lightblue'
        }

        Image{
            source: 'watch.bin'
        }
        
        Gauge{
            id: g1
            x:10
            y:10
            width:100
            height:100

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
            x:20
            y:20
            width:80
            height:80

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
            x:30
            y:30
            width:60
            height:60

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
