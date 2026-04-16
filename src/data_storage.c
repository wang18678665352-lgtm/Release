#include "data_storage.h"
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

/**
 * @brief 初始化数据存储环境
 * 
 * 检查系统预设的数据存储目录是否存在。如果不存在，则根据当前操作系统
 * （Windows 或 POSIX）调用相应的系统 API 创建目录。
 * 
 * @return int 执行状态码，SUCCESS 表示初始化成功，ERROR_FILE_IO 表示目录创建失败
 */
int init_data_storage(void) {
#ifdef _WIN32
    // Windows 环境下检查并创建目录
    DWORD dwAttrib = GetFileAttributesA(DATA_DIR);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        if (!CreateDirectoryA(DATA_DIR, NULL)) {
            printf("创建数据目录失败!\n");
            return ERROR_FILE_IO;
        }
    }
#else
    // Linux/Unix 环境下检查并创建目录
    struct stat st = {0};
    if (stat(DATA_DIR, &st) == -1) {
        if (mkdir(DATA_DIR, 0755) != 0) {
            printf("创建数据目录失败: %s\n", strerror(errno));
            return ERROR_FILE_IO;
        }
    }
#endif
    return SUCCESS;
}

// ==================== 链表操作函数 ====================
// 以下函数负责各类医疗实体链表节点的创建、内存释放及数量统计

/**
 * @brief 创建用户节点
 * @param user 用户数据结构体指针
 * @return UserNode* 指向新创建节点的指针，失败返回 NULL
 */
