#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stdlib.h> /*size_t */

typedef struct priority_queue priority_q_t;

/* compare functions */
typedef int(*pq_cmp_func_t)(const void *data1, const void *data2);

typedef int(*pq_match_func_t)(const void *data, const void *param);

/* DESCRIPTION
* creates the priority_queue
*
* @param:
* cmp		user defined compare function
*			to determine order of elements
*
* @return: 	pointer to the new priority_queue
*/
priority_q_t *PQCreate(pq_cmp_func_t cmp);


/* DESCRIPTION
* destroys the priority_queue and frees allocated memory
*
* @param:
* *priority_queue:	pointer to the priority queue
*/
void PQDestroy(priority_q_t *priority_queue);


/* DESCRIPTION
* removes the first element from the priority queue
*
* @param:
* *priority_queue:	pointer to the priority queue
*
* @return: 	pointer to data from the removed element
*/
void* PQDeQueue(priority_q_t *priority_queue);


/* DESCRIPTION
* adds new element to the correct position
* in the priority queue. If the element has same priority
* as existing element -insert according to fifo
*
* @param:
* *priority_queue:	pointer to the priority_queue
* *data:			pointer to element we want to add
*
* @return: 	0 for success, 1 for failure
*/
int PQEnQueue(priority_q_t *priority_queue, const void *data);


/* DESCRIPTION
* returns the data of the first element in the priority_queue
*
* @param:
* *priority_queue:	pointer to the priority queue
*
*
* @return: 	pointer to the first data in the priority queue
*/
void *PQPeek(const priority_q_t *priority_queue);


/* DESCRIPTION
* returns the current size of the priority_queue
*
* @param:
* *priority_queue:	pointer to the priority queue
*
* @return: 	number of elements stored in the priority queue
*/
size_t PQSize(const priority_q_t *priority_queue);


/* DESCRIPTION
* Checks if there are no elements in the priority_queue
*
* @param:
* priority_queue	pointer to the priority queue
*
* @return: 	boolean value 1 empty, 0 not empty.
*/
int PQueueIsEmpty(const priority_q_t *priority_queue);

/* DESCRIPTION
* empty priority queue elements
*
* @param:
* *priority_queue:	pointer to the priority queue
*/
void PQClear(priority_q_t *priority_queue);

/* DESCRIPTION
* erase desired element	in priority_queue
* that was matched to param by is_match
*
* @param:
* priority_queue	pointer to the priority_queue
* is_match			user defined match function
* param				value to match elements with
*
* @return: 	pointer to erased value, otherwise NULL
*/
void *PQErase(priority_q_t *priority_queue,
	pq_match_func_t is_match,
	const void *param);


#endif /* __PRIORITY_QUEUE_H__ */



