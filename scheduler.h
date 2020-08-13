#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "../uid/uid.h"

typedef struct scheduler scheduler_t;

/* DESCRIPTION:
 * create a scheduler 
 * 
 * @return:
 * scheduler	pointer to a new scheduler
 */
scheduler_t *SchedulerCreate();

/* DESCRIPTION:
 * destroy a given scheduler.
 * 
 * @param:
 * scheduler	pointer to a scheduler
 */
void SchedulerDestroy(scheduler_t *scheduler);

/* DESCRIPTION:
 * executes the tasks in the scheduler 
 * 
 * @param:
 * scheduler	pointer to a scheduler
 *
 * @return: 
 * exit status. 0 for success.
 */
int SchedulerExecute(scheduler_t *scheduler);

/* DESCRIPTION:
 * clears the tasks in the scheduler 
 * 
 * @param:
 * scheduler	pointer to a scheduler
 */
void SchedulerClear(scheduler_t *scheduler);

/* DESCRIPTION:
 * create task with user defined op_func, which will receive func_params
 * and will be executed according to the interval time. 
 * in addition, a UID will be generated for the task.
 * 
 * @param:
 * scheduler	pointer to a scheduler
 * op_func		user defined function
 * func_params	parameters for user defined function
 * interval		time interval to perform the task (in seconds)
 *
 * @return:
 * the uid of the inserted task
 */
ilrd_uid_t SchedulerInsertTask(scheduler_t *scheduler,
							   int (*op_func)(void *func_params),
							   void *func_params,
							   size_t interval);

/* DESCRIPTION:
 * removes a task with a given UID from the scheduler 
 * 
 * @param:
 * scheduler	pointer to a scheduler
 * uid			the requested task's uid
 *
 * @return:
 * 0 for success, if uid is not found - return 1.
 */
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid);

/* DESCRIPTION:
 * get number of tasks in scheduler 
 * 
 * @param:
 * scheduler	pointer to a scheduler
 *
 * @return:
 * number of tasks
 */
size_t SchedulerSize(scheduler_t *scheduler);

/* DESCRIPTION:
 * checks wether a scheduler is empty or not
 * 
 * @param:
 * scheduler	pointer to a scheduler
 *
 * @return:
 * 1 if empty, otherwise 0
 */
int SchedulerIsEmpty(scheduler_t *scheduler);

/* DESCRIPTION:
 * stops the scheduler 
 * 
 * @param:
 * scheduler	pointer to a scheduler
 */
void SchedulerStop(scheduler_t *scheduler);

/* DESCRIPTION:
 * checks wether a scheduler is active or not
 * 
 * @param:
 * scheduler	pointer to a scheduler
 *
 * @return:
 * 1 if active, otherwise 0
 */
int SchedulerIsActive(scheduler_t *scheduler);

#endif /*__SCHEDULER_H__*/
