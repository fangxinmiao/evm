Rectangle {
    id: root
    x: 0
    y: 0
    width: 800
    height: 600

    Image{
        source:'images_login/planet.bin'
    }

    Keyboard{
        id: keyboard
        width: 800
        height: 300
        visible:true
        ta: null
    }

    Rectangle {
        id: user
        x: 300
        y: 200
        width: 200
        height: 36
        radius: 10
        opacity: 0.3
        visible: false

        style: Style{
            opacity:0
        }

        Image{
            x: 5
            source:'images_login/user.bin'
        }

        TextArea { 
            x: 40
            y: 8
            width: 160
            height: 25
            text:''
            placeholder: "Username"

            style: Style{
                opacity:0
                border_opacity:0
            }

            onClicked:{
                keyboard.ta = this;
            }
        }
    }

    Rectangle {
        id: pwd
        x: 300
        y: 250
        width: 200
        height: 36
        radius: 10
        opacity: 0.3
        visible: false

        style: Style{
            opacity:0
        }

        Image{
            x: 5
            source:'images_login/password.bin'
        }


        TextArea { 
            x: 40
            y: 8
            width: 160
            height: 25
            text:''
            placeholder: "Password"
            pwdMode: true
            
            style: Style{
                opacity:0
                border_opacity:0
            }

            onClicked:{
                keyboard.ta = this;
            }
        }
    }


    x_pos: 0
    is_pressed: false

    Button {
        x: 720; y: 30; width: 40; height: 40; opacity: 0.2
        pressColor: 32217

        

        timer_id1: 0
        timer_id2: 0

        style: Style{
            opacity:0
            border_opacity:0
        }

        function animation(){
            if( parent.x_pos >= 300 ){
                clearInterval(timer_id1);
            }
            user.x = parent.x_pos;
            pwd.x = parent.x_pos;
            parent.x_pos = parent.x_pos + 10;
        }

        onClicked:{
            
            if( parent.is_pressed ){
                parent.is_pressed = false;
                user.visible = true;
                pwd.visible = true;
                keyboard.visible = true;
                clearInterval(timer_id1);
            }
            else{
                parent.x_pos = 0;
                timer_id1 = setInterval(animation, 5);
                parent.is_pressed = true;

                user.x = parent.x_pos;
                pwd.x = parent.x_pos;
                user.visible = false;
                pwd.visible = false;
                keyboard.visible = false;
            }
        }

        Image{
            source:'images_login/keyboard.bin'
        }
    }
}