本项目为CUMCM2018选题B仿真代码
采用贪心策略进行RGV控制

使用方式：
建议在main.cpp的计时主循环中加入断点，
通过VS提供的变量监视功能监视cnc_array, r, msg来观察仿真情况

Update 3：
1.支持情况2，即需要两道工序，需要在macro.h中定义宏MULTIPLE，删除改宏可以恢复到情况1。

Update 2：
1.能够正确的将material在cnc与RGV之间传递与销毁，可以通过material的成员函数is_init来判断是否真实存在。
2.为material加入id用于区别。
3.将log以csv格式输出至log.csv。

Update 1：
1.为消息加入了id用于区别（暂未发挥作用）。
2.修复了RGV代码中的一些问题。
3.在cnc.h中加入了函数get_pos用于将cnc编号转换为位置。
4.为RGV增加了简单的运行策略。



代码编写平台 Visual Studio 2017 in Windows 10