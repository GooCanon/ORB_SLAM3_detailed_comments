/*
 * @Description: 
 * @Autor: drx
 * @Date: 2021-01-29 11:43:17
 * @LastEditors: drx
 * @LastEditTime: 2021-01-29 21:14:51
 */
int main(void)
{
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
                    //优化位姿
                    PoseInertialOptimizationLastFrame();
                }
                else
                {
                    //优化位姿
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
            LocalInertialBA();
        }
        if (!IMU初始化成功)
        {
            //快速初始化IMU
            InertialOptimization();
            FullInertialBA();
            IMU初始化成功
        }
        if (IMU初始化成功 && !IMU第二阶段初始化成功)
        {
            //快速修正IMU
            InertialOptimization();
            FullInertialBA();
            IMU第二阶段初始化成功
        }
        if (IMU初始化成功 && IMU第二阶段初始化成功 && !IMU第三阶段初始化成功)
        {
            //IMU最终版
            InertialOptimization();
            FullInertialBA();
            IMU第三阶段初始化成功
        }
        if (IMU第三阶段初始化成功)
        {
            //多次优化重力方向和尺度，最终版2.0、3.0、4.0……最终打死不改版2.0
            InertialOptimization();
        }
    }
    //LoopClosing
    While(得到关键帧)
    {
        if (需要地图融合)
        {
            //优化
            InertialOptimization();
            MergeInertialBA ? ? ?
        }
    }
}