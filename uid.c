
#include <unistd.h> /*getpid */
#include <assert.h> /* assert */
#include "uid.h"
#include <stdio.h>

#define BAD -1
#define INIT 0

ilrd_uid_t UIDCreate(void)
{
    static size_t counter_static = INIT;
    ilrd_uid_t new_uid;

    new_uid.pid = getpid();
    new_uid.time_stamp = time(NULL);
    new_uid.counter = ++counter_static;

    return new_uid;
}

ilrd_uid_t BadUIDCreate(void)
{
    ilrd_uid_t new_uid;

    new_uid.pid = BAD;
    new_uid.time_stamp = BAD;
    new_uid.counter = INIT;

    return new_uid;
}

int UIDISEqual(const ilrd_uid_t *uid1, const ilrd_uid_t *uid2)
{
    assert(NULL != uid1);
    assert(NULL != uid1);

    return (uid1->counter == uid2->counter) &&
        (uid1->time_stamp == uid2->time_stamp) &&
        (uid1->pid == uid2->pid);

}

