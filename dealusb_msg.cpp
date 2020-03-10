#include "dealusb_msg.h"



extern QMutex mutex_3D;  //3D点云/2D传输的互斥锁
QImage tofImage;
QImage intensityImage;
extern pcl::PointCloud<pcl::PointXYZRGB> pointCloudRgb;
extern bool isShowPointCloud;  //是否有点云数据 ，有的话显示否则不显示

QMutex mouseShowMutex;
float mouseShowTOF[256][64];
int mouseShowPEAK[256][64];

/*保存用到的标识*/
extern bool isSaveFlag;        //是否进行存储
extern QString saveFilePath;   //保存的路径  E:/..../.../的形式
extern int saveFileIndex;      //文件标号；1作为开始



/*******统计信息相关的变量***********/
extern QMutex statisticMutex;
extern vector<vector<int>> allStatisticTofPoints;   //用于统计 均值和方差的 容器  TOF
extern vector<vector<int>> allStatisticPeakPoints;   //用于统计 均值和方差的 容器  TOF



DealUsb_msg::DealUsb_msg(QObject *parent) : QObject(parent),
    microQimage(256,64, QImage::Format_RGB32),macroQimage(256,64, QImage::Format_RGB32)
{

    //    pointCloudRgb.width = 16384;
    //    pointCloudRgb.height = 1;
    //    pointCloudRgb.resize(pointCloudRgb.width);

    tempRgbCloud.width = 16384;
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
    for(int i=0; i<16384; i++)
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

//260个字节的 解析协议的槽函数
void DealUsb_msg::recvMsgSlot(QByteArray array)
{
    int ret;
    char *MyBuffer;


    MyBuffer = array.data();
    int imgRow,imgCol;
    int spadNum = (quint8)(MyBuffer[0]) +  (((quint8)(MyBuffer[1]))<<8);
    int line_number = (quint8)(MyBuffer[2]) +  (((quint8)(MyBuffer[3]))<<8);
//     qDebug()<<"spadNum = "<<spadNum<<"  line_number = "<<line_number<<endl;     //打包发布会导致打包发布后的程序卡顿

    if(line_number!=0  && ( (lastLineNum+1) != line_number) )
    {
        qDebug()<<"lastLineNum="<<lastLineNum <<"   "<<line_number<<endl;
    }
    lastLineNum = line_number;


    if(spadNum==0 && lastSpadNum==7)  //此时说明上一帧数据已经接收完毕，把整帧数据付给其他线程，供其显示，数据可以显示了
    {

        haveIndex++;    //满足 足够一帧的数据了


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

        }else
        {                      //不进行滤波
            mutex_3D.lock();
            tofImage = microQimage;
            intensityImage = macroQimage;
            pcl::copyPointCloud(tempRgbCloud,pointCloudRgb);
            mutex_3D.unlock();
        }


        //判断是否保存数据部分
        if(isSaveFlag)
        {

            bool flag = true;
            for(int i=0; i<16384; i++)
            {
                if(tofPeakNum[i].isEmpty())
                {
                    flag =false;
                    tofPeakNum[i] = QString("%1").arg(0, 5, 10, QChar('0')).append(",").append(QString("%1").arg(0, 5, 10, QChar('0'))).append("\n");    //把没有接收到的数据设置为0 并且保存  2019-10-16 华为需求更改
                }
                tofPeakToSave_string.append(tofPeakNum[i]);
                // tofPeakNum[i].clear();   //因为存在丢数据的问题，所以这里不置为0，当前帧丢失某个数据时，则保留上一帧的数据
            }
            emit saveTXTSignal(tofPeakToSave_string);
            tofPeakToSave_string.clear();

        }





        isShowPointCloud = true;

        //        tempRgbCloud.clear();
    }  //以上为处理完整的一帧数据*********************************************************



    int line_offset,row_offset;
    if(lineSelect)
    {
        line_offset = spadNum / 2;           //取值 0 1 2 3 ；
        row_offset = (spadNum+1) % 2;      //表示是在第一行 还是在第二行
    }else
    {                                             //这种方式应该是对的
        line_offset = spadNum / 2;           //取值 0 1 2 3 ；
        row_offset = (spadNum) % 2;      //表示是在第一行 还是在第二行
    }



    for(int i=0; i<64; i++)
    {

        imgRow = i * 4 + line_offset;
        imgCol = line_number * 2 + row_offset;
        cloudIndex = imgCol*256+imgRow;      //在点云数据中的标号
        int tof,intensity ,tmpTof;     //tof：是用来做显示（二维、三维、最大最小值）（因为涉及到要进行校正）    tmpTof：用来存储本地数据 以及统计界面时候用

        if(isTOF == false)   //设置一个不可能的值
        {
            tof = quint8(MyBuffer[4 + i * 4]) + ((quint8(MyBuffer[4 + i * 4 +1]))<<8);
            intensity = quint8(MyBuffer[4 + i * 4 + 2]) + ((quint8(MyBuffer[4 + i * 4 + 3 ]))<<8);
        }else
        {
            intensity = quint8(MyBuffer[4 + i * 4]) + ((quint8(MyBuffer[4 + i * 4 +1]))<<8);
            tof = quint8(MyBuffer[4 + i * 4 + 2]) + ((quint8(MyBuffer[4 + i * 4 + 3 ]))<<8);
        }



        /*******************************************************************************/

        //循环赋值  滑动平均滤波
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
        /************************************************************/


        //这个是和90度直角矫正相关的  减去一个偏移量70  ；把处理之后小于0的值都过滤掉
//      tof = tof -70;
        tmpTof = tof;    //原始的tof值  ，没有做角度矫正相关的操作

//      tof =tof +32;
        tof = tof + tofOffsetArray[cloudIndex];

        //设置TOF图像、强度图像的颜色
        QRgb tofColor,intenColor;
        int gainIndex_tof = tof*gainImage;
        gainIndex_tof = gainIndex_tof>0 ?gainIndex_tof:0;
        int gainIndex_intensity =intensity * gainImage;
        gainIndex_intensity = gainIndex_intensity>0?gainIndex_intensity:0;
        if(gainIndex_tof<1024 && gainIndex_tof>=0)
            tofColor = qRgb(colormap[gainIndex_tof * 3], colormap[gainIndex_tof * 3 + 1], colormap[gainIndex_tof * 3 + 2]);
        else
            tofColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);

        if(gainIndex_intensity<1024 && gainIndex_intensity>=0)
            intenColor = qRgb(colormap[gainIndex_intensity * 3], colormap[gainIndex_intensity * 3 + 1], colormap[gainIndex_intensity * 3 + 2]);
        else
            intenColor = qRgb(colormap[1023 * 3], colormap[1023 * 3 + 1], colormap[1023 * 3 + 2]);

        //Tof 转换为2D图像 3D点云 部分
        if(imgRow>=0 && imgRow<256 && imgCol>=0 && imgCol<64)
        {
            microQimage.setPixel(imgRow,imgCol,tofColor);         //TOF图像的赋值
            macroQimage.setPixel(imgRow,imgCol,intenColor);       //强度图像的赋值

            /************鼠标点击处显示信息相关*************/
            mouseShowMutex.lock();
            mouseShowTOF[imgRow][imgCol] = tof;
            mouseShowPEAK[imgRow][imgCol] = intensity;
            mouseShowMutex.unlock();

            /*********文件保存相关*****************/
            if(isSaveFlag == true)
            {
                tofPeakNum[cloudIndex] = QString("%1").arg(tmpTof, 5, 10, QChar('0')).append(",").append(QString("%1").arg(intensity, 5, 10, QChar('0'))).append("\n");

            }


            /************点云数据相关************/
            //这部分是tof到三维点云的转换
            Lr =  (tof*tof - (5/1.55)*(5/1.55))/(2*(tof + (5/1.55)*sin(thetaArray[cloudIndex]))) ;      //
            Lr = Lr<0?0:Lr;
            temp_x = Lr *  sin(thetaArray[cloudIndex]) * LSB;                                          //  x坐标值
            temp_z = Lr *  cos(thetaArray[cloudIndex]) * sin(betaArray[cloudIndex]) * LSB;            //  y坐标值
            temp_y = Lr *  cos(thetaArray[cloudIndex]) * cos(betaArray[cloudIndex]) * LSB -0.2;      // z坐标值

            if(tofOffsetArray[cloudIndex] ==tof)     //tof 原始值为0 处的位置会 显示成为一个弧度,所以将这里的三维点云坐标置为0
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }
            if(intensity <peakOffset)    //根据peak值进行滤波处理数据
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }

            mouseShowTOF[imgRow][imgCol] = temp_y;

