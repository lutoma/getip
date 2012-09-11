/* getip: A small fastcgi handler that returns the client's IP address.
 * Author: Lukas Martini <lutoma@ohai.su>
 *
 * To the extent possible under law, Lukas Martini has waived all copyright and
 * related or neighboring rights to getip. This work is published from: United
 * States.
 *
 * For more information and the legal code, see
 * http://creativecommons.org/publicdomain/zero/1.0/legalcode
 */

#define LISTEN_ADDR "127.0.0.1:8003"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcgiapp.h>

int main(void)
{
	FCGX_Init();
	int listen_socket = FCGX_OpenSocket(LISTEN_ADDR, 400);
	FCGX_Request request;
	FCGX_InitRequest(&request, listen_socket, 0);

	if(fork())
	{
		printf("Successfull startup.\n");
		_Exit(EXIT_SUCCESS);
	}

	while(FCGX_Accept_r(&request) == 0)
		FCGX_FPrintF(request.out,
			"Content-Type: text/plain\r\n"
			"X-Sourcecode: https://github.com/lutoma/getip\r\n"
			"\r\n%s",
			FCGX_GetParam("REMOTE_ADDR", request.envp));

	return EXIT_SUCCESS;
}
