/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:04:26 by rschlott          #+#    #+#             */
/*   Updated: 2023/02/07 10:02:30 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    int     i = 0;
    int     rd = 0;
    char    character;
    char     *buffer = malloc(10000);

    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
    return(buffer);
}

/*char	*get_next_line(int fd)
{
	char	*string;
	char	*copy;

	string = malloc(10000);
	copy = string;
	while (read(fd, copy, 1) > 0 && *copy++ != '\n');
	if (copy > string)
	{
		*copy = 0;
		return (string);
	}
	free(string);
	return (NULL);
}*/

/*
* Bedingung ? Ausdruck1 : Ausdruck2
* Zuerst wird die Bedingung ausgewertet. Trifft diese zu, wird der erste 
* Ausdruck abgearbeitet, andernfalls der zweite.
*/
/*char *get_next_line(int fd)
{
    char    *string;
    char    *copy;

    string = malloc(10000);
    copy = string;
    while (read(fd, copy, 1) > 0 && *copy++ != '\n');
    return (copy > string) ? (*copy = 0, string) : (free(string), NULL);
}*/

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
    int fd;
    char *line;
    fd = open("test.txt", O_RDWR);
    line = get_next_line(fd);
    printf("%s", line);
    free (line);
    line = get_next_line(fd);
    printf("%s", line);
    free (line);
    line = get_next_line(fd);
    printf("%s", line);
    free (line);
    line = get_next_line(fd);
    printf("%s", line);
    free (line);
    close(fd);
}