//          //这里是只显示中间光强度比较大的区域 显示行数：12-52   显示列数：78-178
            if(isOnlyCenterShow_flag)
            {
                if(imgCol<12 || imgCol>52 || imgRow<78 || imgRow>178)
                {
                    temp_x = 0;
                    temp_y = 0;
                    temp_z = 0;
                }
            }
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
                tempStatisticTofPoints[cloudIndex].push_back(tmpTof);
                tempStatisticPeakPoints[cloudIndex].push_back(intensity);
            }


            /******统计点云空间坐标最大值、最小值**********/
            xMax = (temp_x>xMax) ? temp_x : xMax;
            xMin = (temp_x<xMin) ? temp_x : xMin;
            yMax = (temp_y>yMax) ? temp_y : yMax;
            yMin = (temp_y<yMin) ? temp_y : yMin;
            zMax = (temp_z>zMax) ? temp_z : zMax;
            zMin = (temp_z<zMin) ? temp_z : zMin;

            //统计二维图像 tof/peak 的最大值 最小值
            tofMax = (tof>tofMax) ? tof : tofMax;
            tofMin = (tof<tofMin) ? tof : tofMin;
            peakMax = (intensity>peakMax) ? intensity : peakMax;
            peakMin = (intensity<peakMin) ? intensity : peakMin;
        }
        else
            qDebug()<<QStringLiteral("给像素赋值时出现异常 imgrow=")<<imgRow<<"   imgCol = "<<imgCol<<endl;

    }

    lastSpadNum = spadNum ;
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
    //    int fileIndex = 1;
    QString fileName;
    QString line[17000];
    QStringList tofPeakList;
    int imgRow,imgCol;


    haveIndex++;

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
        qDebug()<<"read local file error!,filename = "<<fileName<<endl;
        //            localFile_timer->stop();
        fileIndex = 1;
        return;
    }
    for(int i=0; i<16384; i++)            //去掉空的数据
    {
        int tof,intensity,tmpTof;   //tof:用来显示（二维、三维、鼠标点击、最大最小值）,因为涉及到要减去一个偏移；     tmpTof：用来存储原始数据、以及统计界面的显示
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

        //循环赋值
        for(int n=0; n<averageNum-1; n++)
        {
            lastTOF[n][i] = lastTOF[n+1][i];
        }
        lastTOF[averageNum-1][i] = tof;

        if(haveIndex >averageNum)
        {
            float zeroNum = 0;
            haveIndex = averageNum+1;
            float allTof_100 = 0;
            for(int k=0; k<averageNum; k++)     //100帧取平均   ，如果有0的数据则不进行平均处理
            {
                if(lastTOF[k][i] == 0)
                {
                    zeroNum = zeroNum+1;
                }
                allTof_100 += lastTOF[k][i];
            }
            if(zeroNum != averageNum)

           tof = allTof_100/(averageNum-zeroNum);
        }


        tmpTof = tof;
//        tof = tof - 70;

        tof = tof + tofOffsetArray[i];
//        qDebug()<<" tofOffsetArray[cloudIndex] "<<cloudIndex<<"      "<<tofOffsetArray[cloudIndex];
//        tof = tof<0? 0:tof;

        //行列以及颜色传递给图像
        imgRow = i%256;
        imgCol = i/256;
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


        if(imgRow>=0 && imgRow<256 && imgCol>=0 && imgCol<64)
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


            Lr =  (tof*tof - (5/1.55)*(5/1.55))/(2*(tof + (5/1.55)*sin(thetaArray[cloudIndex]))) ;      //
            Lr = Lr<0?0:Lr;
            temp_x = Lr * sin(thetaArray[cloudIndex]) * LSB ;                                   //  x坐标值
            temp_z = Lr *  cos(thetaArray[cloudIndex]) * sin(betaArray[cloudIndex]) * LSB;     //  y坐标值
            temp_y = Lr *  cos(thetaArray[cloudIndex]) * cos(betaArray[cloudIndex]) * LSB - 0.2;      // z坐标值


            if(isOnlyCenterShow_flag)
            {
                if(imgCol<12 || imgCol>52 || imgRow<78 || imgRow>178)
                {
                    temp_x = 0;
                    temp_y = 0;
                    temp_z = 0;
                }
            }

            mouseShowTOF[imgRow][imgCol] = temp_y;

            QColor mColor = QColor(tofColor);
            r = mColor.red();
            g = mColor.green();
            b = mColor.blue();
            rgb = ((int)r << 16 | (int)g << 8 | (int)b);


            if(intensity < peakOffset)
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }

            if(tofOffsetArray[cloudIndex] == tof)
            {
                temp_x = 0;
                temp_z = 0;
                temp_y = 0;
            }

            tempRgbCloud.points[cloudIndex].x = temp_x;
            tempRgbCloud.points[cloudIndex].y = temp_y;
            tempRgbCloud.points[cloudIndex].z = temp_z;
            tempRgbCloud.points[cloudIndex].rgb = *reinterpret_cast<float*>(&rgb);

