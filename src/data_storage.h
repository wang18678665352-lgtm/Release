#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include "common.h"

/**
 * @brief 数据文件存储目录及路径配置
 * 定义了系统内所有 CSV 文本数据文件的相对路径
 */
#define DATA_DIR "data"
#define USERS_FILE DATA_DIR "/users.txt"
#define PATIENTS_FILE DATA_DIR "/patients.txt"
#define DOCTORS_FILE DATA_DIR "/doctors.txt"
#define DEPARTMENTS_FILE DATA_DIR "/departments.txt"
#define DRUGS_FILE DATA_DIR "/drugs.txt"
#define WARDS_FILE DATA_DIR "/wards.txt"
#define APPOINTMENTS_FILE DATA_DIR "/appointments.txt"
#define MEDICAL_RECORDS_FILE DATA_DIR "/medical_records.txt"
#define PRESCRIPTIONS_FILE DATA_DIR "/prescriptions.txt"

// ==================== 核心业务数据结构定义 ====================

/**
 * @brief 患者档案结构体
 * 记录患者的个人基本信息及就诊状态
 */
typedef struct {
    char patient_id[MAX_ID];        // 患者唯一业务标识 (前缀: P)
    char username[MAX_USERNAME];    // 绑定的登录账号名
    char name[MAX_NAME];            // 真实姓名
    char gender[10];                // 性别 (男/女/未知)
    int age;                        // 年龄
    char phone[20];                 // 联系电话
    char address[200];              // 家庭住址
    char patient_type[20];          // 患者类型 (普通/VIP等)
    char treatment_stage[20];       // 治疗阶段 (初诊/复诊/住院等)
    bool is_emergency;              // 是否为急诊标志
} Patient;

/**
 * @brief 医生档案结构体
 * 记录医生的基本信息和排班状态
 */
typedef struct {
    char doctor_id[MAX_ID];         // 医生唯一业务标识 (前缀: D)
    char username[MAX_USERNAME];    // 绑定的登录账号名
    char name[MAX_NAME];            // 医生真实姓名
    char department_id[MAX_ID];     // 所属科室的ID
    char title[50];                 // 职称 (主任医师/副主任医师等)
    int busy_level;                 // 忙碌程度指标 (排队人数或工作量度量)
} Doctor;

/**
 * @brief 科室结构体
 * 记录医院行政科室信息
 */
typedef struct {
    char department_id[MAX_ID];     // 科室唯一业务标识
    char name[MAX_NAME];            // 科室名称 (内科/外科等)
    char leader[MAX_NAME];          // 科室主任姓名
    char phone[20];                 // 科室内部联系电话
} Department;

/**
 * @brief 药品信息结构体
 * 记录药房药品的库存及价格体系
 */
typedef struct {
    char drug_id[MAX_ID];           // 药品唯一业务标识
    char name[MAX_NAME];            // 药品名称
    float price;                    // 药品单价
    int stock_num;                  // 当前库存数量
    int warning_line;               // 库存预警线 (低于此值需提示采购)
    bool is_special;                // 是否为特管药品 (处方药/管制药)
    float reimbursement_ratio;      // 医保报销比例 (0.0 - 1.0)
} Drug;

/**
 * @brief 病房资源结构体
 * 记录医院床位资源的分配情况
 */
typedef struct {
    char ward_id[MAX_ID];           // 病房唯一业务标识
    char type[50];                  // 病房类型 (普通/ICU/VIP等)
    int total_beds;                 // 总床位数
    int remain_beds;                // 空余床位数
    int warning_line;               // 床位紧张预警线
} Ward;

/**
 * @brief 挂号预约结构体
 * 记录患者挂号的时间、科室、医生及当前状态
 */
typedef struct {
    char appointment_id[MAX_ID];    // 挂号单唯一标识
    char patient_id[MAX_ID];        // 关联的患者ID
    char doctor_id[MAX_ID];         // 预约的医生ID
    char department_id[MAX_ID];     // 预约的科室ID
    char appointment_date[20];      // 预约日期 (YYYY-MM-DD)
    char appointment_time[20];      // 预约具体时间段
    char status[20];                // 挂号状态 (待就诊/已就诊/已取消)
    char create_time[30];           // 订单创建时间戳
} Appointment;

/**
 * @brief 医疗诊断记录结构体
 * 记录医生对患者的诊断结果
 */
typedef struct {
    char record_id[MAX_ID];         // 诊断记录唯一标识
    char patient_id[MAX_ID];        // 关联患者
    char doctor_id[MAX_ID];         // 做出诊断的医生
    char appointment_id[MAX_ID];    // 关联的挂号单ID
    char diagnosis[500];            // 诊断结论详情
    char diagnosis_date[20];        // 诊断日期
    char status[20];                // 病历状态
} MedicalRecord;

