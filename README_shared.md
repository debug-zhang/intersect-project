



# [2020 BUAA 软件工程]结对项目作业



## 4. 计算模块接口的设计与实现过程。说明你的算法的关键（不必列出源代码），以及独到之处

### 解题思路

#### 几何形状表示方法

根据题目所给定的信息，直线、射线和线段均由线上两点表示。

在求交点时，为方便计算，所有几何形状统一表示成直线，在求出交点后再判断是否满足射线、线段的限定条件。

为方便表示所有类型的直线，同时便于判断平行和求交点，采用直线的一般式方程来描述：

$$ Ax+By+C=0 $$

这里，$A,\ B,\ C$ 三个量的计算方法为：

- $A=y_2-y_1$
- $B=x_1-x_2$
- $C=x_2*y_1-x_1*y_2$

在这种情况下，两直线平行时：

$$A_1B_2=A_2B_1$$

#### 交点计算

在用直线的一般式方程来描述时，两直线交点坐标：

$$(\frac{B_1C_2-B_2C_1}{A_1B_2-A_2B_1},\ \frac{A_2C_1-A_1C_2}{A_1B_2-A_2B_1})$$

如果两形状中存在射线，则判断射线的端点与交点的位置关系，交点是否在端点沿射线方向的一侧。

如果两形状中存在线段，则判断线段的两端点与交点的位置关系，交点是否在两端点之间。

#### 判断方法

目前没有想到好的判断方法，所使用的就是暴力枚举，每加入一个新几何形状，将其与集合中每一个元素求交点。

#### 复杂度

因为是暴力枚举，复杂度仅能达到 $O(n^2)$。

### 设计实现过程

#### 交点类 Dot

交点类通过继承 `pair<double, double> ` 实现，操作比较简单。

为了判断重复交点，需要重写 `equals` 函数。

```c++
class Dot : public pair<double, double>;
```

其中考虑到浮点数的精度问题，定义了一个宏函数 `DoubleEquals`。

```c++
#define DoubleEquals(a, b) (fabs((a) - (b)) < 1e-10)
```

#### 图形类

##### Graph

所有几何形状的共同父类，由于统一用直线的一般式表示，定义获取三个参数的虚函数。

```c++
class Graph {
public:
	virtual double GetA() = 0;
	virtual double GetB() = 0;
	virtual double GetC() = 0;
};
```

##### Line

通过继承 `Graph` 实现。

```c++
class Line : public Graph {
private:
	double A, B, C;
};
```

##### Radial

通过继承 `Line` 实现。

```c++
class Radial : public Line {
private:
	Dot* end_point;
	Dot* cross_point;
};
```

##### Segment

通过继承 `Line` 实现。

```c++
class Segment : public Line {
private:
	Dot* end_point1;
	Dot* end_point2;
};
```

#### 交点容器类 Container

用于存储图形，存储并除去重合的交点。

```c++
class Container {
private:
	vector<Graph*>* graphs;
	set<Dot>* dots;
};
```

#### 计算

两直线平行直接使用公式 $A_1B_2=A_2B_1$ 判断。

```c++
double denominator = A1 * B2 - A2 * B1;

if (!DoubleEquals(denominator, 0)) {
    ……
}
```

交点计算同样套用公式 $(\frac{B_1C_2-B_2C_1}{A_1B_2-A_2B_1},\ \frac{A_2C_1-A_1C_2}{A_1B_2-A_2B_1})$。

```c++
double x = (B1 * C2 - B2 * C1) / denominator;
double y = (A2 * C1 - A1 * C2) / denominator;
Dot* intersect = new Dot(x, y);
```

两几何对象平行而且共线的时候，也有可能存在有限的交点（即恰有一个交点）或存在异常：

