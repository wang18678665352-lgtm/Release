#ifndef LOGIN_H
#define LOGIN_H

#include "common.h"
#include "data_storage.h"

/**
 * @brief 用户登录验证
 * 
 * 验证用户输入的凭据（用户名和密码），并根据匹配结果填充用户信息结构体。
 * 
 * @param logged_user 指向用于存储登录成功后用户信息的结构体指针
 * @return int 登录状态码（SUCCESS 表示成功，其他表示错误码如 ERROR_AUTH_FAILED）
 */
int login(User *logged_user);

/**
 * @brief 新用户注册
 * 
 * 引导用户输入注册信息，校验唯一性约束（如用户名、身份证号），并将新用户信息持久化到数据库。
 * 
 * @param new_user 指向包含新用户注册信息的结构体指针
 * @return int 注册状态码（SUCCESS 表示成功，其他表示错误码）
 */
int register_user(User *new_user);

/**
 * @brief 用户注销登录
 * 
 * 清除当前会话信息，释放相关资源，并确保系统返回至未登录状态。
 * 
 * @param session 指向当前活跃会话的指针
 */
void logout(Session *session);

/**
 * @brief 用户权限校验
 * 
 * 检查指定用户是否具备访问特定功能或资源所需的角色权限。
 * 
 * @param user 指向待校验用户的指针
 * @param required_role 所需的角色标识字符串（如 "ADMIN", "DOCTOR", "PATIENT"）
 * @return true 具备权限
 * @return false 权限不足
 */
bool has_permission(const User *user, const char *required_role);

#endif // LOGIN_H
