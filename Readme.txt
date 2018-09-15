本项目为CUMCM2018选题B仿真代码
采用贪心策略进行RGV控制

使用方式：
因为暂时没有加入调试信息输出，所以建议在main.cpp的计时主循环中加入断点，
通过VS提供的变量监视功能监视cnc_array, r, msg来观察仿真情况

暂未加入熟料计数

Update：
1.为消息加入了id用于区别（暂未发挥作用）。
2.修复了RGV代码中的一些问题。
3.在cnc.h中加入了函数get_pos用于将cnc编号转换为位置。
4.为RGV增加了简单的运行策略。

代码编写平台 Visual Studio 2017 in Windows 10