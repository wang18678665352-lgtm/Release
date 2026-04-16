#include "patient.h"

/**
 * @brief 显示所有可用科室
 * 
 * 从数据文件中加载科室列表并以表格形式展示。
 */
void show_available_departments(void) {
    // 加载科室链表
    DepartmentNode *head = load_departments_list();
    
    if (!head) {
        printf("\n暂无科室信息，请联系管理员添加。\n");
        return;
    }
    
    printf("\n========== 可选科室 ==========\n");
    printf("%-10s %-20s %-15s\n", "科室编号", "科室名称", "负责人");
    printf("-------------------------------------------\n");
    
    // 遍历链表打印科室信息
    DepartmentNode *current = head;
    while (current) {
        printf("%-10s %-20s %-15s\n", 
               current->data.department_id, 
               current->data.name, 
               current->data.leader);
        current = current->next;
    }
    
    // 释放内存
    free_department_list(head);
}

/**
 * @brief 显示特定科室的医生列表
 * 
 * 根据输入的科室ID，筛选并展示该科室下所有医生的详细信息。
 * 
 * @param department_id 科室编号
 */
void show_doctors_by_department(const char *department_id) {
    // 加载医生链表
    DoctorNode *head = load_doctors_list();
    
    int found = 0;
    printf("\n========== 可选医生 ==========\n");
    printf("%-10s %-15s %-10s %-10s\n", "医生编号", "医生姓名", "职称", "繁忙程度");
    printf("--------------------------------------------------------\n");
    
    // 遍历并匹配科室编号
    DoctorNode *current = head;
    while (current) {
        if (strcmp(current->data.department_id, department_id) == 0) {
            printf("%-10s %-15s %-10s %-10d\n", 
                   current->data.doctor_id, 
                   current->data.name, 
                   current->data.title,
                   current->data.busy_level);
            found++;
        }
        current = current->next;
    }
    
    free_doctor_list(head);
    
    if (found == 0) {
        printf("该科室暂无医生。\n");
    }
}

/**
 * @brief 患者模块主菜单
 * 
 * 展示患者可操作的功能选项。
 * 
 * @param current_user 当前登录用户
 */
void patient_main_menu(const User *current_user) {
    printf("\n========== 患者系统 ==========\n");
    printf("当前用户: %s\n", current_user->username);
    printf("1. 挂号\n");
    printf("2. 挂号状态查询\n");
    printf("3. 诊断结果查询\n");
    printf("4. 住院信息查看\n");
    printf("5. 治疗进度查看\n");
    printf("6. 修改个人信息\n");
}

