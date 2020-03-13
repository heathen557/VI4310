﻿#include "dealusb_msg.h"


//图像显示相关
extern QMutex mutex_3D;  //3D点云/2D传输的互斥锁
extern QImage tofImage;
extern QImage intensityImage;
extern pcl::PointCloud<pcl::PointXYZRGB> pointCloudRgb;
extern bool isShowPointCloud;  //是否有点云数据 ，有的话显示否则不显示

//鼠标点击显示时相关
extern QMutex mouseShowMutex;
extern float mouseShowTOF[160][120];
extern int mouseShowPEAK[160][120];

/*保存用到的标识*/
extern bool isSaveFlag;        //是否进行存储
extern QString saveFilePath;   //保存的路径  E:/..../.../的形式
extern int saveFileIndex;      //文件标号；1作为开始



/*******统计信息相关的变量***********/
extern QMutex statisticMutex;
extern vector<vector<int>> allStatisticTofPoints;   //用于统计 均值和方差的 容器  TOF
extern vector<vector<int>> allStatisticPeakPoints;   //用于统计 均值和方差的 容器  TOF



DealUsb_msg::DealUsb_msg(QObject *parent) : QObject(parent),
    microQimage(160,120, QImage::Format_RGB32),macroQimage(160,120, QImage::Format_RGB32)
{

    //    pointCloudRgb.width = 16384;
    //    pointCloudRgb.height = 1;
    //    pointCloudRgb.resize(pointCloudRgb.width);

    tempRgbCloud.width = 19200;
    tempRgbCloud.height = 1 ;
    tempRgbCloud.points.resize(tempRgbCloud.width);

    LSB = 0.031; //时钟频率
    isFilterFlag = false ;    //初始化时不进行滤波
    lineSelect = false;       //初始化 不切换两行像素
    isTOF = true;
    localFile_timer = NULL;
    gainImage = 1;

    haveIndex = 0;
    peakOffset = 0;   //设置为阈值，小于这个值的认为是无效数据，将接收到的tof值设置为0  ::此功能预留，面阵_1028效果较好，但是对其他数据会滤掉大部分有效数据
    isOnlyCenterShow_flag = false;   //是否只显示中心区域的标识，设置为true则只显示中心光较强的区域（超过范围的点xyz坐标全部设置为0），设置为false则显示全部点云数据；默认false;
    averageNum = 1;            //滑动平均的帧数 , 默认为1


    //总共有16384个点，针对每一个点开启一个独立的容器进行存储相关内容    统计相关
    statisticStartFlag = true;
    statisticFrameNumber = 10;
    vector<int> singlePoint;
    for(int i=0; i<19200; i++)
    {
        tempStatisticTofPoints.push_back(singlePoint);
        tempStatisticPeakPoints.push_back(singlePoint);
        allStatisticTofPoints.push_back(singlePoint);
        allStatisticPeakPoints.push_back(singlePoint);
    }

}



void DealUsb_msg::loadLocalArray()
{
    //加载数据的配置四个相关的配置矩阵的部分

    //加载tofOffsetArray.txt配置集
    QFile tofOffsetArray_file("tofOffsetArray.txt");
    QString tofOffsetArray_line[16400];
    QString log_str;
    if (tofOffsetArray_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&tofOffsetArray_file);
        int i = 0;
        while (!in.atEnd())
        {
            tofOffsetArray_line[i] = in.readLine();
            i++;
        }
        tofOffsetArray_file.close();

        if(i<16383)
        {
            log_str = "[load conf file error]:tofOffsetArray.txt";
            emit Display_log_signal(log_str);

        }else{
            log_str = "[load conf file success]:tofOffsetArray.txt";
            emit Display_log_signal(log_str);
        }
    }else{
        log_str = "[load conf file error]:tofOffsetArray.txt";
        emit Display_log_signal(log_str);
    }



    //加载thetaArray.txt配置集
    QFile thetaArray_file("thetaArray.txt");
    QString thetaArray_line[16400];
    if (thetaArray_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&thetaArray_file);
        int i = 0;
        while (!in.atEnd())
        {
            thetaArray_line[i] = in.readLine();
            i++;
        }
        thetaArray_file.close();

        if(i<16383)
        {
            log_str = "[load conf file error]:thetaArray.txt";
            emit Display_log_signal(log_str);
        }else{
            log_str = "[load conf file success]:thetaArray.txt";
            emit Display_log_signal(log_str);
        }
    }else{
        log_str = "[load conf file error]:thetaArray.txt";
        emit Display_log_signal(log_str);
    }


    //加载betaArray.txt配置集
    QFile betaArray_file("betaArray.txt");
    QString betaArray_line[16400];
    if (betaArray_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&betaArray_file);
        int i = 0;
        while (!in.atEnd())
        {
            betaArray_line[i] = in.readLine();
            i++;
        }
        betaArray_file.close();

        if(i<16383)
        {
            log_str = "[load conf file error]:betaArray.txt";
            emit Display_log_signal(log_str);
        }else {
            log_str = "[load conf file success]:betaArray.txt";
            emit Display_log_signal(log_str);
        }
    }else{
        log_str = "[load conf file error]:betaArray.txt";
        emit Display_log_signal(log_str);
    }



    for(int i=0;i<16384;i++)
    {
        tofOffsetArray[i] = tofOffsetArray_line[i].toFloat();
        thetaArray[i] = thetaArray_line[i].toFloat();
        betaArray[i] = betaArray_line[i].toFloat();
        //        qDebug()<<"thetaArray["<<i<<"] = "<<thetaArray[i]<<endl;
    }
}

