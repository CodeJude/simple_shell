#include "shell.h"

/**
 * showHistory - This shows the history list in the program,
 *	one line by command and it will be preceded with numbers, starting at 0.
 * @commandInfo: information containing potential arguments in the program
 *  Return: Always 0 and 1 if error
 */
int showHistory(info_t *commandInfo)
{
	listPrint(commandInfo->history);
	return (0);
}

/**
 * removeAlias - this removes the alias and set to string
 * @commandInfo: The parameter or information about the command
 * @str: the string alias used to identify the command
 * Return: Always 0 on success, 1 on error if otherwise
 */
int removeAlias(info_t *commandInfo, char *str)
{
	char *p, c;
	int ret;

	p = findChar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = eraseNodeAtIndex(&(commandInfo->alias),
			findNodeIndex(commandInfo->alias, startsWith(commandInfo->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * addAlias - This add an alias to a string
 * @commandInfo: The parameter or information about the command
 * @str: the string alias used in the program
 *
 * Return: Always 0 on success, 1 on error
 */
int addAlias(info_t *commandInfo, char *str)
{
	char *p;

	p = findChar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (removeAlias(commandInfo, str));

	removeAlias(commandInfo, str);
	return (appendNode(&(commandInfo->alias), str, 0) == NULL);
}

/**
 * showAlias - This shows the alias string in the program
 * @node: the alias node used to create the command
 *
 * Return: Always 0 on success and 1 if an error
 */
int showAlias(list_n *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = findChar(node->str, '=');
		for (a = node->str; a <= p; a++)
			writeChar(*a);
		writeChar('\'');
		printString(p + 1);
		printString("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - This manages and mimics the alias builtin (man alias)
 * @commandInfo: The parameter or information about the command
 *  Return: Always 0 and 1 for error
 */
int manageAlias(info_t *commandInfo)
{
	int i = 0;
	char *p = NULL;
	list_n *node = NULL;

	if (commandInfo->argc == 1)
	{
		node = commandInfo->alias;
		while (node)
		{
			showAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; commandInfo->argv[i]; i++)
	{
		p = findChar(commandInfo->argv[i], '=');
		if (p)
			addAlias(commandInfo, commandInfo->argv[i]);
		else
			showAlias(startsWith(commandInfo->alias, commandInfo->argv[i], '='));
	}

	return (0);
}

