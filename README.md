### QT 

This is a QT learn project.

GUI 事件循环
Qt 跨平台性是指 Qt 可以在多种操作系统平台上运行，包括 Windows、Linux、Mac OS X、Android、iOS 等。
Qt 模块化设计 核心模块：core <事件循环，数据结构，对象间通信，反射>、 gui <比较底层的图形用户界面模块>、 widgets <用c++代码写的组件，性能优秀，嵌入式设备>、qml、 quick

```bash
(base) root@davinci-mini:~# qmake -v
QMake version 3.1
Using Qt version 5.15.3 in /usr/lib/aarch64-linux-gnu
(base) root@davinci-mini:~# qtcreator
```

#### 0. QDbug

QDbug 是 Qt 框架提供的一个调试工具，用于在程序运行时输出调试信息。
qDebug()的使用：
```c++
#include <QDebug>
qDebug() << "Hello";
```

#### 1. 几何相关的数据结构

坐标系都是以左上角为原点，向右为x轴正方向，向下为y轴正方向。点坐标(x,y)表示的是相对于左上角的坐标。
```c++
QPoint p1(10, 20); // 点坐标(10, 20)
QPoint p2(30, 40); // 点坐标(30, 40)
QLine l1(p1, p2); // 直线l1的起点为p1，终点为p2
QRect r1(p1, p2); // 矩形r1的左上角点为p1，右下角点为p2，大小为21x21，
QRect r2(10, 20, 30, 40); // 矩形r2的左上角点为(10, 20)，宽为30，高为40
```

#### 2. QString

QString是Qt提供的字符串类，可以用来存储和操作文本数据。QChar 是 QString 的基本元素，可以用来表示单个字符，占用两个字节，即16bit。

```c++
char str[]="Hello，世界"; // 字符串数组
QString qstr = QString::fromUtf8(str); // 从char数组转换为QString
QLabel *label = new QLabel(qstr); // 在界面上显示qstr，使用QLabel调试而不是QDebug的原因是QDbug输出中文会乱码
```

内存设计：<QString本质上是一个顺序容器>
隐式共享：当多个对象指向相同的内存时，只会分配一次内存，而不会为每个对象分配内存，(写时复制)。

```c++
QString str1;
QString str2("Hello");
QString str3(3,str2[0]); // 复制str2的第一个字符3次
str1 = str2; // 隐式共享，只分配一次内存
str2 = "World"; // 不会影响str1的值
qDebug() << str1 << str2;
qDebug() << str3;

std::string ststr = "nihao";
QString str4 = QString::fromStdString(ststr);// StdString转换为QString
qDebug() << str4;

QString str5 = "hello %1 %2";
qDebug() << str5.arg("world").arg(1234,4,16,QChar('0')); // 格式化字符串, 4表示宽度为4，16表示进制为16，QChar('0')表示填充字符为0
```

```
09:48:42: Debugging starts
"Hello" "World"
"HHH"
"nihao"
"hello world 04d2"
09:48:47: Debugging has finished
```

增加和删除：
append, prepend, operator+=, insert
remove, replace, 

查询：
已知位置，找元素：at, operator[], back, front
已知元素，找位置：indexOf, lastIndexOf, contains, count

#### 3. QList & QVector

QList是Qt提供的列表类，支持下标访问，可以存储不同类型的元素。
```c++
QList<QString> list ={"one","two","3"};
list.insert(0,"zero");//时间复杂度O(n)，少使用
list.append("4");
list.prepend("-1");
qDebug() << list;
```
```
10:31:33: Debugging starts
("-1", "zero", "one", "two", "3", "4")
10:31:37: Debugging has finished
```