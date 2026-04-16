#ifndef DOCTOR_H
#define DOCTOR_H

#include "common.h"

/**
 * @brief 医生模块主菜单
 * 
 * 提供医生功能的入口，包括接诊、开药、病房管理等。
 * 
 * @param current_user 当前登录的医生用户指针
 */
void doctor_main_menu(const User *current_user);

/**
 * @brief 挂号提醒菜单
 * 
 * 医生查看当前待诊患者列表及挂号顺序。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_appointment_reminder_menu(const User *current_user);

/**
 * @brief 接诊处理菜单
 * 
 * 医生对患者进行诊断，记录病情并开具诊断建议。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_consultation_menu(const User *current_user);

/**
 * @brief 开药/处方菜单
 * 
 * 医生根据诊断结果为患者开具药品处方。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_prescribe_menu(const User *current_user);

/**
 * @brief 病房呼叫提醒菜单
 * 
 * 医生接收并处理来自负责病房的紧急呼叫或查房提醒。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_ward_call_menu(const User *current_user);

/**
 * @brief 紧急患者标记菜单
 * 
 * 医生将特定患者标记为紧急状态，以便优先安排治疗。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_emergency_flag_menu(const User *current_user);

/**
 * @brief 更新治疗进度菜单
 * 
 * 医生根据患者康复情况更新其当前的治疗阶段。
 * 
 * @param current_user 当前登录的医生用户指针
 * @return int 返回操作状态码
 */
int doctor_update_progress_menu(const User *current_user);

#endif // DOCTOR_H
