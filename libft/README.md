*This project has been created as part of the 42 curriculum by ltalpain.*

# Libft

## Description

**Libft** is the first project of the 42 curriculum: it consists of writing, from scratch and in C, a personal library of general-purpose functions that will be reused in later projects.

The goal is to understand how the standard C library works under the hood — memory manipulation, string handling, dynamic allocation, linked lists — by re-implementing its functions without using the originals, and to build a clean, reusable static library (`libft.a`) with a proper `Makefile`.

The library is made of three parts:

1. **Libc functions**: re-implementations of standard functions (`ft_strlen`, `ft_memmove`, `ft_atoi`, `ft_calloc`...), with the same behavior and prototypes as the originals, prefixed with `ft_`.
2. **Additional functions**: useful utilities that are not in the libc or exist in a different form (`ft_split`, `ft_itoa`, `ft_substr`, `ft_putnbr_fd`...).
3. **Linked lists**: a `t_list` structure and the functions to create, manipulate and free singly linked lists (`ft_lstnew`, `ft_lstmap`...).

Only `malloc`, `free` and `write` are used by the library (plus the libc functions explicitly allowed by the subject).

## Instructions

### Requirements

- `cc` (gcc or clang) and `make`

- The library is compiled with `-Wall -Wextra -Werror`.

### Building

```sh
make          # builds libft.a (all the functions, including the linked-list ones)
make clean    # removes the object (.o) and dependency (.d) files
make fclean   # removes the objects and libft.a
make re       # fclean, then rebuilds everything
```

Running `make` twice in a row does not relink anything. Object files are rebuilt when their source file, the `Makefile`, or any header they include changes.

### Using the library

Include the header in your code and link against `libft.a`:

```sh
# from the directory that contains libft.h and libft.a
cc -Wall -Wextra -Werror main.c libft.a -I .

# shorter form, if main.c is in the same directory as libft.h
cc -Wall -Wextra -Werror main.c libft.a
```

Example:

```c
#include <stdlib.h>
#include "libft.h"

int	main(void)
{
	char	**words;
	int		i;

	words = ft_split("hello 42  world", ' ');
	if (!words)
		return (1);
	i = 0;
	while (words[i])
	{
		ft_putendl_fd(words[i], 1);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
```

Output:

```
hello
42
world
```

### Testing

The library was tested with a custom test program (not part of the library, generated with AI assistance) that:

- compares each libc re-implementation against the real libc function on normal and edge cases (empty strings, `n == 0`, bytes above 127, overlapping memory areas, `INT_MIN`, overflow in `calloc`...);
- checks the functions that have no libc equivalent (`ft_substr`, `ft_split`, `ft_itoa`, the linked-list functions...) against hard-coded expected results;
- captures the output of the `ft_put*_fd` functions through a pipe to verify the exact bytes written.

Memory errors and leaks were checked with `valgrind --leak-check=full` and with `-fsanitize=address`.

## Library description

All prototypes are declared in `libft.h`.

### Part 1 — Libc functions

