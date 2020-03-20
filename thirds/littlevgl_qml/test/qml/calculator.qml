Rectangle {
    id: rect
    x: 0
    y: 0
    width: 800
    height: 600
    color: 'gray'
    radius: 10    

    result: ''

    TextArea{
        id: display
        x:50; y:50; width:480; height:50;
        radius:2;
        oneLine:true
        textAlign:'right'
        text: '0'
    }

    Container{
        x: 410; y:100;
        layout: 'grid'
        width: 120
        height:300
        
        Button{
            Text{
                text: '+';
            }
        }

        Button{
            Text{
                text: '-';
            }
        }

        Button{
            Text{
                text: '*';
            }
        }

        Button{
            Text{
                text: '/';
            }
        }
    }

    Container{
        x: 50; y:100;
        layout: 'grid'
        width: 350
        height:300
        opacity: 0.3

        Button{
            color:'blue'
            Text{
                text: '7';
            }
            onClicked:{
                rect.result = rect.result + '7';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '8';
            }
            onClicked:{
                rect.result = rect.result + '8';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '9';
            }
            onClicked:{
                rect.result = rect.result + '9';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '4';
            }
            onClicked:{
                rect.result = rect.result + '4';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '5';
            }
            onClicked:{
                rect.result = rect.result + '5';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '6';
            }
            onClicked:{
                rect.result = rect.result + '6';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '1';
            }
            onClicked:{
                rect.result = rect.result + '1';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '2';
            }
            onClicked:{
                rect.result = rect.result + '2';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '3';
            }
            onClicked:{
                rect.result = rect.result + '3';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '0';
            }
            onClicked:{
                rect.result = rect.result + '0';
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '.';
            }
            onClicked:{
                rect.result = rect.result + '.' ;
                display.text = rect.result;
            }
        }

        Button{
            Text{
                text: '+/-';
            }
        }
    }
}