//            qDebug()<<" cloudIndex = "<<cloudIndex<<endl;




            /*********文件保存相关*****************/
            if(isSaveFlag == true)
            {
//                tofPeakNum[cloudIndex] = QString::number(tof).append(", ").append(QString::number(intensity)).append("\n");
                tofPeakNum[cloudIndex] = QString("%1").arg(tmpTof, 5, 10, QChar('0')).append(",").append(QString("%1").arg(intensity, 5, 10, QChar('0'))).append("\n");
            }else
            {
                tofPeakNum[cloudIndex].clear();

            }




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
                tempStatisticTofPoints[cloudIndex].push_back(tmpTof);
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




    /*********************test saveFile HUAWEI ***********************************************/
    haveIndex++;

    /**********************************************************************/
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
//        //先用直通滤波把所有零点重复的零点过滤掉
//        pcl::PassThrough<pcl::PointXYZRGB> pass;                      //创建滤波器对象
//        pass.setInputCloud(tempRgbCloud.makeShared());                //设置待滤波的点云
//        pass.setFilterFieldName("y");                                 //设置在Z轴方向上进行滤波
//        pass.setFilterLimits(0, 0.10);                                //设置滤波范围(从最高点向下0.10米去除)
//        pass.setFilterLimitsNegative(true);                           //保留
//        pass.filter(tempRgbCloud_pass);                                   //滤波并存储
//        if(tempRgbCloud_pass.size()<1)
//                return;