| Function | Description |
|---|---|
| `int ft_isalpha(int c)` | Non-zero if `c` is a letter (`A-Z`, `a-z`), 0 otherwise. |
| `int ft_isdigit(int c)` | Non-zero if `c` is a decimal digit (`0-9`), 0 otherwise. |
| `int ft_isalnum(int c)` | Non-zero if `c` is a letter or a digit, 0 otherwise. |
| `int ft_isascii(int c)` | Non-zero if `c` is in the ASCII range (0–127), 0 otherwise. |
| `int ft_isprint(int c)` | Non-zero if `c` is a printable character (32–126), 0 otherwise. |
| `size_t ft_strlen(const char *s)` | Length of the string `s`, not counting the terminating `'\0'`. |
| `void *ft_memset(void *s, int c, size_t n)` | Fills the first `n` bytes of `s` with the byte `c`. Returns `s`. |
| `void ft_bzero(void *s, size_t n)` | Sets the first `n` bytes of `s` to zero. |
| `void *ft_memcpy(void *dst, const void *src, size_t n)` | Copies `n` bytes from `src` to `dst`. The areas must not overlap. Returns `dst`. |
| `void *ft_memmove(void *dst, const void *src, size_t n)` | Like `ft_memcpy`, but the areas may overlap: the copy direction is chosen so no source byte is overwritten before being read. Returns `dst`. |
| `size_t ft_strlcpy(char *dst, const char *src, size_t size)` | Copies at most `size - 1` characters of `src` into `dst` and always null-terminates (if `size > 0`). Returns `strlen(src)`, which allows detecting truncation. |
| `size_t ft_strlcat(char *dst, const char *src, size_t size)` | Appends `src` to `dst`, writing at most `size - 1` characters in total and null-terminating. Returns `min(size, strlen(dst)) + strlen(src)`. Nothing is written if `size <= strlen(dst)`. |
| `int ft_toupper(int c)` | Converts a lowercase letter to uppercase; other characters are unchanged. |
| `int ft_tolower(int c)` | Converts an uppercase letter to lowercase; other characters are unchanged. |
| `char *ft_strchr(const char *s, int c)` | Pointer to the first occurrence of `(char)c` in `s` (the terminating `'\0'` is searched too), or `NULL`. |
| `char *ft_strrchr(const char *s, int c)` | Pointer to the last occurrence of `(char)c` in `s`, or `NULL`. |
| `int ft_strncmp(const char *s1, const char *s2, size_t n)` | Compares at most `n` characters, stopping at `'\0'`, treating them as `unsigned char`. Returns the difference of the first differing characters, or 0. |
| `void *ft_memchr(const void *s, int c, size_t n)` | Pointer to the first occurrence of the byte `c` in the first `n` bytes of `s`, or `NULL`. |
| `int ft_memcmp(const void *s1, const void *s2, size_t n)` | Compares `n` bytes (as `unsigned char`). Unlike `ft_strncmp`, it does not stop at `'\0'`. |
| `char *ft_strnstr(const char *big, const char *little, size_t len)` | Locates the first occurrence of `little` in `big`, searching at most `len` characters. Returns `big` if `little` is empty, `NULL` if not found. |
| `int ft_atoi(const char *nptr)` | Converts the initial part of the string to an `int`: skips leading whitespace, accepts one optional `+` or `-` sign, then reads digits. |
| `void *ft_calloc(size_t nmemb, size_t size)` | Allocates `nmemb * size` bytes set to zero. Returns `NULL` if the multiplication overflows or if the allocation fails. |
| `char *ft_strdup(const char *s)` | Returns a newly allocated copy of `s`, or `NULL` if the allocation fails. |

### Part 2 — Additional functions

