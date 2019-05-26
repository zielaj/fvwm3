#ifndef _SAFEMALLOC_H
#define _SAFEMALLOC_H

void	*xmalloc(size_t);
void	*xcalloc(size_t, size_t);
void	*xrealloc(void *, size_t, size_t);
char	*xstrdup(const char *);
int	 xasprintf(char **, const char *, ...);
int	 xvasprintf(char **, const char *, va_list);

#endif
