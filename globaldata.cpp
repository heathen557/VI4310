#include"globaldata.h"

using namespace std;
QMutex mutex_3D;

/*保存用到的标识*/
bool isSaveFlag;        //是否进行存储
QString saveFilePath;   //保存的路径  E:/..../.../的形式
int saveFileIndex;      //文件标号；1作为开始

/*******统计信息相关的变量***********/
QMutex statisticMutex;
vector<vector<int>> allStatisticTofPoints;   //用于统计 均值和方差的 容器  TOF
vector<vector<int>> allStatisticPeakPoints;   //用于统计 均值和方差的 容器  TOF
