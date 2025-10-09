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
/*增加，访问，统计元素
QList<QString> list ={"one","two","3"};
list.insert(0,"zero");//时间复杂度O(n)，少使用
list.append("4");
list.prepend("-1");
qDebug() << list;
qDebug() << list[0];
qDebug() << "size" <<list.size();
qDebug() << "count()" << list.count();
qDebug() << "count(-1)" << list.count("-1");
*/
QList<int> newList={1,3,5,4,6,3,9,8};
newList.removeFirst();
newList.removeLast();
newList.removeAll(3);
newList.removeAt(0);
qDebug() << newList;
```
```
10:42:53: Debugging starts
("-1", "zero", "one", "two", "3", "4")
"-1"
size 6
count() 6
count(-1) 1
10:42:58: Debugging has finished

10:45:41: Debugging starts
(4, 6, 9)
10:45:44: Debugging has finished
```
```c++
/*
QStack<int> stack;//先进后出, from QVector
stack.push(1);
stack.push(2);
stack.push(3);
stack.push(4);
stack.pop();
qDebug() << stack;
*/
QQueue<int> queue;//先进先出, from QList
queue.enqueue(1);
queue.enqueue(2);
queue.enqueue(3);
queue.enqueue(4);
queue.enqueue(5);
queue.dequeue();
qDebug() << queue;
```
```
12:11:42: Debugging starts
QVector(1, 2, 3)
12:11:51: Debugging has finished

13:43:54: Debugging starts
(2, 3, 4, 5)
13:44:58: Debugging has finished
```

#### 4. 关联容器

QMap, QMultiMap, QHash, QMultiHash

（键→值，K = Key，T = Value）

| 类名            | 底层结构 | 键是否唯一 | 是否按键排序 | 典型查找复杂度 |
|-----------------|----------|------------|--------------|----------------|
| QMap<K,T>       | 跳表     | 唯一       | 升序         | O(log n)       |
| QMultiMap<K,T>  | 跳表     | **可重复** | 升序         | O(log n)       |
| QHash<K,T>      | 哈希表   | 唯一       | **无序**     | 平均 O(1)      |
| QMultiHash<K,T> | 哈希表   | **可重复** | 无序         | 平均 O(1)      |

------------------------------------------------

1. QMap —— “**字典**”  
   想象一本《新华字典》：  
   - 汉字（Key）按拼音字母顺序排好  
   - 每页只有一个汉字，不重复  
   - 查“Qt”直接翻 Q 字母区，二分定位，O(log n)  

   代码 
   ```cpp
   QMap<QString,int> price;
   price["apple"]  = 5;   // 插入或覆盖
   price["banana"] = 3;
   int a = price["apple"]; // 5
   ```

2. QMultiMap —— “**允许同姓的人住同一栋楼**”  
   还是字典，但允许**同一个拼音**对应**多条解释**。  
   查“王”姓住户，会拿到一串结果。  

   代码  
   ```cpp
   QMultiMap<QString,QString> phone;
   phone.insert("Tom", "111");
   phone.insert("Tom", "222"); // 不会覆盖，两条都存
   QList<QString> l = phone.values("Tom"); // ("111","222")
   ```

3. QHash —— “**超市储物柜**”  
   柜子编号 = hash(钥匙牌)，不排序，但**一插即取**，最快。  
   键唯一：一个牌只能开一个柜。  

   代码
   ```cpp
   QHash<int,QString> locker;
   locker[10086] = "雨伞";
   QString item = locker.value(10086); // O(1)
   ```

4. QMultiHash —— “**一个钥匙牌可开多个柜**”  
   你交了 10 块钱，服务员给你**同一个编号**的 3 把钥匙，  
   可以打开 3 个相邻柜子。  

   代码 
   ```cpp
   QMultiHash<QString,int> score;
   score.insert("Bob", 95);
   score.insert("Bob", 87);     // Bob 现在有两条成绩
   QList<int> all = score.values("Bob"); // (95,87)
   ```

   如何设计一个容器，使其支持范围for？<range-based for>
   1. 实现begin()和end()方法，返回迭代器
   2. 迭代器重载operator !=() , operator ++() , operator*()，使得可以用*it来访问元素

c++ 11 的新特性有哪些？
1. 移动语义
2. 智能指针
3. range-based for

```cpp
QMap<int,int> myMap={{1,3},{5,3},{6,6},{7,9}};
for(QMap<int,int>::iterator it=myMap.begin();it!=myMap.end();++it){
    qDebug() << it.key() << ": " << it.value();
}
qDebug() << "----------";
for(auto item:myMap){//范围for，不能访问key
    qDebug() << item;
}
```
```
14:27:13: Debugging starts
1 :  3
5 :  3
6 :  6
7 :  9
----------
3
3
6
9
14:27:38: Debugging has finished
```
#### 5. 信号和槽

| Qt 概念      | 现实类比                          |
| ---------- | ----------------------------- |
| 信号（Signal） | 家里的“门铃按钮”——只负责“叮”一声，不知道谁会响应。  |
| 槽（Slot）    | 门铃响后去开门的“人”——只负责执行动作，不知道谁按的铃。 |
| connect    | 电工把按钮和门铃的线路接起来——建立连接。         |