```c++
    else if (平行而且共线) {
		if (都是直线) {
			throw 无穷交点异常();
		} else if (都是射线) {
			if (垂直于x轴){
				if (相离) {;
				} else if (恰有一个交点){					
                    计算交点();
				} else {
					throw 无穷交点异常();
				}
			} else if(不垂直于x轴){...}
		} else if(g1是射线&&g2是线段){...}
        else if(g1是线段&&g2是射线){...}
        else if(g1是线段&&g2是线段){...}
}
```

即出现如下情况

![](./assets/line.png)



#### 判断

##### 判断交点是否在射线上

交点是否在射线上，其实就是交点是否在端点沿射线方向的一侧。

通过判断交点与端点组成的向量是否与射线射线上一点与端点组成的向量同向，即可得到答案。

```c++
return IsSameSymbol((cross_point->GetX() - end_point->GetX()), (intersect->GetX() - end_point->GetX()))
		&& IsSameSymbol((cross_point->GetY() - end_point->GetY()), (intersect->GetY() - end_point->GetY()));
```

##### 判断交点是否在线段上

交点是否在线段上就非常简单了，暴力判断交点的横纵坐标是否在线段两端点的横纵坐标范围内。

```c++
return intersect->GetX() >= min(end_point1->GetX(), end_point2->GetX())
		&& intersect->GetX() <= max(end_point1->GetX(), end_point2->GetX())
		&& intersect->GetY() >= min(end_point1->GetY(), end_point2->GetY())
		&& intersect->GetY() <= max(end_point1->GetY(), end_point2->GetY());
```

#### 封装为独立模块

封装后暴露 $Container$ 类，设计以下接口：

- 项目核心功能交点计算
  - `void AddGraph(char type,int x1, int y1, int x2, int y2)`
  - `void DeleteGraph(char type, int x1, int y1, int x2, int y2)`
- 获取交点个数，完成题目要求
  - `int Size()`
- 获取图形集合和交点集合，为 $UI$ 设计做准备
  - `vector<Graph*>* Getgraphs()`
  - `set<pair<double,double>>* GetDots()`

封装后暴露 $IOHandler$ 类，设计以下接口：

- 读取一个$(-100000, 100000)$范围内的整数
  - `int readNum()`
- 读取几何对象的数目$M\geq1$
  - `int readLine()`
- 读取结合对象类型
  - `char readGraphType()`

+ 打印一个整数到文件
  + `void outputInt(const int n)`



## 6.  计算模块接口部分的性能改进

对一组10000个随机几何对象共约250000个交点的运行结果如下

![](D:/shared_codes/IntersectProject/assets/time_cost.png)

其中，我们关注到，耗时最长的单体方法是`AddGraph`，但是考虑到其中很大部分是因为调用了`IntersectCalculate`方法，计算两个几何对象之间的交点。所以分析该方法：

这个函数有三个地方耗时可能比较多：一个是计算交点的浮点数计算模块，涉及大量的浮点计算；另一个是对于很多特殊情况的判断，尤其是需要考虑到线段和射线共线的几种情况，做了非常多的if-else判断，在运行时会增加很多跳转；第三个是因为AddDot方法使用了内置的set容器，使用红黑树作为存储结构，在添加一个点时，需要判断多次的$<$关系，其时间复杂度为$O(logn)$。

可能的解决办法为使用`<unorder_map>`来存储交点，将时间复杂度将为`O(1)`。



## 8. 计算模块部分单元测试展示

## 单元测试

### 消除 Code Quality Analysis 中的所有警告

此处我们也学习到了很多细节知识，比如在封装dll时使用的fstream和vector需要写成指针，以防止不同平台上模板不同导致的问题。

![Warning](D:/shared_codes/IntersectProject/assets/Warning.jpg)

### 单元测试

#### 覆盖率

![Coverage](D:/shared_codes/IntersectProject/assets/Coverage.jpg)

#### 扩展计算交点功能

##### TestDot

测试 $Dot$ 类的 5 个函数

- 构造函数 `Dot(double, double)`
- 拷贝构造 `Dot(const Dot&)`
- 获取坐标 `double GetX()`，`double GetY()`
- 相等判断 `bool equals(Dot b)`

