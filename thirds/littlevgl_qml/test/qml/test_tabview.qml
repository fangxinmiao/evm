Rectangle {
    id: rect0
    x: 50
    y: 50
    width: 600
    height: 600
    color: 'red'
    radius: 10

    TabView {

        Tab {
            title: "Red"

            
            Rectangle {
                id: rect1
                x: 50
                y: 50
                width: 500
                height: 300
                color: 'red'
                radius: 10

                x_pos: 100
                y_pos: 50

                Rectangle {
                    x: parent.x_pos
                    y: parent.y_pos
                    width: 50
                    height: 50
                    color: 1000
                    radius: 10
                }

                Button{
                    x: 20
                    y: 220
                    width: 80
                    height: 30
                    color: 'Yellow'
                    pressColor: 'blue'
                    releaseColor: 'yellow'
                    
                    onClicked: 
                    {
                        print(rect1);
                        rect1.x_pos = rect1.x_pos - 10;
                    }

                    Text{
                        text: 'Left'
                    }
                }

                Button{
                    x: 210
                    y: 220
                    width: 80
                    height: 30
                    color: 'Yellow'
                    pressColor: 'blue'
                    releaseColor: 'yellow'

                    onClicked: {
                    
                        parent.x_pos = parent.x_pos + 10;
                    }

                    Text{
                        text: 'Right'
                    }
                }

                Button{
                    x: 120
                    y: 200
                    width: 80
                    height: 30
                    color: 'Yellow'
                    pressColor: 'blue'
                    releaseColor: 'yellow'

                    onClicked: {
                        parent.y_pos = parent.y_pos - 10;
                    }

                    Text{
                        text: 'Up'
                    }
                }

                Button{
                    x: 120
                    y: 250
                    width: 80
                    height: 30
                    color: 'Yellow'
                    pressColor: 'blue'
                    releaseColor: 'yellow'

                    onClicked: {
                        print('down');
                        parent.y_pos = parent.y_pos + 10;
                    }

                    Text{
                        text: 'Down'
                    }
                }

                Slider{
                    x: 120
                    y: 50
                    width: 100
                    height: 30
                    color: 'Yellow'
                    value: 0
                    min: 0
                    max: 200
                    onValueChanged: {
                        parent.width = 200 + value;
                        parent.height = 200 + value;
                    }
                }

                Image{
                source:'P:app.bin'
                }

            }
        }

        Tab {
            title: "Blue"
            TextArea { 
                width: 100
                height: 150
                text: "hello"
                onValueChanged:{
                    print(text);
                }

                Keyboard{
                    id: keyboard
                    width: 400
                    height: 200
                    visible:true
                }
            }

            Button{
                x:500
                y:400
                width: 60
                height: 30
                color: 'Yellow'
                pressColor: 'blue'
                releaseColor: 'yellow'

                onClicked:{
                    if(keyboard.visible)
                        keyboard.visible = false;
                    else
                        keyboard.visible = true;
                }

                Text{
                    text: 'Input'
                }
            }

        }

        Tab {
            title: "Green"
            ListView {
                id: listview
                x: 0
                width: 100
                // items: [{"icon": "green","text": "green"}]
                items: ["red", "green", "blue"]
            }

            Roller {
                x: listview.width + 10
                items: ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"]
                currentIndex: 0
                visibleItemsCount: 5
            }
        }
    }
}