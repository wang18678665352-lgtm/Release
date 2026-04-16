#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief 系统角色定义宏
 * 用于全局权限校验和模块路由分发
 */
#define ROLE_ADMIN  "admin"     // 系统管理员角色，拥有所有基础数据配置权限
#define ROLE_DOCTOR "doctor"    // 医生角色，负责接诊、开处方、病房管理等
#define ROLE_PATIENT "patient"  // 患者角色，拥有挂号、查询进度、查询档案等权限

/**
 * @brief 缓冲区最大长度限制定义
 * 防止缓冲区溢出攻击，规范各个字段的最大存储尺寸
 */
#define MAX_USERNAME 50         // 登录账户名最大长度
#define MAX_PASSWORD 50         // 密码最大长度
#define MAX_NAME 100            // 真实姓名（如患者姓名、医生姓名）最大长度
#define MAX_ID 20               // 唯一标识符（如患者ID、挂号ID）最大长度
#define MAX_BUFFER 256          // 通用字符串读取缓冲区最大长度

/**
 * @brief 全局函数返回状态码
 * 统一的错误处理机制，规范模块间调用的返回值
 */
#define SUCCESS 0                       // 操作执行成功
#define ERROR_INVALID_INPUT -1          // 用户输入不合法或超出范围
#define ERROR_NOT_FOUND -2              // 查询的数据记录在文件中不存在
#define ERROR_DUPLICATE -3              // 数据记录冲突（如重复的用户名）
#define ERROR_PERMISSION_DENIED -4      // 当前角色无权执行此操作
#define ERROR_FILE_IO -5                // 读写本地数据文件(txt)失败

/**
 * @brief 基础登录用户结构体
 * 记录账号最核心的鉴权和角色信息
 */
typedef struct {
    char username[MAX_USERNAME];  // 账号标识
    char password[MAX_PASSWORD];  // 登录口令
    char role[20];                // 角色类别（对应上述ROLE宏定义）
} User;

/**
 * @brief 运行时会话状态上下文
 * 全局单例，用于在不同模块间透传当前登录用户的状态
 */
typedef struct {
    User current_user;  // 当前持有的用户对象拷贝
    bool logged_in;     // 登录状态标记，为true表示已通过验证
} Session;

// ==================== 基础UI及输入控制函数 ====================

/**
 * @brief 初始化终端的字符编码
 * 将Windows CMD的活动代码页切换为GBK(936)，防止出现中文字符丢失和乱码
 */
void init_console_encoding(void);

/**
 * @brief 清空标准输入缓冲区
 * 防止遗留的换行符或非法字符干扰后续的 scanf 读取
 */
void clear_input_buffer(void);

/**
 * @brief 暂停终端显示
 * 提示用户按回车键继续，用于结果展示后的界面停留
 */
void pause_screen(void);

/**
 * @brief 获取并在范围内校验用户菜单选择
 * @param min 允许的最小序号
 * @param max 允许的最大序号
 * @return 合法返回选择的数字，非法返回 ERROR_INVALID_INPUT
 */
int get_menu_choice(int min, int max);

// ==================== 通用业务工具函数 ====================

/**
 * @brief 获取系统当前时间格式化字符串
 * @param buffer 接收时间串的数组
 * @param buffer_size 数组容量
 * @note 格式化为 "YYYY-MM-DD HH:MM:SS"
 */
void get_current_time(char *buffer, int buffer_size);

/**
 * @brief 生成业务相关的唯一标识符(ID)
 * @param buffer 接收ID的数组
 * @param buffer_size 数组容量
 * @param prefix 业务前缀（例如 "P" 代表患者, "D" 代表医生）
 * @note 格式为：前缀 + 年月日时分，例如 "P202310241030"
 */
void generate_id(char *buffer, int buffer_size, const char *prefix);

#endif // COMMON_H
