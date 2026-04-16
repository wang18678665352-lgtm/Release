#include "login.h"
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief 新用户注册
 * 
 * 引导用户输入注册信息，校验唯一性约束（如用户名、身份证号），并将新用户信息持久化到数据库。
 * 
 * @param new_user 指向包含新用户注册信息的结构体指针
 * @return int 注册状态码（SUCCESS 表示成功，其他表示错误码）
 */
int register_user(User *new_user) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char confirm_password[MAX_PASSWORD];
    char role[20];
    
    printf("\n========== 用户注册 ==========\n");
    printf("1. 注册管理员\n");
    printf("2. 注册医生\n");
    printf("3. 注册患者\n");
    printf("0. 返回\n");
    
    // 获取用户选择的角色类型
    int role_choice = get_menu_choice(0, 3);
    if (role_choice == 0) return ERROR_INVALID_INPUT;
    
    switch (role_choice) {
        case 1: strcpy(role, ROLE_ADMIN); break;
        case 2: strcpy(role, ROLE_DOCTOR); break;
        case 3: strcpy(role, ROLE_PATIENT); break;
        default: return ERROR_INVALID_INPUT;
    }
    
    // 输入用户名并去除换行符
    printf("\n请输入用户名: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL) return ERROR_INVALID_INPUT;
    username[strcspn(username, "\n")] = 0;
    
    // 校验用户名不能为空
    if (strlen(username) == 0) {
        printf("用户名不能为空!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // 输入密码
    printf("请输入密码: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL) return ERROR_INVALID_INPUT;
    password[strcspn(password, "\n")] = 0;
    
    // 校验密码不能为空
    if (strlen(password) == 0) {
        printf("密码不能为空!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // 确认密码输入
    printf("请再次输入密码: ");
    if (fgets(confirm_password, MAX_PASSWORD, stdin) == NULL) return ERROR_INVALID_INPUT;
    confirm_password[strcspn(confirm_password, "\n")] = 0;
    
    // 检查两次密码是否一致
    if (strcmp(password, confirm_password) != 0) {
        printf("两次输入的密码不一致!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // 从文件加载现有用户列表进行唯一性检查
    UserNode *head = load_users_list();
    
    // 检查用户名是否已存在
    UserNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            free_user_list(head);
            printf("用户名已存在!\n");
            return ERROR_DUPLICATE;
        }
        current = current->next;
    }
    
    // 创建新用户结构体
    User user;
    strcpy(user.username, username);
    strcpy(user.password, password);
    strcpy(user.role, role);
    
    // 创建链表节点
    UserNode *new_node = create_user_node(&user);
    if (!new_node) {
        free_user_list(head);
        printf("内存分配失败!\n");
        return ERROR_FILE_IO;
    }
    
    // 将新节点添加到链表末尾
    if (!head) {
        head = new_node;
    } else {
        current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    // 将更新后的用户列表保存回文件
    int result = save_users_list(head);
    free_user_list(head);
    
    if (result != SUCCESS) {
        printf("保存用户数据失败!\n");
        return result;
    }
    
    printf("注册成功! 用户名: %s, 角色: %s\n", username, role);
    
    // 根据角色自动创建关联的档案（患者档案或医生档案）
    if (strcmp(role, ROLE_PATIENT) == 0) {
        ensure_patient_profile(username);
    } else if (strcmp(role, ROLE_DOCTOR) == 0) {
        ensure_doctor_profile(username);
    }
    
    if (new_user) *new_user = user;
    return SUCCESS;
}

/**
 * @brief 用户登录验证
 * 
 * 验证用户输入的凭据（用户名和密码），并根据匹配结果填充用户信息结构体。
 * 
 * @param logged_user 指向用于存储登录成功后用户信息的结构体指针
 * @return int 登录状态码（SUCCESS 表示成功，其他表示错误码如 ERROR_AUTH_FAILED）
 */
int login(User *logged_user) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[20];
    
    printf("\n========== 登录系统 ==========\n");
    printf("1. 管理员登录\n");
    printf("2. 医生登录\n");
    printf("3. 患者登录\n");
    printf("0. 退出\n");
    
    // 获取登录角色选择
    int role_choice = get_menu_choice(0, 3);
    if (role_choice == 0) return ERROR_INVALID_INPUT;
    
    switch (role_choice) {
        case 1: strcpy(role, ROLE_ADMIN); break;
        case 2: strcpy(role, ROLE_DOCTOR); break;
        case 3: strcpy(role, ROLE_PATIENT); break;
        default: return ERROR_INVALID_INPUT;
    }
    
    printf("\n请输入用户名: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL) return ERROR_INVALID_INPUT;
    username[strcspn(username, "\n")] = 0;
    
    printf("请输入密码: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL) return ERROR_INVALID_INPUT;
    password[strcspn(password, "\n")] = 0;
    
    // 加载用户数据并校验凭据
    UserNode *head = load_users_list();
    
    if (!head) {
        printf("加载用户数据失败!\n");
        return ERROR_FILE_IO;
    }
    
    // 遍历用户列表寻找匹配项
    UserNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0 &&
            strcmp(current->data.password, password) == 0 &&
            strcmp(current->data.role, role) == 0) {
            *logged_user = current->data;
            free_user_list(head);
            printf("登录成功! 欢迎, %s (%s)\n", username, role);
            return SUCCESS;
        }
        current = current->next;
    }
    
    free_user_list(head);
    printf("用户名、密码或角色类型错误!\n");
    return ERROR_NOT_FOUND;
}

/**
 * @brief 用户注销登录
 * 
 * 清除当前会话信息，释放相关资源，并确保系统返回至未登录状态。
 * 
 * @param session 指向当前活跃会话的指针
 */
void logout(Session *session) {
    if (session && session->logged_in) {
        printf("用户 %s 已退出登录\n", session->current_user.username);
        session->logged_in = false;
        // 清空当前用户信息
        memset(&session->current_user, 0, sizeof(User));
    }
}

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
bool has_permission(const User *user, const char *required_role) {
    if (!user || !required_role) return false;
    
    // 管理员具备所有操作权限
    if (strcmp(user->role, ROLE_ADMIN) == 0) {
        return true;
    }
    
    // 普通角色需进行精确匹配
    return strcmp(user->role, required_role) == 0;
}