其中测试重点在相等判断上，需要修正 $double$ 的精度误差，例如

- $77940 / 11959+1.11111111- 1.11111111$
- $78005 / 11969 +0.33333333- 0.33333333$
- $16451 / 16447 + 0.99999999 - 0.99999999$
- $48119 / 48121 + 0.000000003 - 0.000000003$

##### Test Line, Radial, Segment

测试图形类的函数

- 构造函数
- 获取参数
- 获取端点

这方面比较简单，无需赘述。

##### TestSolve

测试交点的平行、计算与位置关系，包括

- 一般情况
- 平行

```c++
segment = new Segment(Dot(1, 1), Dot(1, -1));
line = new Line(Dot(2, 2), Dot(2, 0));
radial = new Radial(Dot(3, 3), Dot(3, 4));
```

- 交点与交点重合

```c++
segment = new Segment(Dot(-1, 3), Dot(2, -1));
line = new Line(Dot(-2, 2), Dot(3, 0));
radial = new Radial(Dot(-3, 0), Dot(4, 2));
```

- 端点与端点重合

```c++
segment = new Segment(Dot(0, 2), Dot(3, -1));
line = new Line(Dot(4, 2), Dot(5, 0));
radial = new Radial(Dot(0, 2), Dot(3, -1));
```

- 端点与交点重合

```c++
segment = new Segment(Dot(0, 2), Dot(3, -1));
line = new Line(Dot(0, 2), Dot(2, 2));
radial = new Radial(Dot(0, 2), Dot(3, -1));
```

#### 将扩展后的功能封装为独立模块

回归测试，同时测试模块接口

```c++
container->AddGraph('S', -1, 3, 2, -1);
container->AddGraph('L', -2, 2, 3, 0);
container->AddGraph('R', -3, 0, 4, 2);
Assert::AreEqual(container->Size(), 1);

container = new Container();
container->AddGraph('S', 1, 1, 1, -1);
container->AddGraph('L', 2, 2, 2, 0);
container->AddGraph('R', 3, 3, 3, 4);
Assert::AreEqual(container->Size(), 0);
……
```

------



## 9. 计算模块部分异常处理说明

注：下述`WRITE()`为一个宏函数，将制定字符串写入测试文件，以便模拟IO读取中遇到的异常

+ 输入不是整数的异常

  为了防止输入小数或者异常字符的情况

  ```c++
  WRITE("wordsssss");// 将wordsssss写入文件
  auto func0 = [&] {io->readNum(); };// 尝试读取文件
  Assert::ExpectException<not_integer_exception>(func0);// 捕获“不是整数”异常
  WRITE("0.136");// 将0.136写入文件
  auto func2 = [&] {io->readNum(); };// 尝试读取文件
  Assert::ExpectException<not_integer_exception>(func2);// 捕获“不是整数”异常
  ```

  wordsssss不为整数，0.135也不是整数，故抛出`not_integer_exception`异常

  

+ 输入整数小于一的异常

  为了防止输入几何对象的数目时，自然数$N<1的情况$

  ```c++
  WRITE("0");// 将0写入文件
  auto func0 = [&] {io->readLine(); };// 尝试读取文件
  Assert::ExpectException<not_valid_integer_exception>(func0);// 捕获“几何对象数量小于1”异常
  ```

  输入的整数0代表有0个几何对象，不合法，故抛出`not_valid_integer_exception`异常

  

+ 输入整数小于等于-100000或大于等于100000的异常

  为了防止输入的整数超过$(-100000,100000)$的范围

  ```c++
  WRITE("-100000");// 将-100000写入文件
  auto func = [&] {io->readNum(); };// 尝试读取文件
  Assert::ExpectException<over_range_exception>(func);// 捕获“坐标超出范围”异常
  ```

  输入的-100000超出了$(-100000,100000)$的坐标限制，故抛出`over_range_exception`异常

  

