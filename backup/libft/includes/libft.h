/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:20:09 by akambou           #+#    #+#             */
/*   Updated: 2024/04/08 23:47:29 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*-------------------------------CHARS------------------------------------*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(int c);
int		ft_ishexdigit(int c);
/*-------------------------------NUMBERS----------------------------------*/
int		ft_atoi(const char *str);
double	ft_atof(char *str);
char	*ft_itoa(int n);
/*-------------------------------ALLOCS-----------------------------------*/
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t size);
char	*ft_crazy_free(char **buffer);
/*-------------------------------MEMORY-----------------------------------*/
void	ft_bzero(void *s, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *b, int c, size_t len);
/*-------------------------------STRINGS----------------------------------*/
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t len);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strspn(char *str, const char *str2);
size_t	ft_strcspn(char *str, const char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(char *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(const char *s, char c);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtok_r(char *str, const char *delim, char **saveptr);
char	*ft_strpbrk(const char *str, const char *accept);
/*-------------------------------FILES------------------------------------*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
char	*get_next_line(int fd);
/*-------------------------------LISTS------------------------------------*/
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*-------------------------------PRINTF-----------------------------------*/
int		ft_printf(const char *str, ...);
int		ft_char_len(char c, int *len);
int		ft_str_len(char *str, int *len);
int		ft_nbr(int nbr, int *len);
int		ft_ptr(unsigned long ptr, int *len);
int		ft_hex(unsigned int nbr, int *len, const char *base);
int		ft_unsint(unsigned int nbr, int *len);

#endif
