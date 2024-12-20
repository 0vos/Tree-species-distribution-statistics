# Tree-species-distribution-statistics
2024 Winter 数据结构课程设计
```
15、树种分布统计问题
【问题描述】
科学家根据某森林地区的卫星云图标记处该地区的树种分布情况。树木名称存放在文本文件中，每一行存放一种数据名称和该树的其它信息。树种分布问题要求根据文本文件信息统计出各种树种在该森林地区所占的比例。
【设计要求】
设计基于STL的散列表的树种分布统计程序。
（1）采用STL的散列表等数据结构。
（2）应用基本运算，实现算法求解。
```
## 运行
生成饼图（但是主要的增删改查工作在io.cpp的控制台）
1. 运行 server.cpp
2. 在浏览器（比如Chrome）中输入：
```
localhost:8888
```
## 开发日志
- 12.21
  - Qianqian: 衔接文件的读取，完成了从文件到散列表统计，统计出占比，生成饼图
  - 需解决：中文的问题

