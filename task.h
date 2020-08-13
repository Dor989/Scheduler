#ifndef __TASK_H__
#define __TASK_H__

#include "../uid/uid.h" /* ilrd_uid_t, time_t */

typedef struct task task_t;
typedef int (*op_func_t)(void *func_params);

/* in c file: */
/*
struct task
{
    ilrd_uid_t uid;
    op_func_t op_func;
    void *func_params;
    size_t interval;
    time_t exec_time;
    int exec_state;
};
*/

/* DESCRIPTION:
 * create task with user defined op_func, which will receive func_params
 * and will be executed according to the interval time. 
 * in addition, a UID will be generated for the task.
 * 
 * @param:
 * op_func		user defined function
 * func_params	parameters for user defined function
 * interval		time interval to perform the task (in seconds)
 *
 * @return:
 * pointer to new task, if creation failed - return NULL
 */
task_t *TaskCreate(int (*op_func)(void *func_params), 
									void *func_params, 
									size_t interval);

/* DESCRIPTION:
 * destroy given task.
 * 
 * @param:
 * task			pointer to task to destroy
 */
void TaskDestroy(task_t *task);

/* DESCRIPTION:
 * execute given task.
 * 
 * @param:
 * task			pointer to task to execute.
 *
 * @return:
 * value returned from executed function
 */
int TaskExecute(task_t *task);

/* DESCRIPTION:
 * set the execute time of a given task.
 * 
 * @param:
 * task					pointer to task.
 * new_execution_time	user defined execution time.
 */
void TaskSetExecutionTime(task_t *task, time_t new_execution_time);

/* DESCRIPTION:
 * get the execute time of a given task.
 * 
 * @param:
 * task			pointer to task.
 *
 * @return:
 * execution time.
 */
time_t TaskGetExecutionTime(const task_t *task);

/* DESCRIPTION:
 * get the interval time of a give task.
 * 
 * @param:
 * task			pointer to task.
 *
 * @return:
 * interval time.
 */
size_t TaskGetInterval(const task_t *task);

/* DESCRIPTION:
 * turn off (0) the execution state of a give task.
 * 
 * @param:
 * task			pointer to task.
 */
void TaskShutDown(task_t *task);

/* DESCRIPTION:
 * turn on (1) the execution state of a give task.
 * 
 * @param:
 * task			pointer to task.
 */
void TaskTurnOn(task_t *task);

/* DESCRIPTION:
 * checks the execution state of a give task.
 * 
 * @param:
 * task			pointer to task.
 *
 * @return:
 * 1 for on, 0 for off.
 */
int TaskIsTurnedOn(task_t *task);

/* DESCRIPTION:
 * get the unique ID of a given task.
 * 
 * @param:
 * task			pointer to task to destroy
 * 
 * return:
 * task's unique ID
 */
ilrd_uid_t TaskGetUid(task_t *task);

#endif /* __TASK_H__ */

