/*

Assignment name  : ulstr
Expected files   : ulstr.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and reverses the case of all its letters.
Other characters remain unchanged.

You must display the result followed by a '\n'.

If the number of arguments is not 1, the program displays '\n'.

Examples :

$>./ulstr "L'eSPrit nE peUt plUs pRogResSer s'Il staGne et sI peRsIsTent VAnIte et auto-justification." | cat -e
l'EspRIT Ne PEuT PLuS PrOGrESsER S'iL STAgNE ET Si PErSiStENT vaNiTE ET AUTO-JUSTIFICATION.$
$>./ulstr "S'enTOuRer dE sECreT eSt uN sIGnE De mAnQuE De coNNaiSSanCe.  " | cat -e
s'ENtoUrER De SecREt EsT Un SigNe dE MaNqUe dE COnnAIssANcE.  $
$>./ulstr "3:21 Ba  tOut  moUn ki Ka di KE m'en Ka fe fot" | cat -e
3:21 bA  ToUT  MOuN KI kA DI ke M'EN kA FE FOT$
$>./ulstr | cat -e
$

*/
#include <stdlib.h>
#include <unistd.h>

int	is_upper (char c)
{
	return(c >= 'A' && c <= 'Z');
}

int	is_lower (char c)
{
	return(c >= 'a' && c <= 'z');
}

void	invert(char *str)
{
	char	c;

	while (*str)
	{
		if(is_upper(*str))
			c = *str + 32;
		else if(is_lower(*str))
			c = *str - 32;
		else
			c = *str;
		write (1, &c, 1);	
		str++;
	}
}

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		write (1, "\n", 1);
		return 1;
	}
	invert(argv[1]);
}
