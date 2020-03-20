Rectangle {
    id: root
    x: 10
    y: 10
    width: 780
    height: 580
    color: 'darkblue'
    radius: 10

    spacing: 10

    rectWidth: 180
    rectHeight: 180

    timer_id1: 0
    count : 0

    start_x: (root.width - root.rectWidth *3 - 2 * root.spacing) / 2
    start_y: root.spacing

    style:Style{
        main_color: 'red'
        grad_color: 'darkBlue'
    }

    onCompleted:{
        print('hello');
    }

    StyleBtnRelease{
        main_color: 'magenta'
        grad_color: 'darkBlue'
    }

    Button {
        id: rect1
        x: root.start_x
        y: root.start_y
        width: root.rectWidth
        height: root.rectHeight

        Text {
            text: "js"
        }
    }

    Button {
        id: rect2
        x: start_x + root.rectWidth + root.spacing
        y: root.spacing
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "python"
        }  
    }

    Button {
        id: rect3
        x: start_x + (root.rectWidth + root.spacing) * 2
        y: root.spacing
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "lua"
        }      
    }


    Button {
        id: rect4
        x: start_x
        y: start_y + root.rectHeight + root.spacing
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "json"
            textColor: "darkblue"
        } 
    }

    Button {
        id: rect5
        x: start_x + root.rectWidth + root.spacing
        y: start_y + root.rectHeight + root.spacing
        width: root.rectWidth
        height: root.rectHeight

        style:Style{
            main_color: 'red'
        }

        Text {
            text: "EVM"
            textColor: "darkblue"
        }

        function myswitch(r1, r2) {
            r1.x = r2.x;
            r1.y = r2.y;
        }

        function animation(){
            var x = rect1.x;
            var y = rect1.y;
            
            myswitch(rect1, rect2);
            myswitch(rect2, rect3);
            myswitch(rect3, rect6);
            myswitch(rect6, rect9);
            myswitch(rect9, rect8);
            myswitch(rect8, rect7);
            myswitch(rect7, rect4);
            rect4.x = x;
            rect4.y = y;
        }

        timer_id:0

        onCompleted: {
            rect5.timer_id = setInterval(rect5.animation, 500);
        }
    }

    Button {
        id: rect6
        x: start_x + (root.rectWidth + root.spacing) * 2
        y: start_y + root.rectHeight + root.spacing
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "xml"
        }   
    }

    Button {
        id: rect7
        x: start_x
        y: start_y + (root.rectHeight + root.spacing) * 2
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "QML"
        }      
    }

    Button {
        id: rect8
        x: start_x + root.rectWidth + root.spacing
        y: start_y + (root.rectHeight + root.spacing) * 2
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: " IOT SDK "
        }  
    }

    Button {
        id: rect9
        x: start_x + (root.rectWidth + root.spacing) * 2
        y: start_y + (root.rectHeight + root.spacing) * 2
        width: root.rectWidth
        height: root.rectHeight
        Text {
            text: "More..."
        }    
    }
}