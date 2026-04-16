#include "admin.h"

void admin_main_menu(const User *current_user) {
    printf("\n========== 管理员系统 ==========\n");
    printf("功能模块框架 - 待实现\n");
    printf("1. 科室管理\n");
    printf("2. 医生管理\n");
    printf("3. 患者管理\n");
    printf("4. 药物管理\n");
    printf("5. 病房管理\n");
    printf("6. 报表管理\n");
    printf("0. 退出\n");
}

int admin_department_menu(const User *current_user) {
    printf("\n[管理员模块] 科室管理 - 待实现\n");
    return SUCCESS;
}

int admin_doctor_menu(const User *current_user) {
    printf("\n[管理员模块] 医生管理 - 待实现\n");
    return SUCCESS;
}

int admin_patient_menu(const User *current_user) {
    printf("\n[管理员模块] 患者管理 - 待实现\n");
    return SUCCESS;
}

int admin_drug_menu(const User *current_user) {
    printf("\n[管理员模块] 药物管理 - 待实现\n");
    return SUCCESS;
}

int admin_ward_menu(const User *current_user) {
    printf("\n[管理员模块] 病房管理 - 待实现\n");
    return SUCCESS;
}

int admin_report_menu(const User *current_user) {
    printf("\n[管理员模块] 报表管理 - 待实现\n");
    return SUCCESS;
}