UserNode* create_user_node(const User *user) {
    UserNode *node = (UserNode *)malloc(sizeof(UserNode));
    if (node) {
        node->data = *user;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放用户链表内存
 * @param head 链表头指针
 */
void free_user_list(UserNode *head) {
    UserNode *current = head;
    while (current) {
        UserNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计用户链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_user_list(UserNode *head) {
    int count = 0;
    UserNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建患者节点
 * @param patient 患者数据结构体指针
 * @return PatientNode* 指向新创建节点的指针
 */
PatientNode* create_patient_node(const Patient *patient) {
    PatientNode *node = (PatientNode *)malloc(sizeof(PatientNode));
    if (node) {
        node->data = *patient;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放患者链表内存
 * @param head 链表头指针
 */
void free_patient_list(PatientNode *head) {
    PatientNode *current = head;
    while (current) {
        PatientNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计患者链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_patient_list(PatientNode *head) {
    int count = 0;
    PatientNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建医生节点
 * @param doctor 医生数据结构体指针
 * @return DoctorNode* 指向新创建节点的指针
 */
DoctorNode* create_doctor_node(const Doctor *doctor) {
    DoctorNode *node = (DoctorNode *)malloc(sizeof(DoctorNode));
    if (node) {
        node->data = *doctor;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放医生链表内存
 * @param head 链表头指针
 */
void free_doctor_list(DoctorNode *head) {
    DoctorNode *current = head;
    while (current) {
        DoctorNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计医生链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_doctor_list(DoctorNode *head) {
    int count = 0;
    DoctorNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建科室节点
 * @param department 科室数据结构体指针
 * @return DepartmentNode* 指向新创建节点的指针
 */
DepartmentNode* create_department_node(const Department *department) {
    DepartmentNode *node = (DepartmentNode *)malloc(sizeof(DepartmentNode));
    if (node) {
        node->data = *department;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放科室链表内存
 * @param head 链表头指针
 */
void free_department_list(DepartmentNode *head) {
    DepartmentNode *current = head;
    while (current) {
        DepartmentNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计科室链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_department_list(DepartmentNode *head) {
    int count = 0;
    DepartmentNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建药物节点
 * @param drug 药物数据结构体指针
 * @return DrugNode* 指向新创建节点的指针
 */
DrugNode* create_drug_node(const Drug *drug) {
    DrugNode *node = (DrugNode *)malloc(sizeof(DrugNode));
    if (node) {
        node->data = *drug;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放药物链表内存
 * @param head 链表头指针
 */
void free_drug_list(DrugNode *head) {
    DrugNode *current = head;
    while (current) {
        DrugNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计药物链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_drug_list(DrugNode *head) {
    int count = 0;
    DrugNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建病房节点
 * @param ward 病房数据结构体指针
 * @return WardNode* 指向新创建节点的指针
 */
WardNode* create_ward_node(const Ward *ward) {
    WardNode *node = (WardNode *)malloc(sizeof(WardNode));
    if (node) {
        node->data = *ward;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放病房链表内存
 * @param head 链表头指针
 */
void free_ward_list(WardNode *head) {
    WardNode *current = head;
    while (current) {
        WardNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计病房链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_ward_list(WardNode *head) {
    int count = 0;
    WardNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建挂号预约节点
 * @param appointment 预约数据结构体指针
 * @return AppointmentNode* 指向新创建节点的指针
 */
AppointmentNode* create_appointment_node(const Appointment *appointment) {
    AppointmentNode *node = (AppointmentNode *)malloc(sizeof(AppointmentNode));
    if (node) {
        node->data = *appointment;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放预约链表内存
 * @param head 链表头指针
 */
void free_appointment_list(AppointmentNode *head) {
    AppointmentNode *current = head;
    while (current) {
        AppointmentNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计预约链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_appointment_list(AppointmentNode *head) {
    int count = 0;
    AppointmentNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建病历记录节点
 * @param record 病历数据结构体指针
 * @return MedicalRecordNode* 指向新创建节点的指针
 */
MedicalRecordNode* create_medical_record_node(const MedicalRecord *record) {
    MedicalRecordNode *node = (MedicalRecordNode *)malloc(sizeof(MedicalRecordNode));
    if (node) {
        node->data = *record;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放病历链表内存
 * @param head 链表头指针
 */
void free_medical_record_list(MedicalRecordNode *head) {
    MedicalRecordNode *current = head;
    while (current) {
        MedicalRecordNode *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief 统计病历链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_medical_record_list(MedicalRecordNode *head) {
    int count = 0;
    MedicalRecordNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * @brief 创建处方节点
 * @param prescription 处方数据结构体指针
 * @return PrescriptionNode* 指向新创建节点的指针
 */
PrescriptionNode* create_prescription_node(const Prescription *prescription) {
    PrescriptionNode *node = (PrescriptionNode *)malloc(sizeof(PrescriptionNode));
    if (node) {
        node->data = *prescription;
        node->next = NULL;
    }
    return node;
}

/**
 * @brief 释放处方链表内存
 * @param head 链表头指针
 */
void free_prescription_list(PrescriptionNode *head) {
    PrescriptionNode *current = head;
    while (current) {
        UserNode *next = (UserNode *)current->next;
        free(current);
        current = (PrescriptionNode *)next;
    }
}

/**
 * @brief 统计处方链表节点总数
 * @param head 链表头指针
 * @return int 节点数量
 */
int count_prescription_list(PrescriptionNode *head) {
    int count = 0;
    PrescriptionNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// ==================== 链表版本的数据加载和保存函数 ====================
// 以下函数负责将二进制/文本文件中的数据加载到内存链表中，或将链表数据持久化到文件

/**
 * @brief 从文件加载所有用户信息
 * @return UserNode* 用户链表头指针，失败或文件为空返回 NULL
 */
UserNode* load_users_list(void) {
    FILE *fp = fopen(USERS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    UserNode *head = NULL;
    UserNode *tail = NULL;
    User user;
    
    // 循环读取 CSV 格式的用户数据
    while (fscanf(fp, " %[^,],%[^,],%[^\n\r]", user.username, user.password, user.role) == 3) {
        UserNode *node = create_user_node(&user);
        if (!node) {
            free_user_list(head);
            fclose(fp);
            return NULL;
        }
        
        // 构建单向链表
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将用户链表保存到文件
 * @param head 用户链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_users_list(UserNode *head) {
    FILE *fp = fopen(USERS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    UserNode *current = head;
    while (current) {
        // 按 CSV 格式写入文件
        fprintf(fp, "%s,%s,%s\n", current->data.username, current->data.password, current->data.role);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有患者档案
 * @return PatientNode* 患者链表头指针
 */
PatientNode* load_patients_list(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    PatientNode *head = NULL;
    PatientNode *tail = NULL;
    Patient p;
    int emergency;
    
    // 读取患者详细信息，包括基本资料和就诊状态
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%d",
                  p.patient_id, p.username, p.name, p.gender, &p.age, p.phone,
                  p.address, p.patient_type, p.treatment_stage, &emergency) == 10) {
        p.is_emergency = (emergency != 0);
        PatientNode *node = create_patient_node(&p);
        if (!node) {
            free_patient_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将患者链表保存到文件
 * @param head 患者链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_patients_list(PatientNode *head) {
    FILE *fp = fopen(PATIENTS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    PatientNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%d,%s,%s,%s,%s,%d\n",
                current->data.patient_id, current->data.username, current->data.name,
                current->data.gender, current->data.age, current->data.phone,
                current->data.address, current->data.patient_type,
                current->data.treatment_stage, current->data.is_emergency ? 1 : 0);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有医生档案
 * @return DoctorNode* 医生链表头指针
 */
DoctorNode* load_doctors_list(void) {
    FILE *fp = fopen(DOCTORS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DoctorNode *head = NULL;
    DoctorNode *tail = NULL;
    Doctor d;
    
    // 读取医生信息，包括所属科室、职称及忙碌程度
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%[^,],%d",
                  d.doctor_id, d.username, d.name, d.department_id, d.title, &d.busy_level) == 6) {
        DoctorNode *node = create_doctor_node(&d);
        if (!node) {
            free_doctor_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将医生链表保存到文件
 * @param head 医生链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_doctors_list(DoctorNode *head) {
    FILE *fp = fopen(DOCTORS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    DoctorNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%s,%d\n",
                current->data.doctor_id, current->data.username, current->data.name,
                current->data.department_id, current->data.title, current->data.busy_level);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有科室信息
 * @return DepartmentNode* 科室链表头指针
 */
DepartmentNode* load_departments_list(void) {
    FILE *fp = fopen(DEPARTMENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DepartmentNode *head = NULL;
    DepartmentNode *tail = NULL;
    Department d;
    
    // 读取科室基本资料
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^\n\r]",
                  d.department_id, d.name, d.leader, d.phone) == 4) {
        DepartmentNode *node = create_department_node(&d);
        if (!node) {
            free_department_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将科室链表保存到文件
 * @param head 科室链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_departments_list(DepartmentNode *head) {
    FILE *fp = fopen(DEPARTMENTS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    DepartmentNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s\n",
                current->data.department_id, current->data.name,
                current->data.leader, current->data.phone);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有药品信息
 * @return DrugNode* 药品链表头指针
 */
DrugNode* load_drugs_list(void) {
    FILE *fp = fopen(DRUGS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DrugNode *head = NULL;
    DrugNode *tail = NULL;
    Drug d;
    int special;
    
    // 读取药品资料，包括价格、库存及报销比例
    while (fscanf(fp, " %[^,],%[^,],%f,%d,%d,%d,%f",
                  d.drug_id, d.name, &d.price, &d.stock_num, &d.warning_line, &special, &d.reimbursement_ratio) == 7) {
        d.is_special = (special != 0);
        DrugNode *node = create_drug_node(&d);
        if (!node) {
            free_drug_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将药品链表保存到文件
 * @param head 药品链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_drugs_list(DrugNode *head) {
    FILE *fp = fopen(DRUGS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    DrugNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%.2f,%d,%d,%d,%.2f\n",
                current->data.drug_id, current->data.name, current->data.price,
                current->data.stock_num, current->data.warning_line,
                current->data.is_special ? 1 : 0, current->data.reimbursement_ratio);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有病房信息
 * @return WardNode* 病房链表头指针
 */
WardNode* load_wards_list(void) {
    FILE *fp = fopen(WARDS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    WardNode *head = NULL;
    WardNode *tail = NULL;
    Ward w;
    
    // 读取病房资源状态
    while (fscanf(fp, " %[^,],%[^,],%d,%d,%d",
                  w.ward_id, w.type, &w.total_beds, &w.remain_beds, &w.warning_line) == 5) {
        WardNode *node = create_ward_node(&w);
        if (!node) {
            free_ward_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将病房链表保存到文件
 * @param head 病房链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_wards_list(WardNode *head) {
    FILE *fp = fopen(WARDS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    WardNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%d,%d,%d\n",
                current->data.ward_id, current->data.type,
                current->data.total_beds, current->data.remain_beds, current->data.warning_line);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有挂号预约记录
 * @return AppointmentNode* 预约链表头指针
 */
AppointmentNode* load_appointments_list(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    AppointmentNode *head = NULL;
    AppointmentNode *tail = NULL;
    Appointment a;
    
    // 读取挂号流水信息
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n\r]",
                  a.appointment_id, a.patient_id, a.doctor_id, a.department_id,
                  a.appointment_date, a.appointment_time, a.status, a.create_time) == 8) {
        AppointmentNode *node = create_appointment_node(&a);
        if (!node) {
            free_appointment_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将预约链表保存到文件
 * @param head 预约链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_appointments_list(AppointmentNode *head) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    AppointmentNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n",
                current->data.appointment_id, current->data.patient_id,
                current->data.doctor_id, current->data.department_id,
                current->data.appointment_date, current->data.appointment_time,
                current->data.status, current->data.create_time);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有病历记录
 * @return MedicalRecordNode* 病历链表头指针
 */
MedicalRecordNode* load_medical_records_list(void) {
    FILE *fp = fopen(MEDICAL_RECORDS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    MedicalRecordNode *head = NULL;
    MedicalRecordNode *tail = NULL;
    MedicalRecord m;
    
    // 读取诊断结果及病历状态
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n\r]",
                  m.record_id, m.patient_id, m.doctor_id, m.appointment_id,
                  m.diagnosis, m.diagnosis_date, m.status) == 7) {
        MedicalRecordNode *node = create_medical_record_node(&m);
        if (!node) {
            free_medical_record_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将病历链表保存到文件
 * @param head 病历链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_medical_records_list(MedicalRecordNode *head) {
    FILE *fp = fopen(MEDICAL_RECORDS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    MedicalRecordNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n",
                current->data.record_id, current->data.patient_id,
                current->data.doctor_id, current->data.appointment_id,
                current->data.diagnosis, current->data.diagnosis_date, current->data.status);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

/**
 * @brief 从文件加载所有处方信息
 * @return PrescriptionNode* 处方链表头指针
 */
PrescriptionNode* load_prescriptions_list(void) {
    FILE *fp = fopen(PRESCRIPTIONS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    PrescriptionNode *head = NULL;
    PrescriptionNode *tail = NULL;
    Prescription p;
    
    // 读取处方明细，包括药品、数量及总价
    while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n\r]",
                  p.prescription_id, p.record_id, p.patient_id, p.doctor_id, p.drug_id,
                  &p.quantity, &p.total_price, p.prescription_date) == 8) {
        PrescriptionNode *node = create_prescription_node(&p);
        if (!node) {
            free_prescription_list(head);
            fclose(fp);
            return NULL;
        }
        
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    fclose(fp);
    return head;
}

/**
 * @brief 将处方链表保存到文件
 * @param head 处方链表头指针
 * @return int SUCCESS 或 ERROR_FILE_IO
 */
int save_prescriptions_list(PrescriptionNode *head) {
    FILE *fp = fopen(PRESCRIPTIONS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    PrescriptionNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%s,%d,%.2f,%s\n",
                current->data.prescription_id, current->data.record_id,
                current->data.patient_id, current->data.doctor_id,
                current->data.drug_id, current->data.quantity,
                current->data.total_price, current->data.prescription_date);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

// ==================== 辅助查询与维护函数 ====================
// 以下函数提供基于特定字段的快速查询及档案自动补全功能

/**
 * @brief 根据用户名查找患者档案
 * @param username 用户名
 * @return Patient* 匹配的患者数据指针（需手动释放），未找到返回 NULL
 */
Patient* find_patient_by_username(const char *username) {
    PatientNode *head = load_patients_list();
    if (!head) {
        return NULL;
    }
    
    PatientNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            Patient *patient = (Patient *)malloc(sizeof(Patient));
            if (patient) {
                *patient = current->data;
            }
            free_patient_list(head);
            return patient;
        }
        current = current->next;
    }
    
    free_patient_list(head);
    return NULL;
}

/**
 * @brief 根据患者 ID 查找患者档案
 * @param patient_id 患者唯一标识符
 * @return Patient* 匹配的患者数据指针（需手动释放）
 */
Patient* find_patient_by_id(const char *patient_id) {
    PatientNode *head = load_patients_list();
    if (!head) {
        return NULL;
    }
    
    PatientNode *current = head;
    while (current) {
        if (strcmp(current->data.patient_id, patient_id) == 0) {
            Patient *patient = (Patient *)malloc(sizeof(Patient));
            if (patient) {
                *patient = current->data;
            }
            free_patient_list(head);
            return patient;
        }
        current = current->next;
    }
    
    free_patient_list(head);
    return NULL;
}

/**
 * @brief 确保患者档案存在（自动补全）
 * 
 * 检查指定用户名的患者档案是否存在。如果不存在，则自动生成一个新的患者档案
 * 并赋予默认值，确保系统业务逻辑的连续性。
 * 
 * @param username 用户名
 * @return int SUCCESS 或错误码
 */
int ensure_patient_profile(const char *username) {
    PatientNode *head = load_patients_list();
    if (!head) {
        // 档案库为空，直接创建首个患者
        Patient new_patient = {0};
        generate_id(new_patient.patient_id, MAX_ID, "P");
        strcpy(new_patient.username, username);
        strcpy(new_patient.name, username);
        strcpy(new_patient.gender, "未知");
        strcpy(new_patient.patient_type, "普通");
        strcpy(new_patient.treatment_stage, "初诊");
        new_patient.is_emergency = false;
        
        PatientNode *node = create_patient_node(&new_patient);
        if (!node) {
            return ERROR_FILE_IO;
        }
        
        int result = save_patients_list(node);
        free_patient_list(node);
        return result;
    }
    
    // 遍历检查是否已存在同名档案
    PatientNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            free_patient_list(head);
            return SUCCESS;
        }
        current = current->next;
    }
    
    // 档案不存在，追加新档案
    Patient new_patient = {0};
    generate_id(new_patient.patient_id, MAX_ID, "P");
    strcpy(new_patient.username, username);
    strcpy(new_patient.name, username);
    strcpy(new_patient.gender, "未知");
    strcpy(new_patient.patient_type, "普通");
    strcpy(new_patient.treatment_stage, "初诊");
    new_patient.is_emergency = false;
    
    PatientNode *node = create_patient_node(&new_patient);
    if (!node) {
        free_patient_list(head);
        return ERROR_FILE_IO;
    }
    
    // 挂载到链表尾部
    PatientNode *tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
    
    int result = save_patients_list(head);
    free_patient_list(head);
    return result;
}

/**
 * @brief 根据用户名查找医生档案
 * @param username 用户名
 * @return Doctor* 匹配的医生数据指针（需手动释放）
 */
Doctor* find_doctor_by_username(const char *username) {
    DoctorNode *head = load_doctors_list();
    if (!head) {
        return NULL;
    }
    
    DoctorNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            Doctor *doctor = (Doctor *)malloc(sizeof(Doctor));
            if (doctor) {
                *doctor = current->data;
            }
            free_doctor_list(head);
            return doctor;
        }
        current = current->next;
    }
    
    free_doctor_list(head);
    return NULL;
}

/**
 * @brief 根据医生 ID 查找医生档案
 * @param doctor_id 医生唯一标识符
 * @return Doctor* 匹配的医生数据指针（需手动释放）
 */
Doctor* find_doctor_by_id(const char *doctor_id) {
    DoctorNode *head = load_doctors_list();
    if (!head) {
        return NULL;
    }
    
    DoctorNode *current = head;
    while (current) {
        if (strcmp(current->data.doctor_id, doctor_id) == 0) {
            Doctor *doctor = (Doctor *)malloc(sizeof(Doctor));
            if (doctor) {
                *doctor = current->data;
            }
            free_doctor_list(head);
            return doctor;
        }
        current = current->next;
    }
    
    free_doctor_list(head);
    return NULL;
}

/**
 * @brief 确保医生档案存在（自动补全）
 * 
 * 检查指定用户名的医生档案是否存在。如果不存在，则自动生成一个新的医生档案。
 * 
 * @param username 用户名
 * @return int SUCCESS 或错误码
 */
int ensure_doctor_profile(const char *username) {
    DoctorNode *head = load_doctors_list();
    if (!head) {
        // 档案库为空，创建首个医生
        Doctor new_doctor = {0};
        generate_id(new_doctor.doctor_id, MAX_ID, "D");
        strcpy(new_doctor.username, username);
        strcpy(new_doctor.name, username);
        strcpy(new_doctor.title, "医生");
        
        DoctorNode *node = create_doctor_node(&new_doctor);
        if (!node) {
            return ERROR_FILE_IO;
        }
        
        int result = save_doctors_list(node);
        free_doctor_list(node);
        return result;
    }
    
    // 检查是否已存在
    DoctorNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            free_doctor_list(head);
            return SUCCESS;
        }
        current = current->next;
    }
    
    // 添加新医生档案
    Doctor new_doctor = {0};
    generate_id(new_doctor.doctor_id, MAX_ID, "D");
    strcpy(new_doctor.username, username);
    strcpy(new_doctor.name, username);
    strcpy(new_doctor.title, "医生");
    
    DoctorNode *node = create_doctor_node(&new_doctor);
    if (!node) {
        free_doctor_list(head);
        return ERROR_FILE_IO;
    }
    
    // 挂载到链表尾部
    DoctorNode *tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
    
    int result = save_doctors_list(head);
    free_doctor_list(head);
    return result;
}

/**
 * @brief 根据药品 ID 查找药品信息
 * @param drug_id 药品唯一标识符
 * @return Drug* 匹配的药品数据指针（需手动释放）
 */
Drug* find_drug_by_id(const char *drug_id) {
    DrugNode *head = load_drugs_list();
    if (!head) {
        return NULL;
    }
    
    DrugNode *current = head;
    while (current) {
        if (strcmp(current->data.drug_id, drug_id) == 0) {
            Drug *drug = (Drug *)malloc(sizeof(Drug));
            if (drug) {
                *drug = current->data;
            }
            free_drug_list(head);
            return drug;
        }
        current = current->next;
    }
    
    free_drug_list(head);
    return NULL;
}

/**
 * @brief 查找指定患者的所有挂号预约记录
 * @param patient_id 患者唯一标识符
 * @return Appointment* 匹配的首条预约记录指针（需手动释放）
 * @note 当前实现仅返回查找到的第一条记录，后续可扩展为返回链表
 */
Appointment* find_appointments_by_patient(const char *patient_id) {
    AppointmentNode *head = load_appointments_list();
    if (!head) {
        return NULL;
    }
    
    AppointmentNode *current = head;
    while (current) {
        if (strcmp(current->data.patient_id, patient_id) == 0) {
            Appointment *appointment = (Appointment *)malloc(sizeof(Appointment));
            if (appointment) {
                *appointment = current->data;
            }
            free_appointment_list(head);
            return appointment;
        }
        current = current->next;
    }
    
    free_appointment_list(head);
    return NULL;
}

/**
 * @brief 查找指定医生的所有接诊预约记录
 * @param doctor_id 医生唯一标识符
 * @return Appointment* 匹配的首条预约记录指针（需手动释放）
 */
Appointment* find_appointments_by_doctor(const char *doctor_id) {
    AppointmentNode *head = load_appointments_list();
    if (!head) {
        return NULL;
    }
    
    AppointmentNode *current = head;
    while (current) {
        if (strcmp(current->data.doctor_id, doctor_id) == 0) {
            Appointment *appointment = (Appointment *)malloc(sizeof(Appointment));
            if (appointment) {
                *appointment = current->data;
            }
            free_appointment_list(head);
            return appointment;
        }
        current = current->next;
    }
    
    free_appointment_list(head);
    return NULL;
}

/**
 * @brief 查找指定患者的所有病历记录
 * @param patient_id 患者唯一标识符
 * @return MedicalRecord* 匹配的首条病历记录指针（需手动释放）
 */
MedicalRecord* find_records_by_patient(const char *patient_id) {
    MedicalRecordNode *head = load_medical_records_list();
    if (!head) {
        return NULL;
    }
    
    MedicalRecordNode *current = head;
    while (current) {
        if (strcmp(current->data.patient_id, patient_id) == 0) {
            MedicalRecord *record = (MedicalRecord *)malloc(sizeof(MedicalRecord));
            if (record) {
                *record = current->data;
            }
            free_medical_record_list(head);
            return record;
        }
        current = current->next;
    }
    
    free_medical_record_list(head);
    return NULL;
}