//!
//! \brief DealUsb_msg::change_gain_slot
//! \param gain
//!改变图像的增益
void DealUsb_msg::change_gain_slot(float gain)
{
    gainImage = gain;
}

//!
//! \brief change_tof_peak_slot
//!切换tof/peak的槽函数
void DealUsb_msg::change_tof_peak_slot()
{
    if(isTOF == true)
        isTOF = false;
    else
        isTOF = true;
}

//修改统计帧数的槽函数
void DealUsb_msg::alterStatisticFrameNum_slot(int num)
{
    statisticFrameNumber = num ;

}

//修改是否进行滤波的槽函数
void DealUsb_msg::isFilter_slot(bool isFiter)
{
    if(true == isFiter)
    {
        isFilterFlag = true;
    }else{
        isFilterFlag = false;
    }


}

// 160x120版本的协议     一个包324个字节 2个字节的spadNum, 2个字节的lineNum
// 从中间往上下两侧扩散
// 中间行为 59   0-59为上半部分   60-129为下半部分
//!
//! \brief DealUsb_msg::recvMsgSlot
//! \param array
//!     spadNum = 0,1,2,...119         一个spadNum 有160个点 一行数据的量 所以总共有120个点
//!  1、首先根据lineNum(0,1)来判断是属于上半部分，还是属于下半部分
//!  2、lineIndex = spadNum/4 = 0,1,2,...29      宏像素的第几个 因为是4个spadNum为一组
//!  3、InnerLineNum =  (spadNum%4)/2 = 0,1      spadNum%4 = 0 ,1,2,3       //宏像素的第一行还是第二行
//!  4、在160*120的图像中的行号为： rowImage = lineIndex*2 + InnerLineNum   (0-59)
//!                                上半区：59 - rowImage
//!                                下半区：60 + rowImage
//!
//!  5、colImage = i*2 + spadNum%2
void DealUsb_msg::recvMsgSlot(QByteArray array)
{
    int ret;
    char *MyBuffer;

    MyBuffer = array.data();


    int rowImg,colImg;
    int spadNum = (quint8)(MyBuffer[0]) +  (((quint8)(MyBuffer[1]))<<8);            // 0,1,2,3....119
    int line_number = (quint8)(MyBuffer[2]) +  (((quint8)(MyBuffer[3]))<<8);        // 0 或者 1


    if(line_number > 1 )
    {
        qDebug()<<"line_number error,  LineNum="<<line_number;
    }

    if(spadNum < lastSpadNum)  //此时说明上一帧数据已经接收完毕，把整帧数据付给其他线程，供其显示，数据可以显示了
    {
        haveIndex++;


        //统计信息相关的 ，将统计信息的容器赋值给全局变量
        if(statisticStartFlag)
        {
            statisticMutex.lock();
            allStatisticTofPoints = tempStatisticTofPoints;
            allStatisticPeakPoints = tempStatisticPeakPoints;
            statisticMutex.unlock();
        }


        //向主线程中发送最大值、最小值等统计信息
        emit staticValueSignal(tofMin,tofMax,peakMin,peakMax,xMin,xMax,yMin,yMax,zMin,zMax);
        //重置变量
        tofMin = 10000;
        tofMax = -10000;
        peakMin = 10000;
        peakMax = -10000;
        xMin = 10000;
        xMax = -10000;
        yMin = 10000;
        yMax = -10000;
        zMin = 10000;
        zMax = -10000;



        // 1、将滤波功能放到这里进行实现，
        // 2、将滤波后的三维点云 同步到二维图像
        if(true == isFilterFlag)
        {
            /*******************开启滤波功能*********************************/
            //先用直通滤波把所有零点重复的零点过滤掉
            /* pcl::PassThrough<pcl::PointXYZRGB> pass;                      //创建滤波器对象
            pass.setInputCloud(tempRgbCloud.makeShared());                //设置待滤波的点云
            pass.setFilterFieldName("y");                                 //设置在Z轴方向上进行滤波
            pass.setFilterLimits(0, 0.10);                                //设置滤波范围(从最高点向下0.10米去除)
            pass.setFilterLimitsNegative(true);                           //保留
            pass.filter(tempRgbCloud_pass);                                   //滤波并存储
            if(tempRgbCloud_pass.size()<1)
                return;

            //统计
            tempRgbCloud_radius.clear();
            pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> outrem(true);
            outrem.setInputCloud(tempRgbCloud_pass.makeShared());
            outrem.setMeanK(40);
            outrem.setStddevMulThresh(0.25);
            //40  0.1 不见前面噪点
            outrem.filter(tempRgbCloud_radius);
            int len = outrem.getRemovedIndices()->size();*/
            QTime t1,t2;
            pcl::VoxelGrid<pcl::PointXYZRGB> sor;//滤波处理对象
            sor.setInputCloud(tempRgbCloud.makeShared());
            sor.setLeafSize(0.03f, 0.03f, 0.03f);//设置滤波器处理时采用的体素大小的参数
            sor.filter(tempRgbCloud_pass);

            tempRgbCloud_radius.resize(0);
            //            t1 = QTime::currentTime();
            pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> outrem;      //设置为true以后才能获取到滤出的噪点的 个数以及点的序列号
            outrem.setInputCloud(tempRgbCloud_pass.makeShared());              //设置输入点云
            outrem.setRadiusSearch(0.2);              //设置在0.8半径的范围内找邻近点
            outrem.setMinNeighborsInRadius(50);       //设置查询点的邻近点集数小于2的删除  30
            outrem.filter (tempRgbCloud_radius);//执行条件滤波，存储结果到cloud_filtered
            //            t2 = QTime::currentTime();
            //            qDebug()<<"RadiusOutlierRemoval costs time = "<<  t1.msecsTo(t2) <<"ms"<<endl;

            /*************************以上为滤波处理部分************************************************************/
            mutex_3D.lock();
            tofImage = microQimage;
            intensityImage = macroQimage;
            pcl::copyPointCloud(tempRgbCloud_radius,pointCloudRgb);
            mutex_3D.unlock();
            /***************************************************************/

        }else{                      //不进行滤波
            mutex_3D.lock();
            tofImage = microQimage;
            intensityImage = macroQimage;
            pcl::copyPointCloud(tempRgbCloud,pointCloudRgb);
            mutex_3D.unlock();
        }


        //判断是否保存数据
        if(isSaveFlag)
        {

            bool flag = true;
            for(int i=0; i<19200; i++)
            {
                tofPeakToSave_string.append(tofPeakNum[i]);
                //tofPeakNum[i].clear();    //这句代码屏蔽以后 ，当有遗漏数据的时候，会使用上一帧的数据进行存储
            }
            emit saveTXTSignal(tofPeakToSave_string);
            tofPeakToSave_string.clear();

        }

        isShowPointCloud = true;

    }//以上为处理完整的一帧数据


    int lineIndex = spadNum/4 ;        //0,1,2,...29   宏像素的第几个 因为是4个spadNum为一组   四个像素点构成一个宏像素
    int InnerLineNum = (spadNum%4)/2;  //属于宏像素的第一行还是第二行； spadNum%4 = 0,1,2,3  0、1在第一行  2、3在第二行
    int tmpRow = lineIndex*2 + InnerLineNum;   //0,1,2,...,59
    if(0 == line_number)  //属于上半区
    {
        rowImg = 59 - tmpRow;          //0,...59
    }else                  //属于下半区
    {
        rowImg = 60 + tmpRow;       //660,..., 119
    }


    //    qDebug()<<"rowImg = "<<rowImg<<endl;


    for(int i=0; i<80; i++)    //每个包有80个点
    {
        colImg = i*2 + spadNum%2;                    //spad%2  0 2:第一列  1,3：第二列
        cloudIndex = rowImg*160 + colImg;           //在点云数据中的标号  0,..., 119*160+159
        int intensity;
        float tof,rawTof,after_pileup_tof,after_offset_tof;

        if(isTOF == false)   //设置一个不可能的值
        {
            tof = quint8(MyBuffer[4 + i * 4]) + ((quint8(MyBuffer[4 + i * 4 +1]))<<8);
            intensity = quint8(MyBuffer[4 + i * 4 + 2]) + ((quint8(MyBuffer[4 + i * 4 + 3 ]))<<8);
        }else
        {
            intensity = quint8(MyBuffer[4 + i * 4]) + ((quint8(MyBuffer[4 + i * 4 +1]))<<8);
            tof = quint8(MyBuffer[4 + i * 4 + 2]) + ((quint8(MyBuffer[4 + i * 4 + 3 ]))<<8);
        }


        /****************循坏赋值 取平均值的部分**************************************/
        for(int n=0; n<averageNum-1; n++)
        {
            lastTOF[n][cloudIndex] = lastTOF[n+1][cloudIndex];
        }
        lastTOF[averageNum-1][cloudIndex] = tof;

        if(haveIndex >averageNum)
        {
            float zeroNum = 0;
            haveIndex = averageNum+1;
            float allTof_100 = 0;
            for(int k=0; k<averageNum; k++)     //100帧取平均   ，如果有0的数据则不进行平均处理
            {
                if(lastTOF[k][cloudIndex] == 0)
                {
                    zeroNum = zeroNum+1;
                }
                allTof_100 += lastTOF[k][cloudIndex];
            }
            if(zeroNum != averageNum)

                tof = allTof_100/(averageNum-zeroNum);
            //           qDebug()<<"  tof = "<<tof;
        }
        /****************************************************/


        /*********************pileUp 以及 offset 校正部分******************************/
        rawTof = tof;
        if(true == is_pileUp_flag)
        {
            tof = pileUp_calibration(rawTof,intensity);
        }
        after_pileup_tof = tof;                   //pileUp处理后的tof
        tof = tof;
        tof = tof + tofOffsetArray[cloudIndex];   //offset校正以后的tof
        after_offset_tof = tof;
        /***************************************************/



        //设置TOF图像、强度图像的颜色
        QRgb tofColor,intenColor;
        int gainIndex_tof = tof*gainImage;
        gainIndex_tof = gainIndex_tof>0 ?gainIndex_tof:0;
        int gainIndex_intensity =intensity * gainImage;
        if(gainIndex_tof<1024 && gainIndex_tof>=0)
            tofColor = qRgb(colormap[gainIndex_tof * 3], colormap[gainIndex_tof * 3 + 1], colormap[gainIndex_tof * 3 + 2]);
        else
            tofColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);

        if(gainIndex_intensity<1024 && gainIndex_intensity>=0)
            intenColor = qRgb(colormap[gainIndex_intensity * 3], colormap[gainIndex_intensity * 3 + 1], colormap[gainIndex_intensity * 3 + 2]);
        else
            intenColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);


        if(colImg>=0 && colImg<160 && rowImg>=0 && rowImg<120)
        {
            microQimage.setPixel(colImg,rowImg,tofColor);         //TOF图像的赋值
            macroQimage.setPixel(colImg,rowImg,intenColor);       //强度图像的赋值

            /************鼠标点击处显示信息相关*************/
            mouseShowMutex.lock();
            mouseShowTOF[colImg][rowImg] = tof;
            mouseShowPEAK[colImg][rowImg] = intensity;
            mouseShowMutex.unlock();



            /************点云数据相关************/
            Lr =  (tof*tof - (5/1.55)*(5/1.55))/(2*(tof + (5/1.55)*sin(thetaArray[cloudIndex]))) ;      //
            Lr = Lr<0?0:Lr;
            temp_x = tof * sin(thetaArray[cloudIndex]) *LSB;
            temp_y = tof * cos(thetaArray[cloudIndex])*cos(betaArray[cloudIndex]) *LSB;
            temp_z = tof * cos(thetaArray[cloudIndex])*sin(betaArray[cloudIndex]) *LSB;
            if(tofOffsetArray[cloudIndex] ==tof)     //tof 原始值为0 处的位置会 显示成为一个弧度,所以将这里的三维点云坐标置为0
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }
            if(intensity <peakOffset)
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }
           mouseShowTOF[colImg][rowImg] = temp_y;     //改为显示深度信息 鼠标点击处

            if(isOnlyCenterShow_flag)  //这里是只显示中间光强度比较大的区域 显示行数：12-52   显示列数：78-178
            {
                if(rowImg<40|| rowImg>80 || colImg<40 || colImg>120)
                {
                    temp_x = 0;
                    temp_y = 0;
                    temp_z = 0;
                }
            }


            /*********文件保存相关*****************/
            if(isSaveFlag == true)
            {
                QString raw_tof_str = QString::number(rawTof);
                QString after_pileUp_tof_str = QString::number(after_pileup_tof);
                QString after_offset_tof_str = QString::number(after_offset_tof);
                QString peak_str = QString::number(intensity);
                QString x_str = QString::number(temp_x);
                QString y_str = QString::number(temp_y);
                QString z_str = QString::number(temp_z);
                tofPeakNum[cloudIndex] = raw_tof_str+","+after_pileUp_tof_str+","+after_offset_tof_str+","+peak_str+","+x_str+","+y_str+","+z_str+"\n";
            }


            /***************开启自动校正**************************/
            //如果开启自动校正，则计算4个点的100帧的tof均值
            // 59*160+79=9519        59*160+80=9520   60*160+79= 9679  60*160+80=9680
            if(true == isAutoCalibration_flag)
            {
                if(9519 == cloudIndex)
                {
                    vec_tof_1.push_back(tof);
                    if(vec_tof_1.size() == calibration_mean_num)
                    {
                        float mean_tof_1 = 0;
                        mean_tof_1 =  std::accumulate(std::begin(vec_tof_1),std::end(vec_tof_1),0.0)/calibration_mean_num;
                        calibrate_offset_slot(9519,mean_tof_1);
                        vec_tof_1.clear();
                    }
                }else if(9520 == cloudIndex)
                {
                    vec_tof_2.push_back(tof);
                    if(vec_tof_2.size() == calibration_mean_num)
                    {
                        float mean_tof_2 = 0;
                        mean_tof_2 = std::accumulate(std::begin(vec_tof_2),std::end(vec_tof_2),0.0)/calibration_mean_num;
                        calibrate_offset_slot(9520,mean_tof_2);
                        vec_tof_2.clear();

                    }
                }else if(9679 == cloudIndex)
                {
                    vec_tof_3.push_back(tof);
                    if(vec_tof_3.size() == calibration_mean_num)
                    {
                        float mean_tof_3 = 0;
                        mean_tof_3 = std::accumulate(std::begin(vec_tof_3),std::end(vec_tof_3),0.0)/calibration_mean_num;
                        calibrate_offset_slot(9679,mean_tof_3);
                        vec_tof_3.clear();

                    }
                }else if(9680 == cloudIndex)
                {
                    vec_tof_4.push_back(tof);
                    if(vec_tof_4.size() == calibration_mean_num)
                    {
                        float mean_tof_4 = 0;
                        mean_tof_4 = std::accumulate(std::begin(vec_tof_4),std::end(vec_tof_4),0.0)/calibration_mean_num;
                        calibrate_offset_slot(9680,mean_tof_4);
                        vec_tof_4.clear();

                    }
                }
            }
            /***************************************************************/

            QColor mColor = QColor(tofColor);
            r = mColor.red();
            g = mColor.green();
            b = mColor.blue();
            rgb = ((int)r << 16 | (int)g << 8 | (int)b);


            tempRgbCloud.points[cloudIndex].x = temp_x;
            tempRgbCloud.points[cloudIndex].y = temp_y;
            tempRgbCloud.points[cloudIndex].z = temp_z;
            tempRgbCloud.points[cloudIndex].rgb = *reinterpret_cast<float*>(&rgb);

            /***************统计均值 、方差相关***********************/
            if(statisticStartFlag == true)
            {
                //判断每个点已经储存的个数，如果已经超过设定的范围，则进行循环储存；
                int offset = tempStatisticPeakPoints[cloudIndex].size() - statisticFrameNumber;
                if(offset >= 0)
                {
                    tempStatisticTofPoints[cloudIndex].erase(tempStatisticTofPoints[cloudIndex].begin(),tempStatisticTofPoints[cloudIndex].begin() + offset + 1);
                    tempStatisticPeakPoints[cloudIndex].erase(tempStatisticPeakPoints[cloudIndex].begin(),tempStatisticPeakPoints[cloudIndex].begin() + offset + 1);
                }
                //向每个点的容器中添加一个新的点,完成循环存储
                tempStatisticTofPoints[cloudIndex].push_back(rawTof);
                tempStatisticPeakPoints[cloudIndex].push_back(intensity);
            }


            /******统计点云空间坐标最大值、最小值**********/
            xMax = (temp_x>xMax) ? temp_x : xMax;
            xMin = (temp_x<xMin) ? temp_x : xMin;
            yMax = (temp_y>yMax) ? temp_y : yMax;
            yMin = (temp_y<yMin) ? temp_y : yMin;
            zMax = (temp_z>zMax) ? temp_z : zMax;
            zMin = (temp_z<zMin) ? temp_z : zMin;

            //统计二维图像
            tofMax = (tof>tofMax) ? tof : tofMax;
            tofMin = (tof<tofMin) ? tof : tofMin;
            peakMax = (intensity>peakMax) ? intensity : peakMax;
            peakMin = (intensity<peakMin) ? intensity : peakMin;
        }
        else
            qDebug()<<QStringLiteral("给像素赋值时出现异常 imgrow=")<<rowImg<<"   imgCol = "<<colImg<<endl;

    }
    lastSpadNum = spadNum ;
}