| Function | Description |
|---|---|
| `char *ft_substr(char const *s, unsigned int start, size_t len)` | Allocates a substring of `s` that starts at index `start` and has at most `len` characters. Returns an empty string if `start` is past the end of `s`. `NULL` if the allocation fails. |
| `char *ft_strjoin(char const *s1, char const *s2)` | Allocates a new string that is the concatenation of `s1` and `s2`. |
| `char *ft_strtrim(char const *s1, char const *set)` | Allocates a copy of `s1` with every character belonging to `set` removed from the beginning and from the end. |
| `char **ft_split(char const *s, char c)` | Splits `s` using the delimiter `c` and returns a `NULL`-terminated array of newly allocated strings. Consecutive, leading and trailing delimiters produce no empty strings. If an allocation fails, everything already allocated is freed and `NULL` is returned. |
| `char *ft_itoa(int n)` | Allocates the string representation of the integer `n`, including negative numbers and `INT_MIN`. |
| `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | Applies `f` to each character of `s` (with its index) and returns a new string made of the results. |
| `void ft_striteri(char *s, void (*f)(unsigned int, char *))` | Applies `f` to each character of `s` (with its index), passing its address so it can be modified in place. |
| `void ft_putchar_fd(char c, int fd)` | Writes the character `c` to the file descriptor `fd`. |
| `void ft_putstr_fd(char *s, int fd)` | Writes the string `s` to the file descriptor `fd`. |
| `void ft_putendl_fd(char *s, int fd)` | Writes the string `s` followed by a newline to the file descriptor `fd`. |
| `void ft_putnbr_fd(int n, int fd)` | Writes the integer `n` to the file descriptor `fd`, including negative numbers and `INT_MIN`. |

### Part 3 — Linked lists

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | Description |
|---|---|
| `t_list *ft_lstnew(void *content)` | Allocates a new node holding `content` (the pointer is stored, not copied), with `next` set to `NULL`. |
| `void ft_lstadd_front(t_list **lst, t_list *new)` | Adds the node `new` at the beginning of the list. |
| `unsigned int ft_lstsize(t_list *lst)` | Counts the number of nodes in the list. |
| `t_list *ft_lstlast(t_list *lst)` | Returns the last node of the list (`NULL` for an empty list). |
| `void ft_lstadd_back(t_list **lst, t_list *new)` | Adds the node `new` at the end of the list. Works on an empty list. |
| `void ft_lstdelone(t_list *lst, void (*del)(void *))` | Frees the content of the node with `del`, then frees the node itself (not the following nodes). |
| `void ft_lstclear(t_list **lst, void (*del)(void *))` | Deletes and frees the given node and every node after it, then sets the list pointer to `NULL`. |
| `void ft_lstiter(t_list *lst, void (*f)(void *))` | Applies `f` to the content of each node, in order. |
| `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | Builds a new list by applying `f` to the content of each node. The original list is not modified. If an allocation fails, the new list is cleared with `del` and `NULL` is returned. |

## Technical choices

- **Language and style**: C, following the 42 Norm.
- **Build system**: the `Makefile` uses an explicit list of source files and a pattern rule to compile each `.c` into a `.o`. The `-MMD` flag generates `.d` files that list the headers each source depends on, so a modified header triggers exactly the right recompilations. The `Makefile` itself is a dependency of every object, so changing the build flags rebuilds everything.
- **Archive**: `libft.a` is created with `ar rcs`.
- **Error handling**: allocating functions return `NULL` on failure, and functions that build several allocations (`ft_split`, `ft_lstmap`) free what they already allocated before returning `NULL`.
- **Edge cases handled on purpose**: `size == 0` and truncation in `ft_strlcpy`/`ft_strlcat`, overlapping areas in `ft_memmove`, unsigned comparisons in `ft_strncmp`/`ft_memcmp`, multiplication overflow in `ft_calloc`, `start` past the end in `ft_substr`, `INT_MIN` in `ft_itoa`/`ft_putnbr_fd`.

## Resources

### References

- [The C standard (C11 draft N1570)]
- [man pages] — `string(3)`, `ctype(3)`, `malloc(3)`, `write(2)`, `ar(1)`

### Use of AI

AI (Claude, by Anthropic) was used as a learning, testing and debugging assistant:

- **Understanding**: explanations of the exact behavior and edge cases of the libc functions (`memcpy` vs `memmove`, return values of `strlcpy`/`strlcat`, unsigned comparison in `strncmp`/`memcmp`), and of C and build concepts (`static`, `const`, compiling vs linking, Makefile pattern rules and automatic variables, `-MMD` dependency files).
- **Testing**: generation of the test program described above (edge-case lists, comparison against the libc, pipe-based capture of `ft_put*_fd`, checks with valgrind and AddressSanitizer).
- **Debugging and review**: AI pointed out bugs in some of my implementations and suggested fixes, in some cases with a rewritten version (`ft_strncmp`, `ft_memmove`, `ft_calloc`, `ft_substr`, `ft_strnstr`, `ft_split`, `ft_strtrim`, `ft_lstiter`, and the `Makefile`'s `re` rule). I reviewed, understood, adapted and re-tested these changes.
- **Documentation**: this README was drafted with AI assistance and then reviewed and modified.

**The library code itself was written by me; AI was not used to submit code I did not understand.**
