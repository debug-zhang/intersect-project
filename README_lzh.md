# [2020 BUAA 软件工程]结对项目作业

| 项目                                 | 内容                                                         |
| :----------------------------------- | :----------------------------------------------------------- |
| 课程：北航2020春软件工程             | [博客园班级博客](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ) |
| 作业：阅读并撰写博客回答问题         | [结对项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10466) |
| 我在这个课程的目标是                 | 积累两人结对编程过程中的经验                                 |
| 这个作业在哪个具体方面帮助我实现目标 | 体验两人结对编程过程，努力提高沟通效率和代码匹配度           |

### 1.项目地址

- 教学班级：006

- 项目地址：https://github.com/blackbird52/IntersectProject.git

- 目录结构：

  ```
  IntersectProject/
  ├── bin
  │   ├── intersect.exe
  │   └── dllProject.dll
  ├── README.md
  ├── src
  │   ├── main.cpp
  │   └── core
  │   │   ├── container.h
  │   │   ├── dot.h
  │   │   ├── exception.h
  │   │   ├── framework.h
  │   │   ├── graph.h
  │   │   ├── IOHandler.h
  │   │   ├── line.h
  │   │   ├── pch.h
  │   │   ├── radial.h
  │   │   ├── segment.h
  │   │   ├── container.cpp
  │   │   ├── dllmain.cpp
  │   │   ├── dot.cpp
  │   │   ├── IOHandler.cpp
  │   │   ├── line.cpp
  │   │   ├── pch.cpp
  │   │   ├── radial.cpp
  │   │   └── segment.cpp
  └── test
      ├── pch.h
      ├── pch.cpp
      ├── UnitTestIntersect.cpp
      ├── UnitTestInterface.cpp
      └── UnitTestException.cpp
  ```



### 2.时间规划

预估耗时

| PSP2.1                                  | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| :-------------------------------------- | :-------------------------------------- | :--------------- | :--------------- |
| Planning                                | 计划                                    |                  |                  |
| · Estimate                              | · 估计这个任务需要多少时间              | 10               |                  |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 500              |                  |
| · Design Spec                           | · 生成设计文档                          | 15               |                  |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 10               |                  |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 5                |                  |
| · Design                                | · 具体设计                              | 15               |                  |
| · Coding                                | · 具体编码                              | 140              |                  |
| · Code Review                           | · 代码复审                              | 15               |                  |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 120              |                  |
| Reporting                               | 报告                                    |                  |                  |
| · Test Report                           | · 测试报告                              | 30               |                  |
| · Size Measurement                      | · 计算工作量                            | 5                |                  |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 5                |                  |
|                                         | 合计                                    | 920              |                  |



### 3.接口设计

#### 信息隐藏

改进了计算几何对象交点的程序，将其封装到Container内，其条件判断、求解方法不公开。

设计了IOHandler模块，作为输入输出的总控制器。将实现细节封装进模块中，比如文件指针、文件路径、具体读写文件的方法和读写时的异常情况。

#### 接口设计

Container只暴露`Size()`，`Getgraphs()`，`GetDots()`，`AddGraph()`和`DeleteGraph()`五个接口。分别用于取得交点个数、取得几何图形、取得交点、添加几何图形和删除几何图形。足以涵盖包括UI在内所有要使用信息。

IOHandler类只暴露四个接口`readNum()​`，`readLine()`，`readGraphType()`和`outputInt()`，分别用于读入一个范围在$(-100000,100000)$的整数、读入几何对象数量，读入一个表示几何对象类型的字符和输出一个整数。四个接口涵盖了IO方面所有的功能。

#### 松耦合

模块和模块之间必然存在着必要的信息交流，比如计算交点的Container类必须知道直线的表示方法是$ax+by+c=0$，所以我们也只透露这点信息给它，它也只能使用一定的接口获得$a$，$b$，$c$三个参数。只要能够保证外界其他类能够获得直线$ax+by+c=0$的表达式，我们可以任意修改直线类里面的任何实现。IOHandler模块也是，只暴露4个必要的接口。

但是对于异常，我是实现将所有的异常都给出，并没有将其封装成一个“异常”类。如果某个异常的含义发生了变化，那么对应的，需要修改所有使用到该异常的地方。这确实是软件在仓促设计时候的一个小不足。



### 5.UML

