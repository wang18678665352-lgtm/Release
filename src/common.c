#include "common.h"

#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif

/**
 * @brief 初始化终端的字符编码
 * 将Windows CMD的活动代码页切换为GBK(936)，防止出现中文字符丢失和乱码。
 * 只有在Windows平台下才编译并执行此逻辑。
 */
void init_console_encoding(void) {
#ifdef _WIN32
    SetConsoleCP(936);        // 设置输入控制台的活动代码页为 GBK
    SetConsoleOutputCP(936);  // 设置输出控制台的活动代码页为 GBK
    setlocale(LC_ALL, "chs"); // 设置C标准库的本地化策略为简体中文
#endif
}

/**
 * @brief 清空标准输入缓冲区
 * 防止遗留的换行符或非法字符（如用户输入字母而程序期望数字）干扰后续的 scanf 读取。
 */
void clear_input_buffer(void) {
    int c;
    // 循环读取直到遇到换行符或文件结束符
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief 暂停终端显示
 * 提示用户按回车键继续，用于结果展示后的界面停留，避免清屏过快。
 */
void pause_screen(void) {
    printf("\n按回车键继续...");
    clear_input_buffer(); // 清除可能残留的回车
    getchar();            // 等待用户敲击回车
}

/**
 * @brief 获取并在范围内校验用户菜单选择
 * @param min 允许的最小序号
 * @param max 允许的最大序号
 * @return 合法返回选择的数字，非法返回 ERROR_INVALID_INPUT (-1)
 */
int get_menu_choice(int min, int max) {
    int choice;
    printf("\n请选择: ");
    // 检查scanf是否成功读取了一个整数
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer(); // 如果输入非数字，清除错误输入
        return ERROR_INVALID_INPUT;
    }
    clear_input_buffer(); // 清除数字后面的换行符
    
    // 判断输入是否在指定范围内
    if (choice < min || choice > max) {
        return ERROR_INVALID_INPUT;
    }
    return choice;
}

/**
 * @brief 获取系统当前时间格式化字符串
 * @param buffer 接收时间串的数组
 * @param buffer_size 数组容量
 * @note 格式化为 "YYYY-MM-DD HH:MM:SS"
 */
void get_current_time(char *buffer, int buffer_size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now); // 转换为本地时间结构
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info); // 格式化时间字符串
}

/**
 * @brief 生成业务相关的唯一标识符(ID)
 * @param buffer 接收ID的数组
 * @param buffer_size 数组容量
 * @param prefix 业务前缀（例如 "P" 代表患者, "D" 代表医生）
 * @note 格式为：前缀 + 年月日时分，例如 "P202310241030"
 */
void generate_id(char *buffer, int buffer_size, const char *prefix) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    // 拼接前缀和时间戳构成唯一ID
    snprintf(buffer, buffer_size, "%s%04d%02d%02d%02d%02d", 
             prefix, 
             tm_info->tm_year + 1900, 
             tm_info->tm_mon + 1, 
             tm_info->tm_mday,
             tm_info->tm_hour, 
             tm_info->tm_min);
}