//!
//! \brief DealUsb_msg::pileUp_calibration
//! \param srcTof
//! \param peak
//! \return
//!利用Peak值线性外插法可得对应校正量ΔTOF (Unit: mm)
float DealUsb_msg::pileUp_calibration(int srcTof,int peak)
{
    //    peak_cal = [0,	  	31,		50,		63,		72,		78,	     84,		90,	    92,		 94,	 96,	120];
    //    bias_cal = [0,	 36.19,    72.88,  106.2,  134.8,   158.6,   191,       234,    256,     285,    318,   318];

    float resTof = 0;
    float bias_tof = 0;
    float begin_tof,end_tof,offset_start,offset_end;

    if(peak<=31)           //[0 31] [0/31 36.19/31]
    {
        begin_tof = 0;
        end_tof = 31;
        offset_start = 0;
        offset_end = 36.19/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=50)    //(31 50] (36.19/31 72.88/31]
    {
        begin_tof = 31;
        end_tof = 50;
        offset_start = 36.19/31.0;
        offset_end = 72.88/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=63)   //(50,63] (72.88/31 106.2/31]
    {
        begin_tof = 50;
        end_tof = 63;
        offset_start = 72.88/31.0;
        offset_end = 106.2/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=72)   //(63,72] (106.2/31,134.8/31]
    {
        begin_tof = 63;
        end_tof = 72;
        offset_start = 106.2/31.0;
        offset_end = 134.8/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=78)   //(72,78] (134.8/31,158.6/31]
    {
        begin_tof = 72;
        end_tof = 78;
        offset_start = 134.8/31.0;
        offset_end = 158.6/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=84)  //(78,84] (158.6/31,191.0/31]
    {
        begin_tof = 78;
        end_tof = 84;
        offset_start = 158.6/31.0;
        offset_end = 191.0/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=90)  //(84,90] (191.0/31,234.0/31]
    {
        begin_tof = 84;
        end_tof = 90;
        offset_start = 191.0/31.0;
        offset_end = 234.0/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=92)  //(90,92] (234/31, 256/31)
    {
        begin_tof = 90;
        end_tof = 92;
        offset_start = 234.0/31.0;
        offset_end = 256.0/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=94)  //(92,94] (256/31, 285/31)
    {
        begin_tof = 92;
        end_tof = 94;
        offset_start = 256.0/31.0;
        offset_end = 285.0/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }else if(peak<=96) //(94,96] (285/31,318/31)
    {
        begin_tof = 94;
        end_tof = 96;
        offset_start = 285.0/31.0;
        offset_end = 318.0/31.0;
        bias_tof = (peak-begin_tof)*(offset_end-offset_start)/(end_tof-begin_tof) + offset_start;
        resTof = srcTof + bias_tof;
        return resTof;
    }
    else if(peak>96)   //>96   bias = 318
    {
        bias_tof = 318.0/31.0;
        resTof = srcTof + bias_tof;
        return resTof;
    }
}