/**
 * @brief 患者挂号流程处理
 * 
 * 包含科室选择、医生选择、预约单生成及医生繁忙度更新的完整业务逻辑。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_register_menu(const User *current_user) {
    printf("\n========== 挂号功能 ==========\n");

    // 确保患者档案已初始化
    if (ensure_patient_profile(current_user->username) != SUCCESS) {
        printf("患者档案初始化失败!\n");
        return ERROR_FILE_IO;
    }    
    
    // 1. 展示科室供选择
    show_available_departments();
    
    // 获取科室编号
    char department_id[MAX_ID];
    printf("\n请输入科室编号: ");
    if (fgets(department_id, MAX_ID, stdin) == NULL) return ERROR_INVALID_INPUT;
    department_id[strcspn(department_id, "\n")] = 0;
    
    // 验证科室是否存在
    DepartmentNode *head = load_departments_list();
    
    int dept_found = 0;
    DepartmentNode *current = head;
    while (current) {
        if (strcmp(current->data.department_id, department_id) == 0) {
            dept_found = 1;
            break;
        }
        current = current->next;
    }
    
    free_department_list(head);
    
    if (!dept_found) {
        printf("科室编号不存在!\n");
        return ERROR_NOT_FOUND;
    }
    
    // 2. 展示该科室医生供选择
    show_doctors_by_department(department_id);
    
    // 获取医生编号
    char doctor_id[MAX_ID];
    printf("\n请输入医生编号: ");
    if (fgets(doctor_id, MAX_ID, stdin) == NULL) return ERROR_INVALID_INPUT;
    doctor_id[strcspn(doctor_id, "\n")] = 0;
    
    // 验证医生是否存在且属于该科室
    DoctorNode *doctor_head = load_doctors_list();
    
    int doc_found = 0;
    Doctor selected_doc;
    DoctorNode *current_doc = doctor_head;
    while (current_doc) {
        if (strcmp(current_doc->data.doctor_id, doctor_id) == 0 && 
            strcmp(current_doc->data.department_id, department_id) == 0) {
            doc_found = 1;
            selected_doc = current_doc->data;
            break;
        }
        current_doc = current_doc->next;
    }
    
    if (!doc_found) {
        free_doctor_list(doctor_head);
        printf("医生编号不存在或不属于该科室!\n");
        return ERROR_NOT_FOUND;
    }
    
    // 3. 获取当前患者详细信息
    PatientNode *patient_head = load_patients_list();
    
    int patient_found = 0;
    Patient current_patient;
    PatientNode *current_patient_node = patient_head;
    while (current_patient_node) {
        if (strcmp(current_patient_node->data.username, current_user->username) == 0) {
            patient_found = 1;
            current_patient = current_patient_node->data;
            break;
        }
        current_patient_node = current_patient_node->next;
    }
    
    if (!patient_found) {
        free_doctor_list(doctor_head);
        free_patient_list(patient_head);
        printf("患者信息不存在!\n");
        return ERROR_NOT_FOUND;
    }
    
    // 备份必要信息用于后续显示
    char patient_id_copy[MAX_ID];
    char patient_name_copy[MAX_NAME];
    char doctor_name_copy[MAX_NAME];
    strcpy(patient_id_copy, current_patient.patient_id);
    strcpy(patient_name_copy, current_patient.name);
    strcpy(doctor_name_copy, selected_doc.name);
    
    // 4. 创建挂号预约记录
    Appointment new_apt;
    generate_id(new_apt.appointment_id, MAX_ID, "APT");
    strcpy(new_apt.patient_id, patient_id_copy);
    strcpy(new_apt.doctor_id, doctor_id);
    strcpy(new_apt.department_id, department_id);
    
    get_current_time(new_apt.appointment_date, 20);
    strcpy(new_apt.appointment_time, new_apt.appointment_date);
    strcpy(new_apt.status, "已挂号");
    get_current_time(new_apt.create_time, 30);
    
    // 加载现有预约列表
    AppointmentNode *apt_head = load_appointments_list();
    
    // 将新预约加入链表末尾
    AppointmentNode *new_apt_node = create_appointment_node(&new_apt);
    if (!new_apt_node) {
        free_doctor_list(doctor_head);
        free_patient_list(patient_head);
        free_appointment_list(apt_head);
        printf("内存分配失败!\n");
        return ERROR_FILE_IO;
    }
    
    if (!apt_head) {
        apt_head = new_apt_node;
    } else {
        AppointmentNode *tail = apt_head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = new_apt_node;
    }
    
    // 保存预约信息到文件
    int result = save_appointments_list(apt_head);
    
    // 5. 更新医生的繁忙程度（挂号人数加1）
    selected_doc.busy_level++;
    
    // 同步更新医生链表中的数据
    current_doc = doctor_head;
    while (current_doc) {
        if (strcmp(current_doc->data.doctor_id, doctor_id) == 0) {
            current_doc->data = selected_doc;
            break;
        }
        current_doc = current_doc->next;
    }
    
    // 保存医生信息
    save_doctors_list(doctor_head);
    
    // 释放所有临时链表内存
    free_doctor_list(doctor_head);
    free_patient_list(patient_head);
    free_appointment_list(apt_head);
    
    if (result == SUCCESS) {
        printf("\n挂号成功!\n");
        printf("挂号单号: %s\n", new_apt.appointment_id);
        printf("患者: %s\n", patient_name_copy);
        printf("科室: %s\n", department_id);
        printf("医生: %s\n", doctor_name_copy);
        printf("状态: %s\n", new_apt.status);
    }
    
    return result;
}

/**
 * @brief 查询患者自身的挂号状态
 * 
 * 遍历预约记录，展示与当前患者相关的所有挂号信息。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_appointment_menu(const User *current_user) {
    printf("\n========== 挂号状态查询 ==========\n");

    if (ensure_patient_profile(current_user->username) != SUCCESS) {
        printf("患者档案初始化失败!\n");
        return ERROR_FILE_IO;
    }    
    
    // 获取当前患者ID
    PatientNode *patient_head = load_patients_list();
    
    int patient_found = 0;
    char patient_id_copy[MAX_ID];
    PatientNode *current_patient_node = patient_head;
    while (current_patient_node) {
        if (strcmp(current_patient_node->data.username, current_user->username) == 0) {
            patient_found = 1;
            strcpy(patient_id_copy, current_patient_node->data.patient_id);
            break;
        }
        current_patient_node = current_patient_node->next;
    }
    
    if (!patient_found) {
        free_patient_list(patient_head);
        printf("患者信息不存在!\n");
        return ERROR_NOT_FOUND;
    }
    
    free_patient_list(patient_head);
    
    // 加载所有预约记录并筛选
    AppointmentNode *apt_head = load_appointments_list();
    
    printf("\n========== 我的挂号记录 ==========\n");
    printf("%-15s %-15s %-15s %-15s\n", "挂号单号", "科室", "医生", "状态");
    printf("------------------------------------------------------------------------\n");
    
    int found = 0;
    AppointmentNode *current_apt = apt_head;
    while (current_apt) {
        if (strcmp(current_apt->data.patient_id, patient_id_copy) == 0) {
            // 获取医生姓名用于友好展示
            DoctorNode *doctor_head = load_doctors_list();
            
            char doctor_name[MAX_NAME] = "未知";
            DoctorNode *current_doc = doctor_head;
            while (current_doc) {
                if (strcmp(current_doc->data.doctor_id, current_apt->data.doctor_id) == 0) {
                    strcpy(doctor_name, current_doc->data.name);
                    break;
                }
                current_doc = current_doc->next;
            }
            free_doctor_list(doctor_head);
            
            printf("%-15s %-15s %-15s %-15s\n", 
                   current_apt->data.appointment_id,
                   current_apt->data.department_id,
                   doctor_name,
                   current_apt->data.status);
            found++;
        }
        current_apt = current_apt->next;
    }
    
    free_appointment_list(apt_head);
    
    if (found == 0) {
        printf("暂无挂号记录。\n");
    }
    
    return SUCCESS;
}

/**
 * @brief 查询诊断结果及病历详情
 * 
 * 患者可以查看历史诊断记录，并根据记录编号查看详细的诊断建议。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_query_diagnosis_menu(const User *current_user) {
    printf("\n========== 诊断结果查询 ==========\n");

    if (ensure_patient_profile(current_user->username) != SUCCESS) {
        printf("患者档案初始化失败!\n");
        return ERROR_FILE_IO;
    }    
    
    // 获取当前患者ID
    PatientNode *patient_head = load_patients_list();
    
    int patient_found = 0;
    char patient_id_copy[MAX_ID];
    PatientNode *current_patient_node = patient_head;
    while (current_patient_node) {
        if (strcmp(current_patient_node->data.username, current_user->username) == 0) {
            patient_found = 1;
            strcpy(patient_id_copy, current_patient_node->data.patient_id);
            break;
        }
        current_patient_node = current_patient_node->next;
    }
    
    if (!patient_found) {
        free_patient_list(patient_head);
        printf("患者信息不存在!\n");
        return ERROR_NOT_FOUND;
    }
    
    free_patient_list(patient_head);
    
    // 加载病历列表
    MedicalRecordNode *record_head = load_medical_records_list();
    
    printf("\n========== 我的诊断记录 ==========\n");
    printf("%-15s %-15s %-20s %-15s\n", "记录编号", "医生编号", "诊断日期", "状态");
    printf("------------------------------------------------------------------------\n");
    
    int found = 0;
    MedicalRecordNode *current_record = record_head;
    while (current_record) {
        if (strcmp(current_record->data.patient_id, patient_id_copy) == 0) {
            printf("%-15s %-15s %-20s %-15s\n", 
                   current_record->data.record_id,
                   current_record->data.doctor_id,
                   current_record->data.diagnosis_date,
                   current_record->data.status);
            found++;
        }
        current_record = current_record->next;
    }
    
    if (found == 0) {
        printf("暂无诊断记录。\n");
    } else {
        // 允许查看具体某条记录的详细内容
        printf("\n请输入记录编号查看详情(输入0返回): ");
        char record_id[MAX_ID];
        if (fgets(record_id, MAX_ID, stdin) == NULL) return ERROR_INVALID_INPUT;
        record_id[strcspn(record_id, "\n")] = 0;
        
        if (strcmp(record_id, "0") != 0) {
            current_record = record_head;
            while (current_record) {
                if (strcmp(current_record->data.record_id, record_id) == 0 &&
                    strcmp(current_record->data.patient_id, patient_id_copy) == 0) {
                    printf("\n========== 诊断详情 ==========\n");
                    printf("诊断结果: %s\n", current_record->data.diagnosis);
                    printf("诊断日期: %s\n", current_record->data.diagnosis_date);
                    printf("治疗状态: %s\n", current_record->data.status);
                    break;
                }
                current_record = current_record->next;
            }
        }
    }
    
    free_medical_record_list(record_head);
    
    return SUCCESS;
}

/**
 * @brief 查看全院病房床位信息
 * 
 * 展示各类型病房的床位总数、剩余数及预警状态。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_view_ward_menu(const User *current_user) {
    printf("\n========== 住院信息查看 ==========\n");
    
    // 加载病房数据
    WardNode *ward_head = load_wards_list();
    
    if (!ward_head) {
        printf("暂无病房信息。\n");
        return SUCCESS;
    }
    
    printf("\n========== 病房信息 ==========\n");
    printf("%-10s %-15s %-10s %-10s %-10s\n", "病房编号", "类型", "总床位", "剩余", "预警阈值");
    printf("--------------------------------------------------------------------------------\n");
    
    // 遍历展示病房状态
    WardNode *current_ward = ward_head;
    while (current_ward) {
        printf("%-10s %-15s %-10d %-10d %-10d\n", 
               current_ward->data.ward_id,
               current_ward->data.type,
               current_ward->data.total_beds,
               current_ward->data.remain_beds,
               current_ward->data.warning_line);
        current_ward = current_ward->next;
    }
    
    free_ward_list(ward_head);
    
    return SUCCESS;
}

/**
 * @brief 查看个人治疗进度
 * 
 * 展示患者当前的治疗阶段（如：检查中、手术后、康复中）及紧急程度。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_view_treatment_progress_menu(const User *current_user) {
    printf("\n========== 治疗进度查看 ==========\n");

    if (ensure_patient_profile(current_user->username) != SUCCESS) {
        printf("患者档案初始化失败!\n");
        return ERROR_FILE_IO;
    }    
    
    // 获取患者档案信息
    PatientNode *patient_head = load_patients_list();
    
    int patient_found = 0;
    char name_copy[MAX_NAME];
    char stage_copy[20];
    char type_copy[20];
    int emergency = 0;
    
    PatientNode *current_patient_node = patient_head;
    while (current_patient_node) {
        if (strcmp(current_patient_node->data.username, current_user->username) == 0) {
            patient_found = 1;
            strcpy(name_copy, current_patient_node->data.name);
            strcpy(stage_copy, current_patient_node->data.treatment_stage);
            strcpy(type_copy, current_patient_node->data.patient_type);
            emergency = current_patient_node->data.is_emergency;
            break;
        }
        current_patient_node = current_patient_node->next;
    }
    
    free_patient_list(patient_head);
    
    if (patient_found) {
        printf("\n患者: %s\n", name_copy);
        printf("当前治疗阶段: %s\n", stage_copy);
        printf("紧急状态: %s\n", emergency ? "是" : "否");
        printf("患者类型: %s\n", type_copy);
    } else {
        printf("患者信息不存在!\n");
    }
    
    return SUCCESS;
}

/**
 * @brief 修改患者个人档案信息
 * 
 * 提供交互式界面，允许患者更新姓名、性别、年龄、联系方式等基础信息。
 * 
 * @param current_user 当前登录用户
 * @return int 操作结果状态码
 */
