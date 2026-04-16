#include "data_storage.h"
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

int init_data_storage(void) {
#ifdef _WIN32
    DWORD dwAttrib = GetFileAttributesA(DATA_DIR);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        if (!CreateDirectoryA(DATA_DIR, NULL)) {
            printf("创建数据目录失败!\n");
            return ERROR_FILE_IO;
        }
    }
#else
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

UserNode* create_user_node(const User *user) {
    UserNode *node = (UserNode *)malloc(sizeof(UserNode));
    if (node) {
        node->data = *user;
        node->next = NULL;
    }
    return node;
}

void free_user_list(UserNode *head) {
    UserNode *current = head;
    while (current) {
        UserNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_user_list(UserNode *head) {
    int count = 0;
    UserNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

PatientNode* create_patient_node(const Patient *patient) {
    PatientNode *node = (PatientNode *)malloc(sizeof(PatientNode));
    if (node) {
        node->data = *patient;
        node->next = NULL;
    }
    return node;
}

void free_patient_list(PatientNode *head) {
    PatientNode *current = head;
    while (current) {
        PatientNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_patient_list(PatientNode *head) {
    int count = 0;
    PatientNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

DoctorNode* create_doctor_node(const Doctor *doctor) {
    DoctorNode *node = (DoctorNode *)malloc(sizeof(DoctorNode));
    if (node) {
        node->data = *doctor;
        node->next = NULL;
    }
    return node;
}

void free_doctor_list(DoctorNode *head) {
    DoctorNode *current = head;
    while (current) {
        DoctorNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_doctor_list(DoctorNode *head) {
    int count = 0;
    DoctorNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

DepartmentNode* create_department_node(const Department *department) {
    DepartmentNode *node = (DepartmentNode *)malloc(sizeof(DepartmentNode));
    if (node) {
        node->data = *department;
        node->next = NULL;
    }
    return node;
}

void free_department_list(DepartmentNode *head) {
    DepartmentNode *current = head;
    while (current) {
        DepartmentNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_department_list(DepartmentNode *head) {
    int count = 0;
    DepartmentNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

DrugNode* create_drug_node(const Drug *drug) {
    DrugNode *node = (DrugNode *)malloc(sizeof(DrugNode));
    if (node) {
        node->data = *drug;
        node->next = NULL;
    }
    return node;
}

void free_drug_list(DrugNode *head) {
    DrugNode *current = head;
    while (current) {
        DrugNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_drug_list(DrugNode *head) {
    int count = 0;
    DrugNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

WardNode* create_ward_node(const Ward *ward) {
    WardNode *node = (WardNode *)malloc(sizeof(WardNode));
    if (node) {
        node->data = *ward;
        node->next = NULL;
    }
    return node;
}

void free_ward_list(WardNode *head) {
    WardNode *current = head;
    while (current) {
        WardNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_ward_list(WardNode *head) {
    int count = 0;
    WardNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

AppointmentNode* create_appointment_node(const Appointment *appointment) {
    AppointmentNode *node = (AppointmentNode *)malloc(sizeof(AppointmentNode));
    if (node) {
        node->data = *appointment;
        node->next = NULL;
    }
    return node;
}

void free_appointment_list(AppointmentNode *head) {
    AppointmentNode *current = head;
    while (current) {
        AppointmentNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_appointment_list(AppointmentNode *head) {
    int count = 0;
    AppointmentNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

MedicalRecordNode* create_medical_record_node(const MedicalRecord *record) {
    MedicalRecordNode *node = (MedicalRecordNode *)malloc(sizeof(MedicalRecordNode));
    if (node) {
        node->data = *record;
        node->next = NULL;
    }
    return node;
}

void free_medical_record_list(MedicalRecordNode *head) {
    MedicalRecordNode *current = head;
    while (current) {
        MedicalRecordNode *next = current->next;
        free(current);
        current = next;
    }
}

int count_medical_record_list(MedicalRecordNode *head) {
    int count = 0;
    MedicalRecordNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

PrescriptionNode* create_prescription_node(const Prescription *prescription) {
    PrescriptionNode *node = (PrescriptionNode *)malloc(sizeof(PrescriptionNode));
    if (node) {
        node->data = *prescription;
        node->next = NULL;
    }
    return node;
}

void free_prescription_list(PrescriptionNode *head) {
    PrescriptionNode *current = head;
    while (current) {
        PrescriptionNode *next = current->next;
        free(current);
        current = next;
    }
}

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

UserNode* load_users_list(void) {
    FILE *fp = fopen(USERS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    UserNode *head = NULL;
    UserNode *tail = NULL;
    User user;
    
    while (fscanf(fp, " %[^,],%[^,],%[^\n\r]", user.username, user.password, user.role) == 3) {
        UserNode *node = create_user_node(&user);
        if (!node) {
            free_user_list(head);
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

int save_users_list(UserNode *head) {
    FILE *fp = fopen(USERS_FILE, "w");
    if (!fp) {
        return ERROR_FILE_IO;
    }
    
    UserNode *current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s\n", current->data.username, current->data.password, current->data.role);
        current = current->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

PatientNode* load_patients_list(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    PatientNode *head = NULL;
    PatientNode *tail = NULL;
    Patient p;
    int emergency;
    
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

DoctorNode* load_doctors_list(void) {
    FILE *fp = fopen(DOCTORS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DoctorNode *head = NULL;
    DoctorNode *tail = NULL;
    Doctor d;
    
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

DepartmentNode* load_departments_list(void) {
    FILE *fp = fopen(DEPARTMENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DepartmentNode *head = NULL;
    DepartmentNode *tail = NULL;
    Department d;
    
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

DrugNode* load_drugs_list(void) {
    FILE *fp = fopen(DRUGS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    DrugNode *head = NULL;
    DrugNode *tail = NULL;
    Drug d;
    int special;
    
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

WardNode* load_wards_list(void) {
    FILE *fp = fopen(WARDS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    WardNode *head = NULL;
    WardNode *tail = NULL;
    Ward w;
    
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

AppointmentNode* load_appointments_list(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    AppointmentNode *head = NULL;
    AppointmentNode *tail = NULL;
    Appointment a;
    
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

MedicalRecordNode* load_medical_records_list(void) {
    FILE *fp = fopen(MEDICAL_RECORDS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    MedicalRecordNode *head = NULL;
    MedicalRecordNode *tail = NULL;
    MedicalRecord m;
    
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

PrescriptionNode* load_prescriptions_list(void) {
    FILE *fp = fopen(PRESCRIPTIONS_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    PrescriptionNode *head = NULL;
    PrescriptionNode *tail = NULL;
    Prescription p;
    
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

// ==================== Helper Functions ====================

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

int ensure_patient_profile(const char *username) {
    PatientNode *head = load_patients_list();
    if (!head) {
        // 创建新患者
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
    
    // 检查是否已存在
    PatientNode *current = head;
    while (current) {
        if (strcmp(current->data.username, username) == 0) {
            free_patient_list(head);
            return SUCCESS;
        }
        current = current->next;
    }
    
    // 添加新患者
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
    
    // 找到链表尾部
    PatientNode *tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
    
    int result = save_patients_list(head);
    free_patient_list(head);
    return result;
}

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

int ensure_doctor_profile(const char *username) {
    DoctorNode *head = load_doctors_list();
    if (!head) {
        // 创建新医生
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
    
    // 添加新医生
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
    
    // 找到链表尾部
    DoctorNode *tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
    
    int result = save_doctors_list(head);
    free_doctor_list(head);
    return result;
}

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