//!
//! \brief autoCalibration_Dialog::on_startCalibration_pushButton_clicked
//! 1、开始校正
//! 2、发送信号到数据处理线程
//! 3、首先清空tofOffsetArray数组，设置为0
//! 4、设置校正的 flag = true
//! 5、把 59*160+79=9519        59*160+80=9520   60*160+79= 9679  60*160+80=9680 的y值传入给处理函数                         （31 32）/（127 128）
//! 6、数据处理函数首先判断够不够100帧，满100帧时，分别取y的均值，分别逆运算为resTof
//! 7、计算理论的realTof值，根据用户指定的距离(单位:m);
//! 8、offset = realTof - resTof
//! 9、写入本地文件，程序重新设置tofOffsetArray数组，isAutoCalibration_flagfalse
void  DealUsb_msg::start_autoCalibration_slot(int meters)
{
    for(int i=0;i<19200;i++)
    {
        tofOffsetArray[i] = 0;
    }
    calibration_real_dis = meters;
    isAutoCalibration_flag = true;

}

//!
//! \brief DealUsb_msg::calibrate_offset_slot
//!  计算校验的offset
//! 1、获取100帧数据的y坐标的均值（中间4个点的）
//! 2、根据公式反推出realTof
//! 3、offset = realTof - tof
//!
//!
//!
//!
//! 59*160+79=9519        59*160+80=9520   60*160+79= 9679  60*160+80=9680
//! temp_y = Lr *  cos(thetaArray[cloudIndex]) * cos(betaArray[cloudIndex]) * LSB;      // y坐标值
//! resTof = Lr +/-  sqrt(a^2 + Lr^2 + 2*a*b*sin0)
void DealUsb_msg::calibrate_offset_slot(int index,float mean_tof)
{


    if(9519 == index)
    {
        resTof_1 = mean_tof;
        float back_lr = calibration_real_dis/(cos(thetaArray[index]) * cos(betaArray[index]) * LSB);
        float a = 5.0/1.55;
        realTof_1 = back_lr + sqrt(a*a + back_lr*back_lr + 2*a*back_lr*sin(thetaArray[index]));
    }
    if(9520 == index)
    {
        resTof_2 = mean_tof;
        float back_lr = calibration_real_dis/(cos(thetaArray[index]) * cos(betaArray[index]) * LSB);
        float a = 5.0/1.55;
        realTof_2 = back_lr + sqrt(a*a + back_lr*back_lr + 2*a*back_lr*sin(thetaArray[index]));
    }
    if(9679 == index)
    {
        resTof_3 = mean_tof;
        float back_lr = calibration_real_dis/(cos(thetaArray[index]) * cos(betaArray[index]) * LSB);
        float a = 5.0/1.55;
        realTof_3 = back_lr + sqrt(a*a + back_lr*back_lr + 2*a*back_lr*sin(thetaArray[index]));
    }
    if(9680 == index)
    {
        resTof_4 = mean_tof;
        float back_lr = calibration_real_dis/(cos(thetaArray[index]) * cos(betaArray[index]) * LSB);
        float a = 5.0/1.55;
        realTof_4 = back_lr + sqrt(a*a + back_lr*back_lr + 2*a*back_lr*sin(thetaArray[index]));
    }


    ishave_Four++;
    if(4 == ishave_Four)   //此时说明中间区域的四个点都已经计算完均值
    {
        float mean_resTof = (resTof_1+ resTof_2+resTof_3+resTof_4)/4.0;
        float mean_realTof = (realTof_1+realTof_2+realTof_3+realTof_4)/4.0;
        int mean_offset  = int(mean_realTof - mean_resTof + 0.5f) ;   //四舍五入

//        qDebug()<<"resTof_1="<<resTof_1<<"  resTof_2="<<resTof_2<<"  resTof_3="<<resTof_3<<"  resTof_4="<<resTof_4;
//        qDebug()<<"realTof_1="<<realTof_1<<"  realTof_2="<<realTof_2<<"  realTof_3="<<realTof_3<<"  realTof_4="<<realTof_4;


        qDebug()<<"mean_resTof = "<<mean_resTof;
        qDebug()<<"mean_realTof = "<<mean_realTof;
        qDebug()<<"mean_offset = "<<mean_offset;

        //修改偏移的offset的值
        QFile file("tofOffsetArray.txt");
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream out(&file);
        QString text = QString::number(mean_offset);
        for(int i=0; i<19200; i++)
        {
            tofOffsetArray[i] = mean_offset;
            out<<text.toLocal8Bit()<<endl;
        }

        file.close();

        isAutoCalibration_flag = false;
        ishave_Four = 0;
        QString msg = "raw_tof="+QString::number(mean_resTof)+",dst_tof="+QString::number(mean_realTof)+",offset="+QString::number(mean_offset);
        emit send_cali_success_signal(msg);   //发送给设置自动校准的界面
    }


}