+ 输入图形类型不是直线、射线、线段或圆的异常

  为了防止描述几何对象时，第一位的字符不为L、R、S、C中的一个的情况

  ```c++
  WRITE("l");// 将l写入文件
  auto func2 = [&] {io->readGraphType(); };// 尝试读取文件
  Assert::ExpectException<undefined_graph_exception>(func2);// 捕获“几何对象类型不正确”异常
  ```

  输入的小写字母l不能够代表任何一种几何对象，故抛出`undefined_graph_exception`异常

  

+ 输入同一图形时两个点重合的异常

  为了防止描述几何对象时，点<x1,y1>和点<x2,y2>为同一个点的情况

  ```c++
  Dot d0(4.123, 0.1341);
  Dot d1(3.123 + 0.9 + 0.1, -8.1341 + 8.2682);
  auto func0 = [&] {Graph* g = new Line(d0, d1); };// 尝试以两个相同的点构造直线
  Assert::ExpectException<dot_superposition_exception>(func0);// 捕获“两点相同”异常
  ```

  新建一条直线时，发现直线经过两个点$(4.123, 0.1341)$和点$(4.123,01241)$是同一个点，他们不能够描述一条特定的直线，故抛出`dot_superposition_exception`异常

  

+ 输入两个图形有无数个交点的异常

  为了防止输入的任意两个几何对象之间，存在无数的交点（重合）

  ```c++
  Dot d0(0, 0);
  Dot d1(1, 1);
  Dot d2(2, 2);
  Dot d3(3, 3);
  auto func = [&] {// 尝试构造一条射线和一条线段，他们有公共部分
  	Container* c = new Container();
  	Graph* s = new Segment(d0, d2);
  	Graph* r = new Radial(d1, d3);
  	c->IntersectCalculate(s, r);
  };
  Assert::ExpectException<infinate_intersect_exception>(func);// 捕获“无数个交点”异常
  ```

  经过$(0,0)$和$(2,2)$的线段，与起点为$(1,1)$通过$(3,3)$的射线，在$x\in (1,2)$的范围内有无数个交点，故抛出`infinate_intersect_exception`异常

  

+ 输入文件不存在的异常

  为了防止命令行输入的输入文件不存在的情况

  ```c++
  // 提前删除默认读入的文件
  auto func = [&] {IOHandler* io = new IOHandler(0, NULL, 1); };// 尝试读取该文件
  Assert::ExpectException<file_not_exist_exception>(func);// 捕获“文件不存在”异常
  ```

  手动将输入文件删除，IOHandler找不到该文件，故抛出`file_not_exist_exception`异常



## 10. 界面模块的详细设计过程

![](./assets/ui.png)

首先发现一个问题：VS封装的dll文件和Qt并不兼容，不能够直接导入使用，需要在qt内新建一个c++ library项目，将所有的.h和.cpp源文件导入并编译成dll和lib文件，才能够在UI模块被Qt所使用。

在Qt的Widgets中，我使用两个QLineEdit模块作为输入要添加和删除的几何对象的属性、使用三个QPushButton分别用来打开文件、删除几何对象和添加几何对象。其具体的工作流程如下：

+ 点击“打开文件”按钮

  ```c++
  QString fileName = QFileDialog::getOpenFileName(this, QString("choose a file"), ".");
  if (fileName.isEmpty()) return;
  io = new IOHandler(fileName.toStdString(),"output.txt");
  ```

  点击“打开文件”按钮时，该代码块在slot（自带的回调机制）内被调用，使用`QFileDialog::getOpenFileName`打开一个熟悉的文件选择目录框，然后使用封装好的IOHandler模块读取该文件和创建默认的输出文件output.txt。

