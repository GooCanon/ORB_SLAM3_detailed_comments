/*
 * @Description: 
 * @Autor: drx
 * @Date: 2021-01-29 11:43:17
 * @LastEditors: drx
 * @LastEditTime: 2021-01-29 21:14:51
 */
int main(void)
{
    //注：只要IMU第一阶段初始化完成，则视为IMU初始化成功
    //Tracking:
    while (得到帧数据和IMU数据)
    {
        //预积分
        PreintegrateIMU();
        if (跟踪过程中)
        {
            //预估位姿
            if (IMU初始化成功)
            {
                PredictStateIMU();
                if (地图更新)
                {
                    //从上一关键帧优化位姿
                    PoseInertialOptimizationLastFrame();
                }
                else
                {
                    //从上一帧优化位姿
                    PoseInertialOptimizationLastKeyFrame();
                }
            }
        }
    }
    //LocalMapping
    while (得到关键帧)
    {
        if (IMU初始化成功)
        {
            更新t
            LocalInertialBA();
        }
        if (IMU未初始化)
        {
            //快速初始化IMU：目的在于尽快用IMU来跟踪
            InertialOptimization();
            FullInertialBA();
            IMU第一阶段初始化成功
        }
        else if (IMU第一阶段 && t > 5秒)
        {
            //快速修正IMU：目的在于短时间内使IMU参数相对靠谱
            InertialOptimization();
            FullInertialBA();
            IMU第二阶段初始化成功
        }
        else if (IMU第二阶段 && t > 15秒)
        {
            //再次修正IMU：目的在于保证IMU精度
            InertialOptimization();
            FullInertialBA();
            IMU第三阶段初始化成功
        }
        if (关键帧数 <= 100 && t某个时间范围内每10秒)
        {
            //优化重力方向和尺度
            InertialOptimization();
        }
    }
    //LoopClosing
    While(得到关键帧)
    {
        if(触发地图融合)
        {
            if (IMU第三阶段初始化前)
            {
                //优化速度、bg、ba
                InertialOptimization();
            }
        }
        if(触发回环)
        {
            if (IMU初始化成功)
            {
                FullInertialBA();
            }
        }
    }
}