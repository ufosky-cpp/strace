#ifndef _STRACE_TESTS_ACCEPT_COMPAT_H_
#define _STRACE_TESTS_ACCEPT_COMPAT_H_

#include <unistd.h>
#include <sys/socket.h>
#include <asm/unistd.h>

#if defined __NR_socketcall && defined __sparc__
/*
 * Working around the fact that glibc starting from 2.26 uses accept4() syscall
 * as an accept() call implementation on sparc combined with the fact that
 * accept syscall had not been wired up until v4.4-rc8~4^2~1
 */
static inline int
do_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	const long args[] = { sockfd, (long) addr, (long) addrlen };

	return syscall(__NR_socketcall, 5, args);
}
#else
# define do_accept accept
#endif

#endif /* !_STRACE_TESTS_ACCEPT_COMPAT_H_ */
