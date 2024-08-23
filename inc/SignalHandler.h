#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <iostream>
#include <signal.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>

class SignalHandler {
public:
    // 构造函数，设置信号处理器
    SignalHandler();
    
    // 析构函数（可选）
    ~SignalHandler();

private:
    // 信号处理函数
    static void signalHandler(int signal);

    // 注册信号处理函数
    void setupSignalHandlers();
};

#endif // SIGNALHANDLER_H
