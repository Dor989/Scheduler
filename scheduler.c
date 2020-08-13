#include "scheduler.h"
#include "../task/task.h"
#include "../priority_queue/priority_queue.h"

#include <string.h> /*memset */
#include <assert.h> /* assert*/
#include <unistd.h> /*sleep */

#define ACTIVE 1
#define OFF 0
#define INIT 0
#define SUCCESS 0
#define FAILURE 1
#define TRUE 1

struct scheduler
{
    priority_q_t *pq;
    int is_active;
};
static int Cmp(const void *data1, const void *data2);
static int MatchToErase(const void *data, const void *param);
static void RemoveAllTasks(scheduler_t *scheduler);

scheduler_t *SchedulerCreate()
{
    scheduler_t *new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));

    if (NULL == new_scheduler)
    {
        return NULL;
    }

    new_scheduler->pq = PQCreate(Cmp);

    if (NULL == new_scheduler->pq)
    {
        memset(new_scheduler, 0, sizeof(scheduler_t));
        free(new_scheduler);
        new_scheduler = NULL;

        return NULL;
    }
    new_scheduler->is_active = ACTIVE;

    return new_scheduler;
}

void SchedulerDestroy(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    RemoveAllTasks(scheduler);
    PQDestroy(scheduler->pq);

    memset(scheduler, INIT, sizeof(scheduler_t));
    free(scheduler);
    scheduler = NULL;
}
int SchedulerExecute(scheduler_t *scheduler)
{
    int res = TRUE;
    time_t time_to_sleep = 0;

    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    if (PQueueIsEmpty(scheduler->pq) || ACTIVE != SchedulerIsActive(scheduler))
    {
        return FAILURE;
    }

    while (ACTIVE == scheduler->is_active && TRUE == res && !PQueueIsEmpty(scheduler->pq))
    {
        time_t new_time = 0;
        task_t *current_task = (task_t *)PQDeQueue(scheduler->pq);
        time_to_sleep = TaskGetExecutionTime(current_task) - time(NULL);

        if (time_to_sleep < INIT)
        {
            time_to_sleep = INIT;
        }

        sleep(time_to_sleep);

        if (TaskIsTurnedOn(current_task))
        {
            if (SUCCESS != TaskExecute(current_task))
            {
                TaskShutDown(current_task);
            }
            new_time = TaskGetInterval(current_task) + time(NULL);
            TaskSetExecutionTime(current_task, new_time);
            res = PQEnQueue(scheduler->pq, current_task);
        }
        else
        {
            TaskDestroy(current_task);
        }
    }

    return ACTIVE != SchedulerIsActive(scheduler);
}

void SchedulerClear(scheduler_t *scheduler)
{

    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    RemoveAllTasks(scheduler);
    PQClear(scheduler->pq);
}

ilrd_uid_t SchedulerInsertTask(scheduler_t *scheduler,
                               int (*op_func)(void *func_params),
                               void *func_params,
                               size_t interval)
{
    task_t *new_task = NULL;
    time_t time_now = time(NULL);
    int res = SUCCESS;

    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);
    assert(NULL != op_func);
    assert(OFF != interval);

    new_task = TaskCreate(op_func, func_params, interval);
    if (NULL == new_task)
    {
        return BadUIDCreate();
    }
    TaskSetExecutionTime(new_task, time_now + interval);
    res = PQEnQueue(scheduler->pq, new_task);

    if (FAILURE == res)
    {
        TaskDestroy(new_task);
        return BadUIDCreate();
    }

    return TaskGetUid(new_task);
}

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid)
{

    task_t *task_to_remove = NULL;

    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    task_to_remove = (task_t *)PQErase(scheduler->pq, MatchToErase, (const void *)&uid);

    if (NULL == task_to_remove)
    {
        return FAILURE;
    }
    TaskDestroy(task_to_remove);

    return SUCCESS;
}

size_t SchedulerSize(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    return PQSize(scheduler->pq);
}

int SchedulerIsEmpty(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    return PQueueIsEmpty(scheduler->pq);
}

void SchedulerStop(scheduler_t *scheduler)
{
    assert(NULL != scheduler);

    scheduler->is_active = OFF;
}

int SchedulerIsActive(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    return scheduler->is_active;
}

static int MatchToErase(const void *data, const void *param)
{

    task_t *task = (task_t *)data;
    ilrd_uid_t *uid1 = (ilrd_uid_t *)param;
    ilrd_uid_t uid2 = TaskGetUid(task);

    return UIDISEqual(uid1, &uid2);
}

static int Cmp(const void *data1, const void *data2)
{
    task_t *task1 = (task_t *)data1;
    task_t *task2 = (task_t *)data2;

    return (int)(TaskGetExecutionTime(task1) - TaskGetExecutionTime(task2));
}

static void RemoveAllTasks(scheduler_t *scheduler)
{
    task_t *task_to_remove = NULL;

    assert(NULL != scheduler);
    assert(NULL != scheduler->pq);

    while (!PQueueIsEmpty(scheduler->pq))
    {
        task_to_remove = (task_t *)PQDeQueue(scheduler->pq);
        TaskDestroy(task_to_remove);
    }
}
