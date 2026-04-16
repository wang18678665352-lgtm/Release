#include "doctor.h"

void doctor_main_menu(const User *current_user) {
    printf("\n========== 医生系统 ==========\n");
    printf("功能模块框架 - 待实现\n");
    printf("1. 被挂号提醒\n");
    printf("2. 接诊处理\n");
    printf("3. 开药功能\n");
    printf("4. 病房被叫提醒\n");
    printf("5. 紧急病人标识\n");
    printf("6. 治疗进度更新\n");
    printf("0. 退出\n");
}

int doctor_appointment_reminder_menu(const User *current_user) {
    printf("\n[医生模块] 被挂号提醒 - 待实现\n");
    return SUCCESS;
}

int doctor_consultation_menu(const User *current_user) {
    printf("\n[医生模块] 接诊处理 - 待实现\n");
    return SUCCESS;
}

int doctor_prescribe_menu(const User *current_user) {
    printf("\n[医生模块] 开药功能 - 待实现\n");
    return SUCCESS;
}

int doctor_ward_call_menu(const User *current_user) {
    printf("\n[医生模块] 病房被叫提醒 - 待实现\n");
    return SUCCESS;
}

int doctor_emergency_flag_menu(const User *current_user) {
    printf("\n[医生模块] 紧急病人标识 - 待实现\n");
    return SUCCESS;
}

int doctor_update_progress_menu(const User *current_user) {
    printf("\n[医生模块] 治疗进度更新 - 待实现\n");
    return SUCCESS;
}
