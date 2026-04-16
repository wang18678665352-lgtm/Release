#include "login.h"
#include <ctype.h>
#include <stdbool.h>

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
    
    int role_choice = get_menu_choice(0, 3);
    if (role_choice == 0) return ERROR_INVALID_INPUT;
    
    switch (role_choice) {
        case 1: strcpy(role, ROLE_ADMIN); break;
        case 2: strcpy(role, ROLE_DOCTOR); break;
        case 3: strcpy(role, ROLE_PATIENT); break;
        default: return ERROR_INVALID_INPUT;
    }
    
    // Input username
    printf("\n请输入用户名: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL) return ERROR_INVALID_INPUT;
    username[strcspn(username, "\n")] = 0;
    
    // Validate username not empty
    if (strlen(username) == 0) {
        printf("用户名不能为空!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // Input password
    printf("请输入密码: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL) return ERROR_INVALID_INPUT;
    password[strcspn(password, "\n")] = 0;
    
    // Validate password not empty
    if (strlen(password) == 0) {
        printf("密码不能为空!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // Confirm password
    printf("请再次输入密码: ");
    if (fgets(confirm_password, MAX_PASSWORD, stdin) == NULL) return ERROR_INVALID_INPUT;
    confirm_password[strcspn(confirm_password, "\n")] = 0;
    
    // Check password match
    if (strcmp(password, confirm_password) != 0) {
        printf("两次输入的密码不一致!\n");
        return ERROR_INVALID_INPUT;
    }
    
    // Load existing users
    UserNode *head = load_users_list();
    
    // Check if username already exists
    UserNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            free_user_list(head);
            printf("用户名已存在!\n");
            return ERROR_DUPLICATE;
        }
        current = current->next;
    }
    
    // Create new user
    User user;
    strcpy(user.username, username);
    strcpy(user.password, password);
    strcpy(user.role, role);
    
    // Add to linked list
    UserNode *new_node = create_user_node(&user);
    if (!new_node) {
        free_user_list(head);
        printf("内存分配失败!\n");
        return ERROR_FILE_IO;
    }
    
    // Find the end of the list
    if (!head) {
        head = new_node;
    } else {
        current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    // Save to file
    int result = save_users_list(head);
    free_user_list(head);
    
    if (result != SUCCESS) {
        printf("保存用户数据失败!\n");
        return result;
    }
    
    printf("注册成功! 用户名: %s, 角色: %s\n", username, role);
    
    // Create associated profile based on role
    if (strcmp(role, ROLE_PATIENT) == 0) {
        ensure_patient_profile(username);
    } else if (strcmp(role, ROLE_DOCTOR) == 0) {
        ensure_doctor_profile(username);
    }
    
    if (new_user) *new_user = user;
    return SUCCESS;
}

int login(User *logged_user) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[20];
    
    printf("\n========== 登录系统 ==========\n");
    printf("1. 管理员登录\n");
    printf("2. 医生登录\n");
    printf("3. 患者登录\n");
    printf("0. 退出\n");
    
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
    
    // Load users and check credentials
    UserNode *head = load_users_list();
    
    if (!head) {
        printf("加载用户数据失败!\n");
        return ERROR_FILE_IO;
    }
    
    // Find matching user
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

void logout(Session *session) {
    if (session && session->logged_in) {
        printf("用户 %s 已退出登录\n", session->current_user.username);
        session->logged_in = false;
        memset(&session->current_user, 0, sizeof(User));
    }
}

bool has_permission(const User *user, const char *required_role) {
    if (!user || !required_role) return false;
    
    if (strcmp(user->role, ROLE_ADMIN) == 0) {
        // Admin has all permissions
        return true;
    }
    
    return strcmp(user->role, required_role) == 0;
}

