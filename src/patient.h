#ifndef PATIENT_H
#define PATIENT_H

#include "common.h"
#include "data_storage.h"

/**
 * @brief 患者模块主菜单
 * 
 * 提供患者功能的入口，包括挂号、查询、个人信息管理等。
 * 
 * @param current_user 当前登录的用户指针
 */
void patient_main_menu(const User *current_user);

/**
 * @brief 患者挂号菜单
 * 
 * 引导患者选择科室和医生进行挂号登记。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码，成功返回 SUCCESS
 */
int patient_register_menu(const User *current_user);

/**
 * @brief 挂号状态查询菜单
 * 
 * 患者可以查看自己当前的挂号信息及排队状态。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码
 */
int patient_appointment_menu(const User *current_user);

/**
 * @brief 诊断结果查询菜单
 * 
 * 患者查看医生开具的诊断建议、处方及医嘱。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码
 */
int patient_query_diagnosis_menu(const User *current_user);

/**
 * @brief 病房信息查看菜单
 * 
 * 住院患者查看所属病房、床位号及相关设施信息。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码
 */
int patient_view_ward_menu(const User *current_user);

/**
 * @brief 治疗进度查看菜单
 * 
 * 患者查看当前的治疗阶段、后续计划及康复情况。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码
 */
int patient_view_treatment_progress_menu(const User *current_user);

/**
 * @brief 辅助函数：显示所有可用科室
 * 
 * 从数据存储中读取并列出医院当前开放的所有科室信息。
 */
void show_available_departments(void);

/**
 * @brief 辅助函数：显示特定科室的医生列表
 * 
 * 根据科室ID筛选并展示该科室下所有在岗医生的信息。
 * 
 * @param department_id 科室唯一标识符
 */
void show_doctors_by_department(const char *department_id);

/**
 * @brief 修改个人信息菜单
 * 
 * 患者可以更新自己的联系方式、密码等基础档案信息。
 * 
 * @param current_user 当前登录的用户指针
 * @return int 返回操作状态码
 */
int patient_edit_profile_menu(const User *current_user);

#endif // PATIENT_H
