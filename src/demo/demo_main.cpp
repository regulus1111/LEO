#include <tchar.h>
#include "demo_main.h"
#include "AgConnect.h"
#include "AgUtUnicode.h"

void printHelloWorld(){
    // 初始化一个连接
    AgConInit(NULL);

    // 建立连接
    char        *connection      = NULL;
    static char  connectName[256] = _T("localhost:5001");
    AgConOpenSTK(reinterpret_cast<int **>(&connection), 0, reinterpret_cast<const int *>(connectName));

    // 连接配置
    AgConSetProperties(reinterpret_cast<int *>(connection), (AgCConVerboseOn | AgCConAckOn));
    // 设置超时。STK有些操作会比较耗时，如果不设置AgCIOWait，可能会超时导致连接出错
    AgConSetTimeout(reinterpret_cast<int *>(connection), AgCIOWait);

    // 用于接收STK返回的数据
    AgTConReturnInfo returnInfo;
    // 构造命令：创建一个名为my_scenario的场景
    char  *cmd_str = "New / Scenario my_scenario";
    /* 用函数AgConProcessSTKCmd执行命令，返回值在returnInfo。
    *  重点关注returnInfo的两个成员，returnInfo.numEntries和returnInfo.returnList[i]：
    *     returnInfo.numEntries表示返回的字符串的个数
    *     returnInfo.returnList[i]表示第i个字符串
    */

    AgConProcessSTKCmd(reinterpret_cast<int *>(connection), reinterpret_cast<const int *>(cmd_str), &returnInfo);

    // 清空returnInfo
    AgConCleanupReturnInfo ( &returnInfo );
    // 关闭连接
    AgConCloseSTK(reinterpret_cast<int **>(&connection));
    //
    AgConShutdownConnect();

}