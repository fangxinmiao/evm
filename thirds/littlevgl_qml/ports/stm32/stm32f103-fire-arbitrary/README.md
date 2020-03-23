Littlevgl QML
=========================
###  1. 什么是QML

QML是一种描述性的脚本语言，文件格式以.qml结尾。
语法格式融合了CSS、JavaScript。通过QML语言可以快速构建UI界面，开发者在不需要掌握大量设计技巧的前提下也能很容易的掌握QML技术。


### 2. 来源

QML是Qt推出的Qt Quick技术的一部分，是一种新增的简便易学的语言。
QML是一种陈述性语言，用来描述一个程序的用户界面：无论是什么样子，以及它如何表现。
在QML，一个用户界面被指定为具有属性的对象树。 这使得Qt更加便于很少或没有编程经验的人使用。


### 3. EVM的QML语言

QML作为QT主打的面向UI开发的语言，其强大的描述能力和调用JavaScript的功能，为UI开发带来了全新的设计理念。尤其是QML属性绑定式编程，可以快速的描述UI的行为和动效。然而QML只能运行在QT图形引擎中，其体积庞大、性能不足的问题一直为人诟病，更不用说能让QML在单片机上运行了。
但EVM引擎打破了这种限制，EVM引擎可以完整运行QML语法，同时通过虚拟机扩展接口，可以让QML语言服务于各种底层图形引擎，例如GuiLite、Littlevgl、AWTK等等。同时EVM引擎能够让多种语言混合运行，所以完美解决了QML中调用JavaScript的功能，并且还打破了QT中的QML无法调用JavaScript库的问题。


### 4.  目录说明

| 文件      |    说明|
| :-------- | --------:| 
| **lib**|    开发库，静态libqml库及头文件|
| **lib/inlcude/evm.h**|    evm虚拟机接口头文件|
| **lib/include/qml_module.h**| qml接口头文件|
| **lib/x86_linux**|    Linux平台静态libqml库|
| **lib/x86_win64**|    win64平台静态libqml库|
| **thirds/littevgl_qml**| littevgl_qml模块| 
| **thirds/littevgl_qml/lvgl_module**| 基于littlelvgl的qml封装| 
| **thirds/littevgl_qml/ports**| 平台适配| 
| **thirds/littevgl_qml/ports/Qt**| Qt平台适配| | 
| **test**|    语法测试代码 |
| **README.md**|   说明文档 |


#### 5.  编译构建

##### 5.1  Qt运行 littevgl_qml

+ libqml是基于 gcc 7.3.0  运行
+ 建议编译环境使用 **Qt 最新版**  http://download.qt.io/archive/qt/5.14/5.14.1/  Qt Creater打开 `evm/thirds/littlevgl_qml/ports/Qt/littlevgl_qml.pro` 直接进行编译即可

+ 自定义qml模块加载路径

	用户如果需要自定义qml路径，可以修改 `evm/thirds/littlevgl_qml/ports/Qt/evm_main.c`中的qml模块路径定义，需要保持 `modules_paths_count`和 `modules_paths`长度一致
```
int modules_paths_count = 3;
char* modules_paths[] = {
    ".",
    "./test",
    "../../../../../../test/qml",
};
```

+  程序默认启动实例 qml 文件
```
evm/test/qml/login.qml
```

### 6. Littlevgl的QML

颜色关键字：

    if( !strcmp(s, "white") ) return LV_COLOR_WHITE;
    if( !strcmp(s, "silver") ) return LV_COLOR_SILVER;
    if( !strcmp(s, "gray") ) return LV_COLOR_GRAY;
    if( !strcmp(s, "black") ) return LV_COLOR_BLACK;
    if( !strcmp(s, "red") ) return LV_COLOR_RED;
    if( !strcmp(s, "maroon") ) return LV_COLOR_MAROON;
    if( !strcmp(s, "yellow") ) return LV_COLOR_YELLOW;
    if( !strcmp(s, "olive") ) return LV_COLOR_OLIVE;
    if( !strcmp(s, "lime") ) return LV_COLOR_LIME;
    if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
    if( !strcmp(s, "cyan") ) return LV_COLOR_CYAN;
    if( !strcmp(s, "aqua") ) return LV_COLOR_AQUA;
    if( !strcmp(s, "teal") ) return LV_COLOR_TEAL;
    if( !strcmp(s, "blue") ) return LV_COLOR_BLUE;
    if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
    if( !strcmp(s, "navy") ) return LV_COLOR_NAVY;
    if( !strcmp(s, "magenta") ) return LV_COLOR_MAGENTA;
    if( !strcmp(s, "purple") ) return LV_COLOR_PURPLE;
    if( !strcmp(s, "orange") ) return LV_COLOR_ORANGE;
    
布局关键字：

    if( !strcmp(s, "off") ) return LV_LAYOUT_OFF;
    if( !strcmp(s, "center") ) return LV_LAYOUT_CENTER;
    if( !strcmp(s, "hLeft") ) return LV_LAYOUT_COL_L;
    if( !strcmp(s, "vCenter") ) return LV_LAYOUT_COL_M;
    if( !strcmp(s, "hRight") ) return LV_LAYOUT_COL_R;
    if( !strcmp(s, "top") ) return LV_LAYOUT_ROW_T;
    if( !strcmp(s, "hCenter") ) return LV_LAYOUT_ROW_M;
    if( !strcmp(s, "bottom") ) return LV_LAYOUT_ROW_B;
    if( !strcmp(s, "pretty") ) return LV_LAYOUT_PRETTY;
    if( !strcmp(s, "grid") ) return LV_LAYOUT_GRID;
    
fit关键字：

    if( !strcmp(s, "none") ) return LV_FIT_NONE;
    if( !strcmp(s, "tight") ) return LV_FIT_TIGHT;
    if( !strcmp(s, "flood") ) return LV_FIT_FLOOD;
    if( !strcmp(s, "fill") ) return LV_FIT_FILL;

对象默认属性：

    *  x，x坐标，整数
    *  y，y坐标，整数
    *  width，宽度，整数
    *  height，高度，整数
    *  color，颜色，整数或者字符串
    *  radius，弧度，整数
    *  visible，可视性，布尔
    *  opacity，透明度，小数
    

支持的对象：

    *  Rectangle，矩形对象
    *  Button，按钮
        *  pressColor，按住颜色，整数或者字符串
        *  releaseColor，释放颜色，整数或者字符串
        *  onClicked，点击事件
    *  Text，文本
        *  text，内容，字符串
    *  TabView，多页面切换
    *  Tab，tab页面
    *  ListView，列表
        *  items，列表内容，字符串数组
    *  Roller，滚动控件
        *  items，内容，字符串数组
        *  currentIndex，当前索引，整数
        *  visibleItemsCount，可视项目数量，整数
    *  Slider，滑动条
        *  value，当前值，整数
        *  min，最小值，整数
        *  max，最大值，整数
        *  onValueChanged，数值变化事件
    *  TextArea，文本输入
        *  text，内容，字符串
        *  placeholder，占位文本
        *  oneLine，单行模式，布尔值
        *  maxLength，最大长度，整数
        *  pwdMode，密码模式，布尔值
        *  onValueChanged，值变化事件
    *  Keyboard，键盘
        *  ta，设置文本输入对象，TextArea对象
    *  Image，图片
        *  source，图片源，字符串
    *  CheckBox，勾选框
        *  text，内容
        *  onClicked，点击事件
    *  Container，布局容器
        *  layout，布局，字符串
        *  fit，大小适应，字符串
        
###  7. 版权声明

Littlevgl_qml 采用 MIT Licence 协议
