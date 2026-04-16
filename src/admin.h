#ifndef ADMIN_H
#define ADMIN_H

/**
 * @file admin.h
 * @brief 管理员模块头文件
 * 
 * 本模块负责处理系统管理员的核心业务逻辑，包括科室、医生、患者、药物、病房及报表的后台管理。
 * 提供统一的菜单接口，用于展示和分发各项管理功能。
 */

#include "common.h"

/**
 * @brief 管理员系统主菜单
 * 
 * 展示管理员可操作的所有功能模块入口，并根据用户输入跳转至相应的子管理模块。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 */
void admin_main_menu(const User *current_user);

/**
 * @brief 科室管理子菜单
 * 
 * 提供科室信息的增删改查功能入口，包括科室名称、负责人及联系电话的管理。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_department_menu(const User *current_user);

/**
 * @brief 医生管理子菜单
 * 
 * 提供医生档案的管理功能，包括医生入职登记、所属科室分配、职称评定及排班信息维护。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_doctor_menu(const User *current_user);

/**
 * @brief 患者管理子菜单
 * 
 * 提供全院患者档案的查询与维护功能，支持对患者基本信息、就诊类型及紧急程度的后台调整。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_patient_menu(const User *current_user);

/**
 * @brief 药物管理子菜单
 * 
 * 负责药库信息的维护，包括药品入库、价格调整、库存预警线设置及医保报销比例配置。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_drug_menu(const User *current_user);

/**
 * @brief 病房管理子菜单
 * 
 * 监控全院病房资源，提供病房类型定义、床位总数调整及床位占用情况的实时查看。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_ward_menu(const User *current_user);

/**
 * @brief 报表管理子菜单
 * 
 * 生成并展示医疗系统的统计报表，如就诊量统计、药品消耗排行、病房周转率等决策支持数据。
 * 
 * @param current_user 当前登录的管理员用户信息指针
 * @return int 执行状态码，SUCCESS 表示正常退出，其他表示错误
 */
int admin_report_menu(const User *current_user);

#endif // ADMIN_H
