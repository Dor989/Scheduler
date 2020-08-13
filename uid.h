#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>/* pid_t */ 
#include <time.h>/*time_t, time */

typedef struct uid
{
	pid_t pid;
	time_t time_stamp;
	size_t counter;
}ilrd_uid_t;
/* DESCRIPTION:
 * Create new UID
 *
 * @return:
 * UID
 */
ilrd_uid_t UIDCreate(void);

/* DESCRIPTION:
 * Create bad UID
 *
 * @return:
 * bad UID
 */
ilrd_uid_t BadUIDCreate(void);

/* DESCRIPTION:
 * Compares two uids
 *
 * @param:
 * uid1, uid2    UIDs to be compared
 *
 * @return:
 * 1 if equal, 0 if not
 */
int UIDISEqual(const ilrd_uid_t *uid1, const ilrd_uid_t *uid2);

#endif /* __UID_H__ */

