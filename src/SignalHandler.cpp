#include "SignalHandler.h"

// 构造函数，自动设置信号处理器
SignalHandler::SignalHandler() {
    setupSignalHandlers();
}

// 析构函数（可选）
SignalHandler::~SignalHandler() {
    // 可以在这里做一些清理工作（如果需要）
}

// 信号处理函数的实现
void SignalHandler::signalHandler(int signal) {
    void *array[10];
    size_t size;

    // 获取调用栈上的返回地址
    size = backtrace(array, 10);

    // 打印错误信号和调用栈
    std::cerr << "Error: signal " << signal << ":\n";
    backtrace_symbols_fd(array, size, STDERR_FILENO);

    exit(1);
}

// 注册信号处理器的实现
void SignalHandler::setupSignalHandlers() {
    signal(SIGSEGV, SignalHandler::signalHandler);  // 段错误
    signal(SIGABRT, SignalHandler::signalHandler);  // abort信号
    signal(SIGFPE, SignalHandler::signalHandler);   // 算术错误，如除以零
    signal(SIGILL, SignalHandler::signalHandler);   // 非法指令
    signal(SIGBUS, SignalHandler::signalHandler);   // 总线错误
}
