#include "common.h"
#include "login.h"
#include "patient.h"
#include "doctor.h"
#include "admin.h"
#include "public.h"
#include "data_storage.h"

Session global_session = { {0}, false };

void show_main_menu(void);
void run_patient_menu(const User *user);
void run_doctor_menu(const User *user);
void run_admin_menu(const User *user);

int main(void) {
    init_console_encoding();
    
    printf("=======================================\n");
    printf("     电子医疗管理系统\n");
    printf("=======================================\n");
    
    if (init_data_storage() != SUCCESS) {
        printf("数据存储初始化失败!\n");
        return 1;
    }
    
    while (1) {
        if (!global_session.logged_in) {
            show_main_menu();
        } else {
            if (strcmp(global_session.current_user.role, ROLE_PATIENT) == 0) {
                run_patient_menu(&global_session.current_user);
            } else if (strcmp(global_session.current_user.role, ROLE_DOCTOR) == 0) {
                run_doctor_menu(&global_session.current_user);
            } else if (strcmp(global_session.current_user.role, ROLE_ADMIN) == 0) {
                run_admin_menu(&global_session.current_user);
            }
        }
        
        if (!global_session.logged_in) {
            int choice = get_menu_choice(0, 2);
            if (choice == 0) {
                printf("感谢使用，再见!\n");
                break;
            }
            
            if (choice == 2) {
                User new_user;
                int result = register_user(&new_user);
                if (result == SUCCESS) {
                    global_session.current_user = new_user;
                    global_session.logged_in = true;
                }
            } else if (choice == 1) {
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

void show_main_menu(void) {
    printf("\n========== 主菜单 ==========\n");
    printf("1. 登录系统\n");
    printf("2. 注册用户\n");
    printf("0. 退出程序\n");
}

void run_patient_menu(const User *user) {
    while (1) {
        patient_main_menu(user);
        printf("0. 退出登录\n");
        
        int choice = get_menu_choice(0, 6);
        
        switch (choice) {
            case 0:
                logout(&global_session);
                return;
            case 1: patient_register_menu(user); break;
            case 2: patient_appointment_menu(user); break;
            case 3: patient_query_diagnosis_menu(user); break;
            case 4: patient_view_ward_menu(user); break;
            case 5: patient_view_treatment_progress_menu(user); break;
            case 6: patient_edit_profile_menu(user); break;
        }
        pause_screen();
    }
}

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