//        tempRgbCloud_radius.clear();
//        pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> outrem(true);
//        outrem.setInputCloud(tempRgbCloud_pass.makeShared());
//        outrem.setMeanK(10);
//        outrem.setStddevMulThresh(0.25);
//        //40  0.1 不见前面噪点
//        outrem.filter(tempRgbCloud_radius);
//        int len = outrem.getRemovedIndices()->size();




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


        /*************************以上为滤波处理部分************************************************************/


        mutex_3D.lock();
        tofImage = microQimage;
        intensityImage = macroQimage;

        pcl::copyPointCloud(tempRgbCloud_radius,pointCloudRgb);
        mutex_3D.unlock();


        /***************************************************************/

    }else
    {                      //不进行滤波
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
        for(int i=0; i<16384; i++)
        {
            if(tofPeakNum[i].isEmpty())
            {
                flag =false;
                tofPeakNum[i] = QString("%1").arg(0, 5, 10, QChar('0')).append(",").append(QString("%1").arg(0, 5, 10, QChar('0'))).append("\n");   //把没有接收到的数据设置为0 并且保存  2019-10-16 华为需求更改
            }
            tofPeakToSave_string.append(tofPeakNum[i]);
            tofPeakNum[i].clear();
        }

        emit saveTXTSignal(tofPeakToSave_string);
        tofPeakToSave_string.clear();

    }

    isShowPointCloud = true;
}





