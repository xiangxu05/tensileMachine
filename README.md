
# 介绍 
使用arduino uno R3 实现对伺服电机控制以及拉力值检测，同时上位机使用了node-red，rs485通讯；其中node-red使用Serial控件和dashboard控件。

# 软件介绍
"拉力测试软件V1"是本公司设计的一款拉力测试机配套使用的专用软件。主要用于控制伺服电机以及实时获取对应拉力值。同时也可以对检测数据进行收集与整理。  
 该款软件可以实时显示当前的拉力值并统计任务开始以来的拉力值生成线图。软件保存数据文件格式目前为.txt文件。操作界面如图所示。  

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/28b51a0a-5aed-49b7-8a76-ec6bfb026eb4)

<p align="center">图1 软件操作界面</p>  

## 查询设备状态
通过点击“查询设备状态”按钮，如图2所示，可以对设备的状态进行查询，设备目前设置总共有两种状态，在线和掉线。设备正常时，显示如图2所示。  

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/ddef1746-5eeb-41a9-9d4e-eff8a77995c1)

<p align="center">图2 查询设备状态示意</p>  

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/3f375bfd-0cfc-406f-a73c-9b29544f603f)  

<p align="center">图3 设备状态显示</p>  
 

## 设备控制
目前拉力机总共有三种状态，分别是启动、停止和复位，分别对应着拉力机从初始位置开始往上运动、任意状态时的停止动作以及当前轮测试结束后操作设备复位的状态，如图4所示。

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/4a7a928e-7064-4a88-a6ed-f4a0418c7fa8)

<p align="center">图4 拉力机状态控制</p>  

## 文件目录
本软件具备将测试获取的数据，保存到指定的文件目录当中，因此在测试开始前，需要将想要存储的目录以及文件名输入到对应的输入框中，如图5所示。

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/95e79328-cefc-4018-a430-58c39abaca87)

 <p align="center">图5 文件路径设置</p>  

## 数据实时可视化
如图6所示，本软件可将获取到的拉力图实时可视化展现到界面当中，在默认状态，该图标显示为“等待数据传入”，拉力机开始工作后，经过预紧，实时数据便可以显示出来，如图7所示。

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/5da5fad0-88bd-475b-810d-e89b361290c7)

  <p align="center">图6 空闲时刻图表状态</p>  

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/ff79f5f3-31ef-4075-a77d-aca0d510a7f6)

   <p align="center">图7 实时数据图表显示</p>  

## 操作流程
综上，拉力测试仪的使用操作流程如图8所示。在初始状态下，界面显示如图1所示。我们可以先通过“查询设备状态”按钮，查看控制设备是否在线。设备在线的基础上，首先输入目标文件存储位置，在夹具夹紧测试样品后，点击开始。此时拉力机便会开始向上运动，在往上拉了100mm的距离后，拉力机停止，文件保存。

![image](https://github.com/xiangxu05/tensileMachine/assets/112842118/a2dc576f-57e5-41c3-887e-52270383f9dd)

<p align="center">图8 操作流程图</p>  