/**
 * @brief 处方单结构体
 * 记录医生为患者开具的用药明细及费用
 */
typedef struct {
    char prescription_id[MAX_ID];   // 处方单唯一标识
    char record_id[MAX_ID];         // 关联的诊断记录ID
    char patient_id[MAX_ID];        // 患者ID
    char doctor_id[MAX_ID];         // 开方医生ID
    char drug_id[MAX_ID];           // 药品ID
    int quantity;                   // 开具数量
    float total_price;              // 该项总价
    char prescription_date[20];     // 开方日期
} Prescription;

// 链表节点结构定义
typedef struct UserNode {
    User data;
    struct UserNode *next;
} UserNode;

typedef struct PatientNode {
    Patient data;
    struct PatientNode *next;
} PatientNode;

typedef struct DoctorNode {
    Doctor data;
    struct DoctorNode *next;
} DoctorNode;

typedef struct DepartmentNode {
    Department data;
    struct DepartmentNode *next;
} DepartmentNode;

typedef struct DrugNode {
    Drug data;
    struct DrugNode *next;
} DrugNode;

typedef struct WardNode {
    Ward data;
    struct WardNode *next;
} WardNode;

typedef struct AppointmentNode {
    Appointment data;
    struct AppointmentNode *next;
} AppointmentNode;

typedef struct MedicalRecordNode {
    MedicalRecord data;
    struct MedicalRecordNode *next;
} MedicalRecordNode;

typedef struct PrescriptionNode {
    Prescription data;
    struct PrescriptionNode *next;
} PrescriptionNode;

int init_data_storage(void);

// 链表操作函数
UserNode* create_user_node(const User *user);
void free_user_list(UserNode *head);
int count_user_list(UserNode *head);

PatientNode* create_patient_node(const Patient *patient);
void free_patient_list(PatientNode *head);
int count_patient_list(PatientNode *head);

DoctorNode* create_doctor_node(const Doctor *doctor);
void free_doctor_list(DoctorNode *head);
int count_doctor_list(DoctorNode *head);

DepartmentNode* create_department_node(const Department *department);
void free_department_list(DepartmentNode *head);
int count_department_list(DepartmentNode *head);

DrugNode* create_drug_node(const Drug *drug);
void free_drug_list(DrugNode *head);
int count_drug_list(DrugNode *head);

WardNode* create_ward_node(const Ward *ward);
void free_ward_list(WardNode *head);
int count_ward_list(WardNode *head);

AppointmentNode* create_appointment_node(const Appointment *appointment);
void free_appointment_list(AppointmentNode *head);
int count_appointment_list(AppointmentNode *head);

MedicalRecordNode* create_medical_record_node(const MedicalRecord *record);
void free_medical_record_list(MedicalRecordNode *head);
int count_medical_record_list(MedicalRecordNode *head);

PrescriptionNode* create_prescription_node(const Prescription *prescription);
void free_prescription_list(PrescriptionNode *head);
int count_prescription_list(PrescriptionNode *head);

// 数据加载和保存函数
UserNode* load_users_list(void);
int save_users_list(UserNode *head);

PatientNode* load_patients_list(void);
int save_patients_list(PatientNode *head);
Patient* find_patient_by_username(const char *username);
Patient* find_patient_by_id(const char *patient_id);
int ensure_patient_profile(const char *username);

DoctorNode* load_doctors_list(void);
int save_doctors_list(DoctorNode *head);
Doctor* find_doctor_by_username(const char *username);
Doctor* find_doctor_by_id(const char *doctor_id);
int ensure_doctor_profile(const char *username);

DepartmentNode* load_departments_list(void);
int save_departments_list(DepartmentNode *head);

DrugNode* load_drugs_list(void);
int save_drugs_list(DrugNode *head);
Drug* find_drug_by_id(const char *drug_id);

WardNode* load_wards_list(void);
int save_wards_list(WardNode *head);

AppointmentNode* load_appointments_list(void);
int save_appointments_list(AppointmentNode *head);
Appointment* find_appointments_by_patient(const char *patient_id);
Appointment* find_appointments_by_doctor(const char *doctor_id);

MedicalRecordNode* load_medical_records_list(void);
int save_medical_records_list(MedicalRecordNode *head);
MedicalRecord* find_records_by_patient(const char *patient_id);

PrescriptionNode* load_prescriptions_list(void);
int save_prescriptions_list(PrescriptionNode *head);

#endif // DATA_STORAGE_H