+ 在输入框输入`L 0 0 1 1`，然后点击“添加几何对象”

  ```c++
  stringstream buf(ui->addText->text().append('\n').toStdString());
  ...
  char type = readGraphType(&buf);
  int x1 = readNum(&buf);
  int y1 = readNum(&buf);
  int x2 = readNum(&buf);
  int y2 = readNum(&buf);
  container->AddGraph(type,x1,y1,x2,y2);
  updateList();
  updateGraph();
  updateIntersect();
  ```

  点击“添加几何对象”按钮时，该代码块被调用，其作用为将`addText`文本框中的内容（即`L 0 0 1 1`）读取，末尾添加一个`\n`以强调结束，并转化为一个`stringstream`流。使用类似于文件读取的方法，用`>>`操作将buf中的值写入相应的变量中，如果有异常就抛出异常（`readGraphType()`和`readNum()`负责）。然后直接调用接口`AddGraph`添加图形。

  添加完成后，调用三个`update*`函数，从container中取出当前已有几何图形列表、所有图形和所有交点，然后在三个`update*`中，绘制列表框、图形曲线和交点数目。

+ 在输入框内输入`L 0 0 1 1`，然后点击“删除几何对象”

  同理“添加几何对象”，只是将`AddGraph()`换成了`DeleteGraph()`接口。

+ 绘制列表框

  ```c++
  QStringList list;
  for(Graph *g: container-> GetGraphs()){
      list<<QString::fromStdString(g->ToString());
  }
  QStringListModel *model = new QStringListModel(list);
  ui->list->setModel(model);
  ```

  更新列表框方法很简单，从container中取出所有的几何对象，将其`toString()`为`S 10 2 5 8`这样的格式，然后压入一个`QStringList`对象，将其转化为`QStringListModel`后展示。

+ 绘制几何曲线

  ```c++
  QPainter painter(&image);
  // 画框
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawLine(0, SIZE/2,SIZE+10,SIZE/2);//绘制x轴
  painter.drawLine(SIZE/2, 0,SIZE/2,SIZE+10);//绘制y轴
  // 画图
  for (Graph* g : container->GetGraphs()) {
     if (g->type=='L') {
          绘制直线();
      } else if (g->type=='R') {
          绘制射线()；
      } else if (g->type=='S') {
          绘制直线()；
      }
  //画点
  for (pair<double,double> d:dots=container->GetDots()){
      drawDot(&painter, d.first,d.second);
  }
  update();
  ```

  在绘制射线时，使用了一种类似**跳棋**的方法绘制射线：设端点为A，射线通过点为B，那么以B为台阶，让A跳到C点（即B为AC的中点）；令B=C，再让A跳，直到超过图像边界。然后再以A和B两点利用`QPainter::drawLine`绘制线段来表示射线。



## 11. 界面模块与计算模块的对接

由于VS的dll文件无法与Qt对接，需要在Qt新建一个C++ Library项目，加入所有的.h头文件和.cpp源文件（再加上Qt自带的两个用于支持dll的.h头文件）进行编译。

将编译得到的.lib和.dll文件，复制到Qt主项目目录下，并在Qt主目录点击右键“添加库”，选择外部库->选择.lib文件->windows->动态，其自动在.pro（项目文件）下添加以下几行

```
win32: LIBS += -L$$PWD/./ -ldllQtProject # 假设.lib文件命名为dllQtProject.lib
INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
```

再导入所有的.h头文件，即可再界面模块使用计算模块。

在界面模块中，使用到了计算模块提供的如下几个接口：

```c++
int Container::Size();
vector<Graph*>* Container::GetGraphs();
set<pair<double,double>>* Container::GetDots();
void Container::AddGraph(char type, int x1, int y1, int x2, int y2);
Graph* Container::DeleteGraph(char type, int x1, int y1, int x2, int y2);
```

```c++
int IOHandler::readNum();
int IOHandler::readLine();
char IOHandler::readGraphType();
```





## 12. 结对的过程

在结对过程中，使用了一段时间的屏幕共享，但是由于两人微小地域时差和作息不一致，并没有全程使用。

![](./assets/screen.png)

还使用了github上的issue和pull request来管理仓库

![](./assets/issue.png)

![](./assets/pr.png)