/********************************* **************** ****************  read local_file ************************ **************** **************** **************** *****************************/

void DealUsb_msg::playLocalFile_slot(QString sPath)
{
    filePath = sPath;

    if( NULL == localFile_timer)
    {
        localFile_timer = new QTimer();
        connect(localFile_timer,SIGNAL(timeout()),this,SLOT(readLocalPCDFile()));
    }
    fileIndex = 1;
    localFile_timer->start(80);

}

void DealUsb_msg::readLocalPCDFile()
{
    QString fileName;
    QString line[20000];
    QStringList tofPeakList;
    int imgRow,imgCol;



    fileName = filePath + QString::number(fileIndex)+".txt";
    fileIndex++;

    QFile file(fileName);

    int countNum = 0;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            line[countNum] = in.readLine();
            countNum++;
        }
        file.close();
    }else
    {
        qDebug()<<"read file error!"<<endl;
        //            localFile_timer->stop();
        fileIndex = 1;
        return;
    }
    for(int i=0; i<countNum; i++)            //去掉空的数据
    {
        int tof,intensity;
        if(line[i].isEmpty())
            continue;

        tofPeakList = line[i].split(",");
        if(tofPeakList.size()<2)
            return;

        if(isTOF)
        {
            tof = tofPeakList[0].toInt();
            intensity = tofPeakList[1].toInt();
        }else
        {
            intensity = tofPeakList[0].toInt();
            tof = tofPeakList[1].toInt();
        }



        //行列以及颜色传递给图像
        imgRow = i%160;
        imgCol = i/160;
        cloudIndex = i;      //在点云数据中的标号

        //            qDebug()<<"imgRow="<<imgRow<<"  imgCol="<<imgCol<<endl;

        //设置TOF图像、强度图像的颜色
        QRgb tofColor,intenColor;
        int gainIndex_tof = tof*gainImage;
        int gainIndex_intensity =intensity * gainImage;

        //        int gainIndex_tof = tof *0.5;
        //        int gainIndex_intensity = intensity * 0.5;

        if(gainIndex_tof<1024 && gainIndex_tof>=0)
            tofColor = qRgb(colormap[gainIndex_tof * 3], colormap[gainIndex_tof * 3 + 1], colormap[gainIndex_tof * 3 + 2]);
        else
            tofColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);

        if(gainIndex_intensity<1024 && gainIndex_intensity>=0)
            intenColor = qRgb(colormap[gainIndex_intensity * 3], colormap[gainIndex_intensity * 3 + 1], colormap[gainIndex_intensity * 3 + 2]);
        else
            intenColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);


        if(imgRow>=0 && imgRow<160 && imgCol>=0 && imgCol<120)
        {
            microQimage.setPixel(imgRow,imgCol,tofColor);         //TOF图像的赋值
            macroQimage.setPixel(imgRow,imgCol,intenColor);       //强度图像的赋值

            /************鼠标点击处显示信息相关*************/
            mouseShowMutex.lock();
            mouseShowTOF[imgRow][imgCol] = tof;
            mouseShowPEAK[imgRow][imgCol] = intensity;
            mouseShowMutex.unlock();


            /************点云数据相关************/
            //获取三维坐标

            //            temp_x = tof * x_Weight[cloudIndex] * LSB;
            //            temp_y = tof * y_Weight[cloudIndex] * LSB;
            //            temp_z = tof * z_Weight[cloudIndex] * LSB;

            temp_x = tof * sin(thetaArray[cloudIndex]) *LSB;
            temp_y = tof * cos(thetaArray[cloudIndex])*cos(betaArray[cloudIndex]) *LSB;
            temp_z = tof * cos(thetaArray[cloudIndex])*sin(betaArray[cloudIndex]) *LSB;

            QColor mColor = QColor(tofColor);
            r = mColor.red();
            g = mColor.green();
            b = mColor.blue();
            rgb = ((int)r << 16 | (int)g << 8 | (int)b);


            tempRgbCloud.points[cloudIndex].x = temp_x;
            tempRgbCloud.points[cloudIndex].y = temp_y;
            tempRgbCloud.points[cloudIndex].z = temp_z;
            tempRgbCloud.points[cloudIndex].rgb = *reinterpret_cast<float*>(&rgb);

            //            qDebug()<<" cloudIndex = "<<cloudIndex<<endl;

            /***************统计均值 、方差相关***********************/
            if(statisticStartFlag == true)
            {
                //判断每个点已经储存的个数，如果已经超过设定的范围，则进行循环储存；
                int offset = tempStatisticPeakPoints[cloudIndex].size() - statisticFrameNumber;
                if(offset >= 0)
                {
                    tempStatisticTofPoints[cloudIndex].erase(tempStatisticTofPoints[cloudIndex].begin(),tempStatisticTofPoints[cloudIndex].begin() + offset + 1);
                    tempStatisticPeakPoints[cloudIndex].erase(tempStatisticPeakPoints[cloudIndex].begin(),tempStatisticPeakPoints[cloudIndex].begin() + offset + 1);
                }
                //向每个点的容器中添加一个新的点,完成循环存储
                tempStatisticTofPoints[cloudIndex].push_back(tof);
                tempStatisticPeakPoints[cloudIndex].push_back(intensity);
            }


            /******统计点云空间坐标最大值、最小值**********/
            xMax = (temp_x>xMax) ? temp_x : xMax;
            xMin = (temp_x<xMin) ? temp_x : xMin;
            yMax = (temp_y>yMax) ? temp_y : yMax;
            yMin = (temp_y<yMin) ? temp_y : yMin;
            zMax = (temp_z>zMax) ? temp_z : zMax;
            zMin = (temp_z<zMin) ? temp_z : zMin;

            //统计二维图像
            tofMax = (tof>tofMax) ? tof : tofMax;
            tofMin = (tof<tofMin) ? tof : tofMin;
            peakMax = (intensity>peakMax) ? intensity : peakMax;
            peakMin = (intensity<peakMin) ? intensity : peakMin;
        }
        else
            qDebug()<<QStringLiteral("给像素赋值时出现异常 imgrow=")<<imgRow<<"   imgCol = "<<imgCol<<endl;

    }  //一帧数据已经读取完成




    //统计信息相关的 ，将统计信息的容器赋值给全局变量
    if(statisticStartFlag)
    {
        statisticMutex.lock();
        allStatisticTofPoints = tempStatisticTofPoints;
        allStatisticPeakPoints = tempStatisticPeakPoints;
        statisticMutex.unlock();
    }


    //向主线程中发送最大值、最小值等统计信息
    emit staticValueSignal(tofMin,tofMax,peakMin,peakMax,xMin,xMax,yMin,yMax,zMin,zMax);
    //重置变量
    tofMin = 10000;
    tofMax = -10000;
    peakMin = 10000;
    peakMax = -10000;
    xMin = 10000;
    xMax = -10000;
    yMin = 10000;
    yMax = -10000;
    zMin = 10000;
    zMax = -10000;






    // 1、将滤波功能放到这里进行实现，
    // 2、将滤波后的三维点云 同步到二维图像
    if(true == isFilterFlag)
    {
        /*******************开启滤波功能*********************************/
        //先用直通滤波把所有零点重复的零点过滤掉
        //        pcl::PassThrough<pcl::PointXYZRGB> pass;                      //创建滤波器对象
        //        pass.setInputCloud(tempRgbCloud.makeShared());                //设置待滤波的点云
        //        pass.setFilterFieldName("y");                                 //设置在Z轴方向上进行滤波
        //        pass.setFilterLimits(0, 0.10);                                //设置滤波范围(从最高点向下0.10米去除)
        //        pass.setFilterLimitsNegative(true);                           //保留
        //        pass.filter(tempRgbCloud_pass);                                   //滤波并存储
        //        if(tempRgbCloud_pass.size()<1)
        //                return;

        //  统计
        tempRgbCloud_radius.clear();
        pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> outrem(true);
        outrem.setInputCloud(tempRgbCloud.makeShared());
        outrem.setMeanK(40);
        outrem.setStddevMulThresh(0.25);
        //40  0.1 不见前面噪点
        outrem.filter(tempRgbCloud_radius);
        int len = outrem.getRemovedIndices()->size();
        qDebug()<<"after filter the points'Number = "<<tempRgbCloud_radius.size()<<endl;


        //        tempRgbCloud_radius.resize(0);
        //        pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> outrem(true);      //设置为true以后才能获取到滤出的噪点的 个数以及点的序列号
        //        outrem.setInputCloud(tempRgbCloud.makeShared());              //设置输入点云
        //        outrem.setRadiusSearch(0.25);              //设置在0.8半径的范围内找邻近点
        //        outrem.setMinNeighborsInRadius(15);       //设置查询点的邻近点集数小于2的删除  30
        //        outrem.filter (tempRgbCloud_radius);//执行条件滤波，存储结果到cloud_filtered
        //        int len = outrem.getRemovedIndices()->size();

        /*************************以上为滤波处理部分************************************************************/

        /***********************接下来 根据点云的序号 去除二维图像中的噪声************************/

        mutex_3D.lock();
        tofImage = microQimage;
        intensityImage = macroQimage;
        pcl::copyPointCloud(tempRgbCloud_radius,pointCloudRgb);
        mutex_3D.unlock();
        /***************************************************************/

    }else{                      //不进行滤波
        mutex_3D.lock();
        tofImage = microQimage;
        intensityImage = macroQimage;
        pcl::copyPointCloud(tempRgbCloud,pointCloudRgb);
        mutex_3D.unlock();
    }
    isShowPointCloud = true;
}