int patient_edit_profile_menu(const User *current_user) {
    printf("\n========== 修改个人信息 ==========\n");

    if (ensure_patient_profile(current_user->username) != SUCCESS) {
        printf("患者档案初始化失败!\n");
        return ERROR_FILE_IO;
    }    
    
    // 定位当前患者节点
    PatientNode *patient_head = load_patients_list();
    
    int patient_found = 0;
    PatientNode *current_patient_node = patient_head;
    while (current_patient_node) {
        if (strcmp(current_patient_node->data.username, current_user->username) == 0) {
            patient_found = 1;
            break;
        }
        current_patient_node = current_patient_node->next;
    }
    
    if (!patient_found) {
        free_patient_list(patient_head);
        printf("患者信息不存在!\n");
        return ERROR_NOT_FOUND;
    }
    
    Patient *p = &current_patient_node->data;
    
    // 显示当前档案内容
    printf("\n当前信息:\n");
    printf("姓名: %s\n", p->name);
    printf("性别: %s\n", p->gender);
    printf("年龄: %d\n", p->age);
    printf("电话: %s\n", p->phone);
    printf("地址: %s\n", p->address);
    printf("患者类型: %s\n", p->patient_type);
    
    printf("\n请选择要修改的项目:\n");
    printf("1. 姓名\n");
    printf("2. 性别\n");
    printf("3. 年龄\n");
    printf("4. 电话\n");
    printf("5. 地址\n");
    printf("6. 患者类型(普通/医保/军人)\n");
    printf("0. 返回\n");
    
    int choice = get_menu_choice(0, 6);
    
    // 根据选择更新对应字段
    switch (choice) {
        case 1:
            printf("请输入新姓名: ");
            if (fgets(p->name, MAX_NAME, stdin)) {
                p->name[strcspn(p->name, "\n")] = 0;
            }
            break;
        case 2:
            printf("请输入新性别(男/女): ");
            if (fgets(p->gender, 10, stdin)) {
                p->gender[strcspn(p->gender, "\n")] = 0;
            }
            break;
        case 3:
            printf("请输入新年龄: ");
            if (scanf("%d", &p->age) != 1) {
                printf("输入无效!\n");
            }
            clear_input_buffer();
            break;
        case 4:
            printf("请输入新电话: ");
            if (fgets(p->phone, 20, stdin)) {
                p->phone[strcspn(p->phone, "\n")] = 0;
            }
            break;
        case 5:
            printf("请输入新地址: ");
            if (fgets(p->address, 200, stdin)) {
                p->address[strcspn(p->address, "\n")] = 0;
            }
            break;
        case 6:
            printf("请输入患者类型(普通/医保/军人): ");
            if (fgets(p->patient_type, 20, stdin)) {
                p->patient_type[strcspn(p->patient_type, "\n")] = 0;
            }
            break;
        case 0:
            free_patient_list(patient_head);
            return SUCCESS;
    }
    
    // 将更新后的链表保存回文件
    int result = save_patients_list(patient_head);
    free_patient_list(patient_head);
    
    if (result == SUCCESS) {
        printf("\n个人信息更新成功!\n");
    }
    
    return result;
}
