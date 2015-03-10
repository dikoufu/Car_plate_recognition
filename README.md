# Car_plate_recognition
A License plate recognition (LPR) program written in C++

用基于基于彩色不变特征的车牌定位算法，对复杂背景及非均匀光照条件下取得的车辆图像进行车牌定位。

算法通过计算R、G、B三色定义出彩色不变性特征H，从而将图像分割成多个候选区域，然后根据车牌的彩色
特征对候选区域进行垂直投影，以除去伪牌照区域,进而精确地定位出车牌。