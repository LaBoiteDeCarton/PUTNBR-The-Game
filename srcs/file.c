#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 2400


#include <stdio.h>

char	*read_file(char *file_name)
{
	int		fd;
	char	*buff;
	int		content_len;

	if ((fd = open(file_name, O_RDONLY))
			&& (buff = (char *)malloc(sizeof(char) * BUFF_SIZE)))
	{
		content_len = read(fd, buff, BUFF_SIZE);
		close(fd);
		//if (content_len == BUFF_SIZE)
		//	errno ...	
		buff[content_len] = '\0';
	}
	else
		buff = NULL;
	return (buff);
}

void	ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

char    *create_fn(int level)
{
	char *filename;

	filename = (char *)malloc(sizeof(char) * 14);
	ft_strcpy(filename, "files/level@@");
	filename[11] = '0' + level / 10;
	filename[12] = '0' + level % 10;
	return (filename);
}