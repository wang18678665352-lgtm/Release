#include "common.h"
#include "login.h"
#include "patient.h"
#include "doctor.h"
#include "admin.h"
#include "public.h"
#include "data_storage.h"

/**
 * @brief 全局会话对象
 * 在整个程序运行生命周期内维持当前登录用户的状态。
 * 初始化为全零状态且未登录。
 */
Session global_session = { {0}, false };

// UI菜单渲染前置声明
void show_main_menu(void);
void run_patient_menu(const User *user);
void run_doctor_menu(const User *user);
void run_admin_menu(const User *user);

/**
 * @brief 电子医疗管理系统主入口
 * 负责环境初始化、数据存储挂载及顶层会话事件循环。
 */
int main(void) {
    // 1. 初始化控制台编码，确保中文输出在 Windows CMD 下不会出现乱码或被截断
    init_console_encoding();
    
    printf("=======================================\n");
    printf("     电子医疗管理系统\n");
    printf("=======================================\n");
    
    // 2. 初始化数据存储引擎（检查或创建 data 目录，确保 CSV 存储环境就绪）
    if (init_data_storage() != SUCCESS) {
        printf("数据存储初始化失败!\n");
        return 1;
    }
    
    // 3. 顶层主事件循环：管理登录状态和角色路由分发
    while (1) {
        // 如果当前未登录，展示系统主菜单
        if (!global_session.logged_in) {
            show_main_menu();
        } else {
            // 已登录状态，根据身份路由到对应的核心业务模块菜单
            if (strcmp(global_session.current_user.role, ROLE_PATIENT) == 0) {
                // 患者端：挂号、查病历、看处方
                run_patient_menu(&global_session.current_user);
            } else if (strcmp(global_session.current_user.role, ROLE_DOCTOR) == 0) {
                // 医生端：接诊、开药、病房调度
                run_doctor_menu(&global_session.current_user);
            } else if (strcmp(global_session.current_user.role, ROLE_ADMIN) == 0) {
                // 管理端：基础档案数据的增删改查
                run_admin_menu(&global_session.current_user);
            }
        }
        
        // 捕获和处理未登录状态下的用户操作（登录/注册/退出）
        if (!global_session.logged_in) {
            int choice = get_menu_choice(0, 2);
            if (choice == 0) {
                printf("感谢使用，再见!\n");
                break; // 0: 退出整个系统
            }
            
            if (choice == 2) {
                // 2: 注册新患者账户。注册成功后直接将该账户置于全局会话中，实现自动登录。
                User new_user;
                int result = register_user(&new_user);
                if (result == SUCCESS) {
                    global_session.current_user = new_user;
                    global_session.logged_in = true;
                }
            } else if (choice == 1) {
                // 1: 用户登录。通过凭证校验后，将会话状态置为已登录。
                User logged_user;
                int result = login(&logged_user);
                if (result == SUCCESS) {
                    global_session.current_user = logged_user;
                    global_session.logged_in = true;
                }
            }
        }
    }
    
    return 0;
}

/**
 * @brief 渲染未登录状态下的欢迎页和操作主菜单
 */
void show_main_menu(void) {
    printf("\n========== 主菜单 ==========\n");
    printf("1. 登录系统\n");
    printf("2. 注册用户\n");
    printf("0. 退出程序\n");
}

/**
 * @brief 挂载并进入患者端事件循环
 */
void run_patient_menu(const User *user) {
    while (1) {
        patient_main_menu(user);
        printf("0. 退出登录\n");
        
        int choice = get_menu_choice(0, 6);
        
        switch (choice) {
            case 0: // 触发登出，清除全局Session
                logout(&global_session);
                return;
            case 1: patient_register_menu(user); break;
            case 2: patient_appointment_menu(user); break;
            case 3: patient_query_diagnosis_menu(user); break;
            case 4: patient_view_ward_menu(user); break;
            case 5: patient_view_treatment_progress_menu(user); break;
            case 6: patient_edit_profile_menu(user); break;
        }
        pause_screen(); // 操作完成后暂停，以便用户阅读输出结果
    }
}

/**
 * @brief 挂载并进入医生端事件循环
 */
void run_doctor_menu(const User *user) {
    while (1) {
        doctor_main_menu(user);
        printf("0. 退出登录\n");
        
        int choice = get_menu_choice(0, 6);
        
        switch (choice) {
            case 0:
                logout(&global_session);
                return;
            case 1: doctor_appointment_reminder_menu(user); break;
            case 2: doctor_consultation_menu(user); break;
            case 3: doctor_prescribe_menu(user); break;
            case 4: doctor_ward_call_menu(user); break;
            case 5: doctor_emergency_flag_menu(user); break;
            case 6: doctor_update_progress_menu(user); break;
        }
        pause_screen();
    }
}

/**
 * @brief 挂载并进入管理员系统后台循环
 */
void run_admin_menu(const User *user) {
    while (1) {
        admin_main_menu(user);
        printf("0. 退出登录\n");
        
        int choice = get_menu_choice(0, 6);
        
        switch (choice) {
            case 0:
                logout(&global_session);
                return;
            case 1: admin_department_menu(user); break;
            case 2: admin_doctor_menu(user); break;
            case 3: admin_patient_menu(user); break;
            case 4: admin_drug_menu(user); break;
            case 5: admin_ward_menu(user); break;
            case 6: admin_report_menu(user); break;
        }
        pause_screen();
    }
}
