/*
 * FVWM Shell -- command input interface.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see: <http://www.gnu.org/licenses/>
 */

#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libs/Module.h"
#include "libs/fvwmlib.h"

#define FVWMSHELLWRAPPER "FvwmShellWrapper"

int fd[2];

int main(int argc, char **argv)
{
	ModuleArgs	*module = ParseModuleArgs(argc, argv, 0);
	char		*this_module = "FvwmShell";
	char		**options;
	int		 clpid = 0i, opcount = 0;

	if (module == NULL) {
		fprintf(stderr, "%s should only be executed by fvwm\n",
			this_module);
		exit (1);
	}

	fd[0] = module->to_fvwm;
	fd[1] = module->from_fvwm;

	options = xmalloc(20 * sizeof(char *));
	options[opcount++] = "xterm";
	options[opcount++] = "-hold";
	options[opcount++] = "-e";
	options[opcount++] = FVWMSHELLWRAPPER; 
	options[opcount] = NULL;

	int o;
	for (o = 0; o < opcount; o++)
		fprintf(stderr, "cmd(%d): %s\n", o, options[o]);
	
	clpid = fork();
	if (clpid < 0) {
		fprintf(stderr, "fork failed: %s\n", strerror(errno));
		exit (1);
	} else if (clpid == 0) {
		execvp(*options, options);
		fprintf(stderr, "execvp failed: %s\n", strerror(errno));
	}


	SetMessageMask(fd, M_END_CONFIG_INFO | M_ERROR | M_EXTENDED_MSG);
	SendFinishedStartupNotification(fd);

	fprintf(stderr, "Implement me!\n");

	return (0);
}	
