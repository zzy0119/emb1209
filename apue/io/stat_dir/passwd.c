#include <stdio.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>

#define NAMESIZE	32

int main(void)
{
	char user[NAMESIZE] = {};
	char *passwd;
	struct spwd *sp;
	char *ec;

	printf("username:");
	fgets(user, NAMESIZE, stdin);
	user[strlen(user)-1] = '\0';
	passwd = getpass("password:");

	// 校验
	sp = getspnam(user);
	if (NULL == sp) {
		perror("getspnam()");	
		return 1;
	}
	ec = crypt(passwd, sp->sp_pwdp);
	if (NULL == ec) {
		fprintf(stderr, "crypt() failed\n");
		return 1;
	}

	if (!strcmp(ec, sp->sp_pwdp)) {
		printf("鉴定成功\n");
	} else {
		printf("失败\n");
	}

	return 0;
}