由于计算的核心模块并非本人所写，故引用合作伙伴张xz同学的[素材](https://github.com/blackbird52/IntersectProject/blob/master/assets/ClassDiagram.png)

![](./assets/ClassDiagram.png)



### 7.契约式设计和代码协定

这种方法要求软件设计者为软件组件定义正式的，精确的并且可验证的接口。分为前置条件、后置条件和类不变项三大部分。

+ 优点是程序员对于代码有着全面的思考和把控，能够确定每一个代码块能够在任何条件下实现它的功能，拥有很好的鲁棒性；同时对每个模块都明确约定好的输入和输出，编码的逻辑相对比较简单
+ 缺点是工作效率太低。首先在设计阶段并不能预知许多实际遇到的问题，在实际开发过程中也许会被迫修改契约；另外，如果要对不同的输入条件做各种异常处理，代码无疑十分臃肿，开发和运行效率可能较低

在我写的那部分代码中，对于后置条件有一定的实现。每个方法都考虑到部分输入可能的情况，在遇到问题时，它能够抛出指定的异常，比如文件不存在或者两个几何对象有无穷个交点。但是对于这方面的问题，双方事先并没有进行沟通，没有对每一个模块都设定规范的输入和输出。同时因为考虑到本次作业的数据流较为单一，每个函数的输入输出都相对种类单一，时间紧迫，讨论后没有没有采用契约式设计。

但是对于每个暴露出来的接口，我都写了接口文档，说明了每个模块的作用、参数、返回值和期望的异常，也许在一个侧面反映了契约式设计的一些特点。

```c++
//IOHandler
/**
* read an integer, ensure in range(-100000, 100000)
* params: None
* returns: aa integer in range(-100000,100000) from ifstream
* exceptions: not_integer_exception - if is not an integer(decimal, char, ect)
*	   		  over_range_exception - if integer is not in range (-100000, 100000)
**/
int readNum();

/**
* read an integer, ensure in range[1, inf), which means how many graphs in the map
* params: None
* returns: an integer in range[1,inf) from ifstream
* exceptions: not_integer_exception - if is not an integer(decimal, char, ect)
*			  not_valid_integer_exception - if not in range[1, inf)
**/
int readLine();

/**
* read a char which means graph type, which must in [L, R, S, C]
* params: None
* returns: a char in [L, R, S, C]
* exceptions:  undefined_graph_exception - if is not a valid type of graph 
**/
char readGraphType();

/**
* print an integer into ofstream
* params: const int n
* returns:
* exceptions:
**/
void outputInt(const int n);
```



### 13.结对编程感想

自我感觉，在编写核心模块中，自己更像一个领航员。在这次的作业中，核心功能的设计和编码并不是我完成的，自己只是写了IO部分、异常部分和修复了核心功能的一些bug；但是在项目规范的设计和博客的分工方面，一直都是我用了“断言”的方式来制定规范的，所以感觉自己更像一个领航员。

在编写UI模块中，自己是一个实践者。从零学习、搭建Qt环境、设计UI、接入核心计算模块，都是我一个人全权负责，伙伴则修改模块接口的不足和缺陷。

但是我也反思，自己这两个星期以来，对于任务进度的把控并不是很好，没有明确任务每一个进度的规划时间，而是做到哪算到哪，导致任务提交前十分匆忙；第二是，对于结对伙伴不够信任，常常会心理担心代码中是不是有bug，会被查出然后扣分。

在这次的体验中，我感受到的结对编程的一些优缺点：

优点：

+ 代码复审的机制能够帮助双方少写bug，提供更好的代码质量和测试质量
+ 双人合作的模式，对于双方都更有动力，更加富有责任感，愿意把自己的事情尽快做完不拖累进度

缺点

+ 额外多了很多沟通的成本，包括规范的设计和遇到一个问题之后双方如何承担责任并修复
+ 系统环境一致性问题，由于双方项目的目录结构不同，开发初期双方在文件路径上出现了分歧
+ 工作时间匹配问题，由于地域时差和作息重合时间少，故屏幕共享直播编程的机会并不会特别多，很多交流是通过微信、pull request或者issue等异步的方式解决



### 14.时间记录

| PSP2.1                                  | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟）        |
| :-------------------------------------- | :-------------------------------------- | :--------------- | :---------------------- |
| Planning                                | 计划                                    |                  |                         |
| · Estimate                              | · 估计这个任务需要多少时间              | 10               | 5                       |
| Development                             | 开发                                    |                  |                         |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 500              | 660（包括搭建、学习Qt） |
| · Design Spec                           | · 生成设计文档                          | 15               | 20                      |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 10               | 5                       |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 5                | 3                       |
| · Design                                | · 具体设计                              | 15               | 5                       |
| · Coding                                | · 具体编码                              | 140              | 195                     |
| · Code Review                           | · 代码复审                              | 15               | 10                      |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 120              | 240                     |
| Reporting                               | 报告                                    |                  |                         |
| · Test Report                           | · 测试报告                              | 30               | 15                      |
| · Size Measurement                      | · 计算工作量                            | 5                | 2                       |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 5                | 5                       |
|                                         | 合计                                    | 920              | 1165                    |

时间相差了245分钟，将近4个小时。我回忆了一下，主要是这几个方面占用了太多的时间：1) Qt的安装，因为依赖没有安装导致四处碰壁 2) Qt不能使用vs导出的.dll库，摸索许久 3) 核心模块的设计并没有对UI方面做好足够的支持，发现了一些接口的不足和缺陷 4) Qt绘制曲线图有一定的难度，如果使用plot相关的插件，相信效果会好很多。

这次结对过程，本人就是很吃了设计上的亏，在具体编码过程中，遇到了不少意料之外的问题，急急忙忙去寻求解决方案。因此，我得到的教训最重要的就是，必须事先在设计阶段就将大部分的问题发现并解决。这个过程需要合作伙伴一起头脑风暴，利用白板等工具画出依赖关系、业务流程等，然后试图发现其中的问题，并且对于已经发现的问题找到可能的解决方案，未雨绸缪。