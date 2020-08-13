#include "../sorted_list/sorted_list.h"
#include "priority_queue.h"

#include <string.h> /* memset */
#include <stdlib.h> /*malloc, free */
#include <assert.h> /* assert */

#define EMPTY 0
#define NOT_EMPTY 0

struct priority_queue
{
    sorted_list_t *sorted_list;
};

priority_q_t *PQCreate(pq_cmp_func_t cmp)
{
    priority_q_t *priority_q = NULL;
    assert(NULL != cmp);

    priority_q = (priority_q_t *)malloc(sizeof(priority_q_t));

    if (NULL == priority_q)
    {
        return NULL;
    }

    priority_q->sorted_list = SortedListCreate(cmp);

    if (NULL == priority_q->sorted_list)
    {
        memset(priority_q->sorted_list, EMPTY, sizeof(priority_q_t));
        free(priority_q->sorted_list);
        priority_q->sorted_list = NULL;
    }

    return priority_q;
}

void PQDestroy(priority_q_t *priority_queue)
{
    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    SortedListDestroy(priority_queue->sorted_list);

    memset(priority_queue, EMPTY, sizeof(priority_q_t));
    free(priority_queue);
    priority_queue = NULL;
}

void *PQDeQueue(priority_q_t *priority_queue)
{
    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    return SortedListPopFront(priority_queue->sorted_list);
}

int PQEnQueue(priority_q_t *priority_queue, const void *data)
{
    iterator_t iter = NULL;

    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    iter = SortedListInsert(priority_queue->sorted_list, (void *)data);
    return iter == SortedListEnd(priority_queue->sorted_list);
}

void *PQPeek(const priority_q_t *priority_queue)
{
    iterator_t iter = NULL;

    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    iter = SortedListBegin(priority_queue->sorted_list);
    return SortedListGetData(iter);
}

size_t PQSize(const priority_q_t *priority_queue)
{
    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    return SortedListCount(priority_queue->sorted_list);
}

int PQueueIsEmpty(const priority_q_t *priority_queue)
{
    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    return SortedListIsEmpty(priority_queue->sorted_list);
}

void PQClear(priority_q_t *priority_queue)
{
    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);

    while (NOT_EMPTY == PQueueIsEmpty(priority_queue))
    {
        PQDeQueue(priority_queue);
    }
}

void *PQErase(priority_q_t *priority_queue,
              pq_match_func_t is_match,
              const void *param)
{
    iterator_t iter_to_remove = NULL;
    iterator_t iter_end = NULL;
    iterator_t iter_begin = NULL;
    void *return_data = NULL;

    assert(NULL != priority_queue);
    assert(NULL != priority_queue->sorted_list);
    assert(NULL != is_match);

    iter_begin = SortedListBegin(priority_queue->sorted_list);
    iter_end = SortedListEnd(priority_queue->sorted_list);

    iter_to_remove = SortedListFindIf(iter_begin, iter_end, is_match, param);

    if (iter_end != iter_to_remove)
    {
        return_data = SortedListGetData(iter_to_remove);
        SortedListRemove(iter_to_remove);
    }

    return return_data;
}
