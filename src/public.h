#ifndef PUBLIC_H
#define PUBLIC_H

#include "common.h"

/**
 * @brief 输入合法性校验函数
 * 
 * 根据指定的类型对用户输入的字符串进行校验，确保符合医疗系统的业务规范。
 * 
 * @param input 待校验的输入字符串
 * @param type 校验类型（如：手机号、身份证号、姓名等）
 * @return true 输入合法
 * @return false 输入不合法
 */
bool validate_input(const char *input, int type);

/**
 * @brief 校验字符串是否为合法数字
 * 
 * 用于金额、年龄、工号等数值字段的初步格式校验。
 * 
 * @param str 待校验的字符串
 * @return true 是合法数字
 * @return false 包含非数字字符
 */
bool is_valid_number(const char *str);

/**
 * @brief 校验日期格式是否合法
 * 
 * 检查日期字符串是否符合 YYYY-MM-DD 格式，并验证日期的逻辑正确性（如月份、天数范围）。
 * 
 * @param date 待校验的日期字符串
 * @return true 日期合法
 * @return false 日期格式错误或逻辑不合法
 */
bool is_valid_date(const char *date);

/**
 * @brief 检查 ID 的唯一性
 * 
 * 在注册或新增记录时，访问数据层校验指定的 ID 是否已存在，防止医疗档案冲突。
 * 
 * @param id 待检查的唯一标识符
 * @param id_type ID 类型（如 "patient_id", "doctor_id" 等）
 * @return true ID 唯一，可以使用
 * @return false ID 已存在，不可重复使用
 */
bool is_unique_id(const char *id, const char *id_type);

/**
 * @brief 药品库存预警检查
 * 
 * 遍历药品数据库，检查库存量是否低于安全阈值，并触发系统预警提示。
 */
void check_drug_warning(void);

/**
 * @brief 病房占用预警检查
 * 
 * 统计各科室病房的使用率，当占用率接近饱和时发出预警，便于医疗资源调度。
 */
void check_ward_warning(void);

/**
 * @brief 医疗费用报销金额计算
 * 
 * 根据患者的医保类型（如：城镇职工、城乡居民、自费等）和总金额，计算可报销的金额。
 * 
 * @param total_amount 医疗总费用
 * @param patient_type 患者医保/身份类型
 * @return float 计算得出的报销金额
 */
float calculate_reimbursement(float total_amount, const char *patient_type);

/**
 * @brief 获取诊疗流程的下一阶段
 * 
 * 根据当前的治疗状态，返回流程中的下一个标准环节（如：挂号 -> 候诊 -> 诊断 -> 缴费 -> 取药）。
 * 
 * @param current_stage 当前诊疗阶段描述
 * @return const char* 下一阶段的描述字符串
 */
const char* get_next_stage(const char *current_stage);

/**
 * @brief 智能医生推荐算法
 * 
 * 根据科室 ID，结合医生的职称、当前接诊量和评价，推荐最合适的医生。
 * 
 * @param department_id 科室唯一标识
 * @return int 推荐的医生 ID，失败返回 -1
 */
int recommend_doctor(const char *department_id);

/**
 * @brief 医疗档案归档处理
 * 
 * 将已完成诊疗的病历记录移至归档库，释放活跃数据库压力，并确保档案安全。
 * 
 * @param record_id 待归档的病历 ID
 * @return int 执行状态码（SUCCESS 或错误码）
 */
int archive_medical_record(int record_id);

#endif // PUBLIC_H
