/* (C) 2022 Olivia May GPLv3+ */

#include <iostream>
#include <string.h>

static Page working_page;

void invalid(char *argv)
{
	printf("Invalid argument: '%s'\n", argv);
}

void no_arg()
{
	printf("error: no arguments ('--help' for more info)\n");
}

void version()
{
	printf("LIVSDiary %s - (LI)ghtweight (V)irtual (S)imple Diary\n", PROGRAM_VERSION);
	printf("Copyright (C) 2022 Olivia May.\n");
	printf("License GPLv3+, this is free software.\n\n");
	printf("Written in C/C++ by Olivia May.\n");
}

void help()
{
	printf("A command line virtual diary.\n");
	printf("-e [page number],	--edit=NUMBER	edit page. No input assumes most recent page\n");
	printf("-h,			--help		show this menu\n");
	printf("-l,			--list		list all pages\n");
	printf("-n,			--new		new page\n");
	printf("-r			--remove	removes most recent page\n");
	printf("-v [page number],	--view=NUMBER	view page\n");
	printf("-V			--version	show version\n");
}

void edit(char page_num[])
{
	printf("** LIVSDiary **\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
	printf("This is free software, and you are welcome to\n");
	printf("redistribute it under certain conditions.\n\n");

	working_page.print_help();
	strcpy(working_page.page_num, page_num);
	working_page.edit();
}

void view(char input[])
{
	char page_num[PAGE_COUNT_BUFFER]; strcpy(page_num, input);
	strcat(CURRENT_PAGE_DIR, page_num);
	copy_file_to_memory(CURRENT_PAGE_DIR);
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(page_num)] = '\0';

	printf("** Page %s **\n%s\n%s\n", page_num, get_page_time(page_num), file_contents);
}

void list_pages()
{
	int page_num_int = convert_to_int(file_contents);
	for (int i = 0; i <= page_num_int; i++)
	{
		convert_to_char_array(i);
		view(converted_int);
	}
}

void command_logic(int argc, char *argv[]) 	
{
	// puts most recent page number in `file_contents` 
	copy_file_to_memory(PAGE_COUNT_DIR);

	if (argc == 1) 
	{
		edit(file_contents);
	}
	else
	{
		if (strncmp(argv[1], "-h", 3) == 0 ||
		strncmp(argv[1], "--help", 7) == 0)
		{
			help();
		} 
		else if (strncmp(argv[1], "-V", 3) == 0 ||
		strncmp(argv[1], "--version", 10) == 0)
		{
			version();
		}
		else if (strncmp(argv[1], "-e", 3) == 0)
		{
			if (argc == 2)
			{
				edit(file_contents);
			}
			else
			{
				if (check_input_is_int(argv[2]) == true)
				{
					int argv2_int = convert_to_int(argv[2]);
					if (argv2_int <= convert_to_int(file_contents)
					&& argv2_int >= 0)
					{ edit(argv[2]); }
					else
					{
						printf("error: found no page with number '%s'\n", argv[2]);
					}
				}
				else
				{
					invalid(argv[2]);
				}
			}
		}
		else if (strncmp(argv[1], "-v", 3) == 0)
		{
			if (argc == 2)
			{
				view(file_contents);
			}
			else
			{
				if (check_input_is_int(argv[2]) == true)
				{
					int argv2_int = convert_to_int(argv[2]);
					if (argv2_int <= convert_to_int(file_contents)
					&& argv2_int >= 0)
					{ view(argv[2]); }
					else
					{ printf("error: found no page with number '%s'\n", argv[2]); }
				}
				else
				{
					invalid(argv[2]);
				}
			}

		}
		// 7 because not checking for end of the argument
		else if (strncmp(argv[1], "--edit=", 7) == 0)
		{
			int i;
			for (i = 7; i < strlen(argv[1]); i++)
			{
				argv[1][i - 7] = argv[1][i];
			}
			argv[1][i - 7] = '\0';
			
			if (argv[1][0] == '\0')
			{
				invalid(argv[1]);
			}
			else if (check_input_is_int(argv[1]) == true)
			{
				int argv2_int = convert_to_int(argv[1]);
				if (argv2_int <= convert_to_int(file_contents)
				&& argv2_int >= 0)
				{ edit(argv[1]); }
				else
				{ printf("error: found no page with number '%s'\n", argv[1]); }
			}
			else
			{
				invalid(argv[1]);
			}

		}
		else if (strncmp(argv[1], "--view=", 7) == 0)
		{
			int i;
			for (i = 7; i < strlen(argv[1]); i++)
			{
				argv[1][i - 7] = argv[1][i];
			}
			argv[1][i - 7] = '\0';
			
			if (argv[1][0] == '\0')
			{
				invalid(argv[1]);
			}
			else if (check_input_is_int(argv[1]) == true)
			{
				int argv2_int = convert_to_int(argv[1]);
				if (argv2_int <= convert_to_int(file_contents)
				&& argv2_int >= 0)
				{ view(argv[1]); }
				else
				{ printf("error: found no page with number '%s'\n", argv[1]); }
			}
			else
			{
				invalid(argv[1]);
			}

		}
		else if (strncmp(argv[1], "-n", 3) == 0 ||
		strncmp(argv[1], "--new", 6) == 0)
		{
			make_new_page();
		}
		else if (strncmp(argv[1], "-r", 3) == 0 ||
		strncmp(argv[1], "--remove", 9) == 0)
		{
			if (file_contents[0] == '0' && file_contents[1] == '\0') 
			{
				printf("error: refusing to remove Table of Contents!\n");
			}
			else
			{
				remove_most_recent_page();
			}
		}
		else if (strncmp(argv[1], "-l", 3) == 0 ||
		strncmp(argv[1], "--list", 7) == 0)
		{
			list_pages();
		}
		else
		{
			invalid(argv[1]);
		}
	}
}
