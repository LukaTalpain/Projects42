#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define BUF 32

#include <limits.h>   /* pour UINT_MAX */

static int	g_fail = 0;

/* 1 = teste aussi itoa, strmapi, striteri, putchar_fd, putstr_fd,
   putendl_fd, putnbr_fd. Mets 0 tant que ces fonctions ne sont pas ecrites. */
#define TEST_PART2 1

/* 1 = teste aussi ft_lstnew, ft_lstadd_front, ft_lstsize, ft_lstlast,
   ft_lstadd_back (necessite t_list dans libft.h). Mets 0 tant que ces
   fonctions ne sont pas ecrites. */
#define TEST_LIST 1

#if TEST_PART2
# define OUT_SIZE 5200
static unsigned int	g_calls = 0;
static int			g_order = 1;
#endif

char	long_str[4001];
char	long_exp[4004];
char	long_pad[4007];

static void	report(const char *name, int ok)
{
	printf("[%s] %s\n", ok ? "OK" : "KO", name);
	if (!ok)
		g_fail++;
}

static void	section(const char *name)
{
	printf("\n=== %s ===\n", name);
}

static int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

/* ------------------------------------------------------------------ */
/* is* / to* : teste tous les c de 0 a 255 contre la vraie fonction     */
/* exact == 0 : seule la valeur de verite compte (isalpha, isdigit...)  */
/* exact == 1 : valeur exacte (toupper, tolower)                        */
/* ------------------------------------------------------------------ */
static void	test_ctype(const char *name, int (*mine)(int), int (*ref)(int),
				int exact)
{
	int	c;
	int	bad;

	bad = -1;
	c = 0;
	while (c < 256)
	{
		if (exact && mine(c) != ref(c))
			bad = (bad == -1) ? c : bad;
		else if (!exact && (mine(c) != 0) != (ref(c) != 0))
			bad = (bad == -1) ? c : bad;
		c++;
	}
	report(name, bad == -1);
	if (bad != -1)
		printf("     premier echec : c = %d ('%c') -> ft=%d ref=%d\n",
			bad, (bad >= 32 && bad < 127) ? bad : '?', mine(bad), ref(bad));
}

/* ------------------------------------------------------------------ */
static void	test_strlen(const char *name, const char *s)
{
	size_t	mine;
	size_t	ref;

	mine = ft_strlen(s);
	ref = strlen(s);
	report(name, mine == ref);
	if (mine != ref)
		printf("     ft=%zu ref=%zu\n", mine, ref);
}

/* ------------------------------------------------------------------ */
static void	test_memset(const char *name, size_t off, int c, size_t n)
{
	unsigned char	a[BUF];
	unsigned char	b[BUF];
	void			*ret;

	memset(a, 'X', BUF);
	memset(b, 'X', BUF);
	ret = ft_memset(a + off, c, n);
	memset(b + off, c, n);
	report(name, ret == a + off && memcmp(a, b, BUF) == 0);
}


static void	test_bzero(const char *name, size_t off, size_t n)
{
	unsigned char	a[BUF];
	unsigned char	b[BUF];

	memset(a, 'X', BUF);
	memset(b, 'X', BUF);
	ft_bzero(a + off, n);
	bzero(b + off, n);
	report(name, memcmp(a, b, BUF) == 0);
}

/* ------------------------------------------------------------------ */
static void	test_memcpy(const char *name, const void *src, size_t n,
				size_t off)
{
	unsigned char	a[BUF];
	unsigned char	b[BUF];
	void			*ret;

	memset(a, 'X', BUF);
	memset(b, 'X', BUF);
	ret = ft_memcpy(a + off, src, n);
	memcpy(b + off, src, n);
	report(name, ret == a + off && memcmp(a, b, BUF) == 0);
}

static void	test_memmove(const char *name, size_t dst_off, size_t src_off,
				size_t n)
{
	char	a[17];
	char	b[17];
	void	*ret;

	strcpy(a, "0123456789abcdef");
	strcpy(b, a);
	ret = ft_memmove(a + dst_off, a + src_off, n);
	memmove(b + dst_off, b + src_off, n);
	report(name, ret == a + dst_off && memcmp(a, b, 17) == 0);
	if (memcmp(a, b, 17) != 0)
		printf("     ft=\"%s\" ref=\"%s\"\n", a, b);
}

/* ------------------------------------------------------------------ */
/* strlcpy : valeurs attendues en dur (absente de beaucoup de libc)     */
/* On compare les BUF octets : rien ne doit etre ecrit en trop          */
/* ------------------------------------------------------------------ */
static void	test_strlcpy(const char *name, const char *src, size_t size,
				const char *exp_str, size_t exp_ret)
{
	char	buf[BUF];
	char	exp[BUF];
	size_t	ret;
	int		ok;

	memset(buf, 'X', BUF);
	memset(exp, 'X', BUF);
	if (size > 0)
		strcpy(exp, exp_str);
	ret = ft_strlcpy(buf, src, size);
	ok = (ret == exp_ret && memcmp(buf, exp, BUF) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=%zu (attendu %zu) dst=\"%.32s\" (attendu \"%.32s\")\n",
			ret, exp_ret, buf, exp);
}

static void	test_strlcat(const char *name, const char *dst_init,
				const char *src, size_t size, const char *exp_str,
				size_t exp_ret)
{
	char	buf[BUF];
	char	exp[BUF];
	size_t	ret;
	int		ok;

	memset(buf, 'X', BUF);
	strcpy(buf, dst_init);
	memcpy(exp, buf, BUF);
	if (size > strlen(dst_init))
		strcpy(exp, exp_str);
	ret = ft_strlcat(buf, src, size);
	ok = (ret == exp_ret && memcmp(buf, exp, BUF) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=%zu (attendu %zu) dst=\"%.32s\" (attendu \"%.32s\")\n",
			ret, exp_ret, buf, exp);
}

/* ------------------------------------------------------------------ */
static void	test_strchr(const char *name, const char *s, int c)
{
	report(name, ft_strchr(s, c) == strchr(s, c));
}

static void	test_strrchr(const char *name, const char *s, int c)
{
	report(name, ft_strrchr(s, c) == strrchr(s, c));
}

/* on compare le signe : seul le signe est garanti par le standard      */
static void	test_strncmp(const char *name, const char *s1, const char *s2,
				size_t n)
{
	int	mine;
	int	ref;

	mine = ft_strncmp(s1, s2, n);
	ref = strncmp(s1, s2, n);
	report(name, sign(mine) == sign(ref));
	if (sign(mine) != sign(ref))
		printf("     ft=%d ref=%d\n", mine, ref);
}

static void	test_memchr(const char *name, const void *s, int c, size_t n)
{
	report(name, ft_memchr(s, c, n) == memchr(s, c, n));
}

static void	test_memcmp(const char *name, const void *s1, const void *s2,
				size_t n)
{
	int	mine;
	int	ref;

	mine = ft_memcmp(s1, s2, n);
	ref = memcmp(s1, s2, n);
	report(name, sign(mine) == sign(ref));
	if (sign(mine) != sign(ref))
		printf("     ft=%d ref=%d\n", mine, ref);
}

/* strnstr : pas dans la glibc, on donne l'offset attendu (-1 = NULL)   */
static void	test_strnstr(const char *name, const char *big,
				const char *little, size_t len, int exp_off)
{
	char	*ret;
	char	*exp;
	int		got;

	ret = ft_strnstr(big, little, len);
	exp = (exp_off < 0) ? NULL : (char *)big + exp_off;
	got = ret ? (int)(ret - big) : -1;
	report(name, ret == exp);
	if (ret != exp)
		printf("     offset retourne %d (attendu %d)\n", got, exp_off);
}

static void	test_atoi(const char *str)
{
	int	mine;
	int	ref;

	mine = ft_atoi(str);
	ref = atoi(str);
	printf("[%s] \"%s\" -> ft_atoi=%d atoi=%d\n",
		mine == ref ? "OK" : "KO", str, mine, ref);
	if (mine != ref)
		g_fail++;
}

//calloc 


static int	is_zero(const unsigned char *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (p[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

/* alloue, verifie que tout est a 0, puis ecrit partout (valgrind verifie la taille) */
static void	test_calloc(const char *name, size_t nmemb, size_t size)
{
	void	*p;
	int		ok;

	p = ft_calloc(nmemb, size);
	ok = (p != NULL && is_zero(p, nmemb * size));
	if (ok)
		memset(p, 'A', nmemb * size);
	report(name, ok);
	free(p);
}

/* tas sale : on libere un bloc rempli de 'X' pour que calloc risque de le reutiliser */
static void	test_calloc_dirty(const char *name, size_t n)
{
	unsigned char	*d;
	unsigned char	*p;

	d = malloc(n);
	memset(d, 'X', n);
	free(d);
	p = ft_calloc(n, 1);
	report(name, p != NULL && is_zero(p, n));
	free(p);
}

/* nmemb ou size == 0 : doit etre NULL / non-NULL comme le vrai calloc */
static void	test_calloc_zero(const char *name, size_t nmemb, size_t size)
{
	volatile size_t	n = nmemb;
	volatile size_t	s = size;
	void			*mine;
	void			*ref;

	mine = ft_calloc(n, s);
	ref = calloc(n, s);
	report(name, (mine == NULL) == (ref == NULL));
	free(mine);
	free(ref);
}

/* nmemb * size deborde : doit retourner NULL */
static void	test_calloc_overflow(const char *name, size_t nmemb, size_t size)
{
	volatile size_t	n = nmemb;
	volatile size_t	s = size;
	void			*p;

	p = ft_calloc(n, s);
	report(name, p == NULL);
	free(p);
}

//split 


static void	free_split(char **tab)
{
	size_t	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	print_split(char **res)
{
	size_t	i;

	if (res == NULL)
	{
		printf("     retour : NULL\n");
		return ;
	}
	printf("     retour :");
	i = 0;
	while (res[i] && i < 20)
	{
		printf(" \"%s\"", res[i]);
		i++;
	}
	printf(" (%zu mot%s)\n", i, i > 1 ? "s" : "");
}

/* exp : tableau de mots attendus, termine par NULL */
static void	test_split(const char *name, const char *s, char c,
				const char **exp)
{
	char	**res;
	size_t	i;
	int		ok;

	res = ft_split(s, c);
	ok = (res != NULL);
	i = 0;
	while (ok && exp[i])
	{
		if (res[i] == NULL || strcmp(res[i], exp[i]) != 0)
			ok = 0;
		i++;
	}
	if (ok && res[i] != NULL)
		ok = 0;
	report(name, ok);
	if (!ok)
		print_split(res);
	free_split(res);
}


//strdup 


/* copie s dans un buffer modifiable, appelle ft_strdup dessus, puis
   verifie : contenu identique, pointeur different, copie independante */
static void	test_strdup(const char *name, const char *s)
{
	char	src[5000];
	char	*mine;
	char	*ref;
	int		ok;

	strcpy(src, s);
	mine = ft_strdup(src);
	ref = strdup(s);
	ok = (mine != NULL && mine != src && strcmp(mine, ref) == 0);
	src[0] = '#';
	ok = (ok && strcmp(mine, ref) == 0);
	report(name, ok);
	if (!ok)
		printf("     ft=\"%s\" ref=\"%s\"\n", mine ? mine : "(null)", ref);
	free(mine);
	free(ref);
}


//substr

/* travaille sur une copie de s, puis ecrase cette copie : si le retour
   pointait dans s (au lieu d'etre une vraie allocation), il changerait */
static void	test_substr(const char *name, const char *s, unsigned int start,
				size_t len, const char *exp)
{
	char	src[64];
	char	*ret;
	int		ok;

	strcpy(src, s);
	ret = ft_substr(src, start, len);
	ok = (ret != NULL && strcmp(ret, exp) == 0);
	memset(src, '#', strlen(s));
	ok = (ok && strcmp(ret, exp) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=\"%s\" (attendu \"%s\")\n", ret ? ret : "(null)", exp);
	free(ret);
}

/* travaille sur des copies de s1 et s2 : on verifie que ft_strjoin ne les
   modifie pas, puis on les ecrase pour verifier que le retour est une vraie
   allocation independante */
static void	test_strjoin(const char *name, const char *s1, const char *s2,
				const char *exp)
{
	char	src1[5000];
	char	src2[5000];
	char	*ret;
	int		ok;

	strcpy(src1, s1);
	strcpy(src2, s2);
	ret = ft_strjoin(src1, src2);
	ok = (ret != NULL && ret != src1 && ret != src2
			&& strcmp(ret, exp) == 0);
	ok = (ok && strcmp(src1, s1) == 0 && strcmp(src2, s2) == 0);
	memset(src1, '#', strlen(s1));
	memset(src2, '#', strlen(s2));
	ok = (ok && strcmp(ret, exp) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=\"%.40s\" (attendu \"%.40s\")\n",
			ret ? ret : "(null)", exp);
	free(ret);
}

/* travaille sur des copies de s1 et set : on verifie qu'elles ne sont pas
   modifiees, puis on ecrase la copie de s1 pour verifier que le retour est
   une vraie allocation independante */
static void	test_strtrim(const char *name, const char *s1, const char *set,
				const char *exp)
{
	char	src[5000];
	char	src_set[64];
	char	*ret;
	int		ok;

	strcpy(src, s1);
	strcpy(src_set, set);
	ret = ft_strtrim(src, src_set);
	ok = (ret != NULL && ret != src && strcmp(ret, exp) == 0);
	ok = (ok && strcmp(src, s1) == 0 && strcmp(src_set, set) == 0);
	memset(src, '#', strlen(s1));
	ok = (ok && strcmp(ret, exp) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=\"%.40s\" (attendu \"%.40s\")\n",
			ret ? ret : "(null)", exp);
	free(ret);
}


#if TEST_PART2

/* ================================================================== */
/* itoa                                                               */
/* ================================================================== */
static void	test_itoa(const char *name, int n)
{
	char	exp[16];
	char	*ret;
	int		ok;

	snprintf(exp, sizeof exp, "%d", n);
	ret = ft_itoa(n);
	ok = (ret != NULL && strcmp(ret, exp) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=\"%s\" (attendu \"%s\")\n", ret ? ret : "(null)", exp);
	free(ret);
}

/* teste tous les entiers de from a to (inclus) : un seul verdict */
static void	test_itoa_range(const char *name, int from, int to)
{
	char	exp[16];
	char	*ret;
	int		n;
	int		bad;
	int		first;

	bad = 0;
	first = 0;
	n = from;
	while (n <= to)
	{
		snprintf(exp, sizeof exp, "%d", n);
		ret = ft_itoa(n);
		if (ret == NULL || strcmp(ret, exp) != 0)
		{
			if (bad == 0)
				first = n;
			bad++;
		}
		free(ret);
		n++;
	}
	report(name, bad == 0);
	if (bad)
		printf("     %d echec(s), premier : n = %d\n", bad, first);
}

/* detecte un buffer static : les deux resultats doivent coexister */
static void	test_itoa_two_calls(void)
{
	char	*a;
	char	*b;
	int		ok;

	a = ft_itoa(12);
	b = ft_itoa(34);
	ok = (a != NULL && b != NULL && a != b
			&& strcmp(a, "12") == 0 && strcmp(b, "34") == 0);
	report("deux appels : deux allocations independantes", ok);
	free(a);
	if (b != a)
		free(b);
}

/* ================================================================== */
/* strmapi : callbacks                                                */
/* ================================================================== */
static char	map_upper(unsigned int i, char c)
{
	(void)i;
	return ((char)toupper((unsigned char)c));
}

static char	map_ident(unsigned int i, char c)
{
	(void)i;
	return (c);
}

static char	map_next(unsigned int i, char c)
{
	(void)i;
	return ((char)(c + 1));
}

static char	map_index(unsigned int i, char c)
{
	(void)c;
	return ((char)('a' + i));
}

static char	map_alt(unsigned int i, char c)
{
	if (i % 2)
		return ((char)toupper((unsigned char)c));
	return ((char)tolower((unsigned char)c));
}

static char	map_count(unsigned int i, char c)
{
	(void)i;
	g_calls++;
	return (c);
}

/* travaille sur une copie de s : on verifie qu'elle n'est pas modifiee,
   puis on l'ecrase pour verifier que le retour est une vraie allocation */
static void	test_strmapi(const char *name, const char *s,
				char (*f)(unsigned int, char), const char *exp)
{
	char	src[64];
	char	*ret;
	int		ok;

	strcpy(src, s);
	ret = ft_strmapi(src, f);
	ok = (ret != NULL && ret != src && strcmp(ret, exp) == 0);
	ok = (ok && strcmp(src, s) == 0);
	memset(src, '#', strlen(s));
	ok = (ok && strcmp(ret, exp) == 0);
	report(name, ok);
	if (!ok)
		printf("     ret=\"%s\" (attendu \"%s\")\n", ret ? ret : "(null)", exp);
	free(ret);
}

/* f doit etre appelee exactement strlen(s) fois */
static void	test_strmapi_calls(const char *name, const char *s)
{
	char	*ret;
	int		ok;

	g_calls = 0;
	ret = ft_strmapi(s, map_count);
	ok = (ret != NULL && g_calls == strlen(s) && strcmp(ret, s) == 0);
	report(name, ok);
	if (!ok)
		printf("     f appelee %u fois (attendu %zu)\n", g_calls, strlen(s));
	free(ret);
}

/* ================================================================== */
/* striteri : callbacks                                               */
/* ================================================================== */
static void	it_upper(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper((unsigned char)*c);
}

static void	it_next(unsigned int i, char *c)
{
	(void)i;
	*c = (char)(*c + 1);
}

static void	it_index(unsigned int i, char *c)
{
	*c = (char)('a' + i);
}

static void	it_count(unsigned int i, char *c)
{
	(void)c;
	if (i != g_calls)
		g_order = 0;
	g_calls++;
}

/* on compare 64 octets : rien ne doit etre ecrit apres le \0 */
static void	test_striteri(const char *name, const char *s,
				void (*f)(unsigned int, char *), const char *exp)
{
	char	buf[64];
	char	e[64];
	int		ok;

	memset(buf, 'X', 64);
	memset(e, 'X', 64);
	strcpy(buf, s);
	strcpy(e, exp);
	ft_striteri(buf, f);
	ok = (memcmp(buf, e, 64) == 0);
	report(name, ok);
	if (!ok)
		printf("     buf=\"%.40s\" (attendu \"%.40s\")\n", buf, e);
}

/* f appelee strlen(s) fois, avec les indices 0, 1, 2... dans l'ordre */
static void	test_striteri_calls(const char *name, const char *s)
{
	char	buf[64];
	int		ok;

	strcpy(buf, s);
	g_calls = 0;
	g_order = 1;
	ft_striteri(buf, it_count);
	ok = (g_calls == strlen(s) && g_order == 1);
	report(name, ok);
	if (!ok)
		printf("     f appelee %u fois (attendu %zu), ordre des indices %s\n",
			g_calls, strlen(s), g_order ? "correct" : "FAUX");
}

/* ================================================================== */
/* put*_fd : on ecrit dans un pipe, puis on relit ce qui y est passe  */
/* ================================================================== */
static size_t	slurp(int fd, char *buf, size_t size)
{
	size_t	total;
	ssize_t	n;

	total = 0;
	while (total < size)
	{
		n = read(fd, buf + total, size - total);
		if (n <= 0)
			break ;
		total += n;
	}
	return (total);
}

static void	open_pipe(int p[2])
{
	if (pipe(p) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

static size_t	close_and_read(int p[2], char *out, size_t size)
{
	size_t	n;

	close(p[1]);
	n = slurp(p[0], out, size);
	close(p[0]);
	out[n] = '\0';
	return (n);
}

static void	check_output(const char *name, const char *out, size_t n,
				const char *exp, size_t exp_len)
{
	int	ok;

	ok = (n == exp_len && memcmp(out, exp, exp_len) == 0);
	report(name, ok);
	if (!ok)
		printf("     recu %zu octet(s) \"%.40s\" (attendu %zu \"%.40s\")\n",
			n, out, exp_len, exp);
}

static void	test_putchar(const char *name, char c)
{
	int		p[2];
	char	out[OUT_SIZE];
	char	exp[2];
	size_t	n;

	exp[0] = c;
	exp[1] = '\0';
	open_pipe(p);
	ft_putchar_fd(c, p[1]);
	n = close_and_read(p, out, OUT_SIZE - 1);
	check_output(name, out, n, exp, 1);
}

static void	test_putstr(const char *name, const char *s)
{
	int		p[2];
	char	out[OUT_SIZE];
	char	tmp[OUT_SIZE];
	size_t	n;

	strcpy(tmp, s);
	open_pipe(p);
	ft_putstr_fd(tmp, p[1]);
	n = close_and_read(p, out, OUT_SIZE - 1);
	check_output(name, out, n, s, strlen(s));
}

static void	test_putendl(const char *name, const char *s)
{
	int		p[2];
	char	out[OUT_SIZE];
	char	tmp[OUT_SIZE];
	char	exp[OUT_SIZE];
	size_t	n;

	strcpy(tmp, s);
	strcpy(exp, s);
	strcat(exp, "\n");
	open_pipe(p);
	ft_putendl_fd(tmp, p[1]);
	n = close_and_read(p, out, OUT_SIZE - 1);
	check_output(name, out, n, exp, strlen(exp));
}

static void	test_putnbr(const char *name, int nb)
{
	int		p[2];
	char	out[OUT_SIZE];
	char	exp[16];
	size_t	n;

	snprintf(exp, sizeof exp, "%d", nb);
	open_pipe(p);
	ft_putnbr_fd(nb, p[1]);
	n = close_and_read(p, out, OUT_SIZE - 1);
	check_output(name, out, n, exp, strlen(exp));
}

static void	test_putnbr_range(const char *name, int from, int to)
{
	int		p[2];
	char	out[OUT_SIZE];
	char	exp[16];
	size_t	n;
	int		nb;
	int		bad;

	bad = 0;
	nb = from;
	while (nb <= to)
	{
		snprintf(exp, sizeof exp, "%d", nb);
		open_pipe(p);
		ft_putnbr_fd(nb, p[1]);
		n = close_and_read(p, out, OUT_SIZE - 1);
		if (n != strlen(exp) || memcmp(out, exp, n) != 0)
			bad++;
		nb++;
	}
	report(name, bad == 0);
	if (bad)
		printf("     %d echec(s) sur %d valeurs\n", bad, to - from + 1);
}

/* fd invalide : write echoue, la fonction ne doit ni planter ni boucler */
static void	test_invalid_fd(void)
{
	char	s1[] = "abc";
	char	s2[] = "abc";

	ft_putchar_fd('a', -1);
	ft_putstr_fd(s1, -1);
	ft_putendl_fd(s2, -1);
	ft_putnbr_fd(42, -1);
	report("fd invalide (-1) : aucune fonction ne plante", 1);
}

#endif

#if TEST_LIST

/* ================================================================== */
/* listes : les listes de test sont construites a la main (malloc),    */
/* sans utiliser les fonctions testees : un bug de ft_lstnew ne fausse */
/* pas les autres sections. Tous les noeuds sont enregistres puis      */
/* liberes a la fin de chaque test, meme si ta liste est corrompue.    */
/* ================================================================== */
# define MAX_NODES 12000

static t_list	*g_nodes[MAX_NODES];
static size_t	g_node_count = 0;
static int		g_nb = 42;
static t_list	g_dummy;

static t_list	*mk(void *content, t_list *next)
{
	t_list	*n;

	if (g_node_count >= MAX_NODES)
	{
		printf("trop de noeuds dans le tester (MAX_NODES)\n");
		exit(1);
	}
	n = malloc(sizeof(t_list));
	if (n == NULL)
		exit(1);
	n->content = content;
	n->next = next;
	g_nodes[g_node_count] = n;
	g_node_count++;
	return (n);
}

static void	free_all_nodes(void)
{
	size_t	i;

	i = 0;
	while (i < g_node_count)
	{
		free(g_nodes[i]);
		i++;
	}
	g_node_count = 0;
}

/* items : tableau de chaines termine par NULL ({NULL} = liste vide) */
static t_list	*mk_list(const char **items)
{
	t_list	*head;
	size_t	n;

	n = 0;
	while (items[n])
		n++;
	head = NULL;
	while (n > 0)
	{
		n--;
		head = mk((void *)items[n], head);
	}
	return (head);
}

/* la liste doit contenir exactement exp, dans l'ordre, puis finir par NULL */
static int	list_matches(t_list *l, const char **exp)
{
	size_t	i;

	i = 0;
	while (exp[i])
	{
		if (l == NULL || l->content == NULL
			|| strcmp((char *)l->content, exp[i]) != 0)
			return (0);
		l = l->next;
		i++;
	}
	return (l == NULL);
}

static void	print_list(t_list *l)
{
	size_t	i;

	printf("     liste :");
	i = 0;
	while (l && i < 20)
	{
		printf(" \"%s\"", l->content ? (char *)l->content : "(null)");
		l = l->next;
		i++;
	}
	printf(" (%zu noeud%s%s)\n", i, i > 1 ? "s" : "", l ? " ou plus" : "");
}

static size_t	count_nodes(t_list *l)
{
	size_t	n;

	n = 0;
	while (l && n <= MAX_NODES)
	{
		n++;
		l = l->next;
	}
	return (n);
}

static t_list	*last_node(t_list *l)
{
	size_t	n;

	n = 0;
	while (l && l->next && n <= MAX_NODES)
	{
		l = l->next;
		n++;
	}
	return (l);
}

/* ------------------------------------------------------------------ */
/* lstnew                                                             */
/* ------------------------------------------------------------------ */
static void	test_lstnew(const char *name, void *content)
{
	t_list	*n;
	int		ok;

	n = ft_lstnew(content);
	ok = (n != NULL && n->content == content && n->next == NULL);
	report(name, ok);
	if (!ok && n == NULL)
		printf("     retour NULL\n");
	else if (!ok)
		printf("     content=%p (attendu %p) next=%p (attendu (nil))\n",
			n->content, content, (void *)n->next);
	free(n);
}

/* tas sale : sur glibc, un bloc libere puis reutilise via le cache (tcache)
   voit son 2e mot remis a 0, ce qui cacherait un next non initialise.
   On sature donc d'abord le cache (7 blocs) pour que ft_lstnew recupere
   un bloc "classique" qui garde les 'X' dans ses champs. */
static void	test_lstnew_dirty(const char *name, void *content)
{
	void	*blk[9];
	t_list	*n;
	int		i;
	int		ok;

	i = 0;
	while (i < 9)
	{
		blk[i] = malloc(sizeof(t_list));
		memset(blk[i], 'X', sizeof(t_list));
		i++;
	}
	i = 0;
	while (i < 9)
		free(blk[i++]);
	i = 0;
	while (i < 7)
		blk[i++] = malloc(sizeof(t_list));
	n = ft_lstnew(content);
	ok = (n != NULL && n->content == content && n->next == NULL);
	report(name, ok);
	if (!ok && n != NULL)
		printf("     next=%p (attendu (nil)) : next non initialise ?\n",
			(void *)n->next);
	free(n);
	i = 0;
	while (i < 7)
		free(blk[i++]);
}

static void	test_lstnew_two(void)
{
	t_list	*a;
	t_list	*b;
	int		ok;

	a = ft_lstnew(&g_nb);
	b = ft_lstnew(&g_nb);
	ok = (a != NULL && b != NULL && a != b);
	report("deux appels : deux noeuds distincts", ok);
	free(a);
	if (b != a)
		free(b);
}

/* ------------------------------------------------------------------ */
/* lstadd_front : on ajoute les noeuds de adds un par un, devant      */
/* ------------------------------------------------------------------ */
static void	test_add_front(const char *name, const char **init,
				const char **adds, const char **exp)
{
	t_list	*head;
	t_list	*n;
	t_list	*last;
	size_t	i;
	int		ok;

	head = mk_list(init);
	last = NULL;
	i = 0;
	while (adds[i])
	{
		n = mk((void *)adds[i], NULL);
		ft_lstadd_front(&head, n);
		last = n;
		i++;
	}
	ok = (list_matches(head, exp) && (last == NULL || head == last));
	report(name, ok);
	if (!ok)
		print_list(head);
	free_all_nodes();
}

static void	test_add_front_many(const char *name, size_t count)
{
	t_list	*head;
	t_list	*n;
	size_t	i;
	int		ok;

	head = NULL;
	n = NULL;
	i = 0;
	while (i < count)
	{
		n = mk("x", NULL);
		ft_lstadd_front(&head, n);
		i++;
	}
	ok = (head == n && count_nodes(head) == count);
	report(name, ok);
	if (!ok)
		printf("     %zu noeud(s) (attendu %zu)\n", count_nodes(head), count);
	free_all_nodes();
}

/* ------------------------------------------------------------------ */
/* lstsize                                                            */
/* ------------------------------------------------------------------ */
static void	test_lstsize(const char *name, const char **items, int exp)
{
	t_list	*head;
	int		ret;
	int		ok;

	head = mk_list(items);
	ret = ft_lstsize(head);
	ok = (ret == exp && list_matches(head, items));
	report(name, ok);
	if (!ok)
		printf("     ret=%d (attendu %d)\n", ret, exp);
	free_all_nodes();
}

static void	test_lstsize_big(const char *name, size_t count)
{
	t_list	*head;
	size_t	i;
	int		ret;

	head = NULL;
	i = 0;
	while (i < count)
	{
		head = mk("x", head);
		i++;
	}
	ret = ft_lstsize(head);
	report(name, (size_t)ret == count);
	if ((size_t)ret != count)
		printf("     ret=%d (attendu %zu)\n", ret, count);
	free_all_nodes();
}

/* ------------------------------------------------------------------ */
/* lstlast                                                            */
/* ------------------------------------------------------------------ */
static void	test_lstlast(const char *name, const char **items)
{
	t_list	*head;
	t_list	*exp;
	t_list	*ret;
	int		ok;

	head = mk_list(items);
	exp = last_node(head);
	ret = ft_lstlast(head);
	ok = (ret == exp && list_matches(head, items));
	report(name, ok);
	if (!ok)
		printf("     retour %p (attendu %p)\n", (void *)ret, (void *)exp);
	free_all_nodes();
}

/* ------------------------------------------------------------------ */
/* lstadd_back : on ajoute les noeuds de adds un par un, a la fin     */
/* ------------------------------------------------------------------ */
static void	test_add_back(const char *name, const char **init,
				const char **adds, const char **exp)
{
	t_list	*head;
	t_list	*n;
	t_list	*first_expected;
	size_t	i;
	int		ok;

	head = mk_list(init);
	first_expected = head;
	i = 0;
	while (adds[i])
	{
		n = mk((void *)adds[i], NULL);
		if (first_expected == NULL)
			first_expected = n;
		ft_lstadd_back(&head, n);
		i++;
	}
	ok = (list_matches(head, exp) && head == first_expected);
	report(name, ok);
	if (!ok)
		print_list(head);
	free_all_nodes();
}

static void	test_add_back_many(const char *name, size_t count)
{
	t_list	*head;
	t_list	*first;
	t_list	*n;
	size_t	i;
	int		ok;

	head = NULL;
	first = NULL;
	n = NULL;
	i = 0;
	while (i < count)
	{
		n = mk("x", NULL);
		if (first == NULL)
			first = n;
		ft_lstadd_back(&head, n);
		i++;
	}
	ok = (head == first && last_node(head) == n && count_nodes(head) == count);
	report(name, ok);
	if (!ok)
		printf("     %zu noeud(s) (attendu %zu)\n", count_nodes(head), count);
	free_all_nodes();
}

/* add_back et add_front melanges : a, puis b devant, puis c derriere... */
static void	test_lst_mix(void)
{
	t_list	*head;
	int		ok;

	head = NULL;
	ft_lstadd_back(&head, mk("a", NULL));
	ft_lstadd_front(&head, mk("b", NULL));
	ft_lstadd_back(&head, mk("c", NULL));
	ft_lstadd_front(&head, mk("d", NULL));
	ok = list_matches(head, (const char *[]){"d", "b", "a", "c", NULL});
	report("add_back / add_front melanges (d b a c)", ok);
	if (!ok)
		print_list(head);
	free_all_nodes();
}

#endif

/* ================================================================== */
int	main(void)
{
	unsigned char		big[BUF];
	const char			str[] = "hello world";
	const unsigned char	bin[] = {1, 2, 0, 3, 0xff, 5};
	const char			bin_cpy[] = "ab\0cd\0ef";

	memset(big, 'Q', BUF);
	memset(long_str, 'A', 4000);
	long_str[4000] = '\0';

	strcpy(long_exp, long_str);
	strcat(long_exp, "END");
	
	strcpy(long_pad, "   ");
	strcat(long_pad, long_str);
	strcat(long_pad, "   ");

	section("isalpha / isdigit / isalnum / isascii / isprint (0..255)");
	test_ctype("isalpha", ft_isalpha, isalpha, 0);
	test_ctype("isdigit", ft_isdigit, isdigit, 0);
	test_ctype("isalnum", ft_isalnum, isalnum, 0);
	test_ctype("isascii", ft_isascii, isascii, 0);
	test_ctype("isprint", ft_isprint, isprint, 0);

	section("toupper / tolower (0..255)");
	test_ctype("toupper", ft_toupper, toupper, 1);
	test_ctype("tolower", ft_tolower, tolower, 1);

	section("strlen");
	test_strlen("chaine vide", "");
	test_strlen("1 caractere", "a");
	test_strlen("Luka", "Luka");
	test_strlen("avec espaces", "hello world 42");
	test_strlen("\\0 au milieu (s'arrete au premier)", "ab\0cd");
	test_strlen("longue chaine",
		"0123456789012345678901234567890123456789012345678901234567890123456789");

	section("bzero");
	test_bzero("met 10 octets a 0 au milieu", 4, 10);
	test_bzero("n == 0 (rien ne change)", 4, 0);
	test_bzero("tout le buffer", 0, BUF);
	test_bzero("dernier octet seulement", BUF - 1, 1);

	section("strlcpy");
	/*            nom                      src     size  dst attendu retour */
	test_strlcpy("copie normale",          "Luka", 20,   "Luka",     4);
	test_strlcpy("rentre pile",            "Luka", 5,    "Luka",     4);
	test_strlcpy("1 octet de trop",        "Luka", 4,    "Luk",      4);
	test_strlcpy("troncature",             "Luka", 3,    "Lu",       4);
	test_strlcpy("size == 2",              "Luka", 2,    "L",        4);
	test_strlcpy("size == 1",              "Luka", 1,    "",         4);
	test_strlcpy("size == 0 (rien ecrit)", "Luka", 0,    "",         4);
	test_strlcpy("src vide",               "",     10,   "",         0);
	test_strlcpy("src vide, size == 0",    "",     0,    "",         0);

	section("strlcat");
	/*            nom                     dst       src      size  dst attendu   retour */
	test_strlcat("copie normale",         "Hello ", "World", 20,  "Hello World", 11);
	test_strlcat("troncature",            "Hello",  " World", 8,  "Hello W",     11);
	test_strlcat("rentre pile",           "abc",    "de",    6,   "abcde",       5);
	test_strlcat("1 octet de trop",       "abc",    "de",    5,   "abcd",        5);
	test_strlcat("size == 0",             "abc",    "de",    0,   "abc",         2);
	test_strlcat("size < strlen(dst)",    "abcdef", "gh",    3,   "abcdef",      5);
	test_strlcat("size == strlen(dst)",   "abc",    "de",    3,   "abc",         5);
	test_strlcat("size == strlen(dst)+1", "abc",    "de",    4,   "abc",         5);
	test_strlcat("src vide",              "abc",    "",      10,  "abc",         3);
	test_strlcat("dst vide",              "",       "Luka",  10,  "Luka",        4);

	section("strchr");
	test_strchr("premier 'l'", "hello", 'l');
	test_strchr("premier caractere", "hello", 'h');
	test_strchr("dernier caractere", "hello", 'o');
	test_strchr("introuvable", "hello", 'z');
	test_strchr("recherche de '\\0'", "hello", '\0');
	test_strchr("chaine vide, 'a'", "", 'a');
	test_strchr("chaine vide, '\\0'", "", '\0');
	test_strchr("c > 255 ('l' + 256)", "hello", 'l' + 256);

	section("strrchr");
	test_strrchr("dernier 'l'", "hello", 'l');
	test_strrchr("un seul 'h'", "hello", 'h');
	test_strrchr("meme caractere partout", "aaaa", 'a');
	test_strrchr("introuvable", "hello", 'z');
	test_strrchr("recherche de '\\0'", "hello", '\0');
	test_strrchr("chaine vide, 'a'", "", 'a');
	test_strrchr("chaine vide, '\\0'", "", '\0');
	test_strrchr("c > 255 ('l' + 256)", "hello", 'l' + 256);

	section("strncmp");
	test_strncmp("identiques", "hello", "hello", 5);
	test_strncmp("difference au milieu", "hello", "help", 5);
	test_strncmp("n avant la difference", "hello", "help", 3);
	test_strncmp("n == 0", "abc", "xyz", 0);
	test_strncmp("s1 prefixe de s2", "abc", "abcd", 4);
	test_strncmp("s2 prefixe de s1", "abcd", "abc", 4);
	test_strncmp("n depasse la longueur", "abc", "abc", 100);
	test_strncmp("deux chaines vides", "", "", 5);
	test_strncmp("une chaine vide", "", "a", 5);
	test_strncmp("s'arrete au \\0", "ab\0cd", "ab\0xy", 5);
	test_strncmp("majuscule vs minuscule", "A", "a", 1);
	test_strncmp("unsigned char (\\xff > \\x01)", "abc\xff", "abc\x01", 4);
	test_strncmp("unsigned char inverse", "abc\x01", "abc\xff", 4);

	section("strnstr");
	/*            nom                          big                 little       len  offset */
	test_strnstr("trouve",                     "Hello World",      "World",     11,  6);
	test_strnstr("len trop court de 1",        "Hello World",      "World",     10,  -1);
	test_strnstr("len bien trop court",        "Hello World",      "World",     5,   -1);
	test_strnstr("len > strlen(big)",          "lorem ipsum dolor", "dolor",    100, 12);
	test_strnstr("little vide",                "abc",              "",          5,   0);
	test_strnstr("little vide, len == 0",      "abc",              "",          0,   0);
	test_strnstr("big vide, little non vide",  "",                 "a",         5,   -1);
	test_strnstr("big et little vides",        "",                 "",          5,   0);
	test_strnstr("len == 0",                   "abc",              "a",         0,   -1);
	test_strnstr("little plus long que big",   "abc",              "abcd",      10,  -1);
	test_strnstr("identique, len pile",        "abc",              "abc",       3,   0);
	test_strnstr("identique, len - 1",         "abc",              "abc",       2,   -1);
	test_strnstr("premiere occurrence",        "abcabc",           "c",         6,   2);
	test_strnstr("n coupe avant 2eme occ.",    "abcabc",           "c",         2,   -1);
	test_strnstr("faux depart (aab dans aaabc)", "aaabc",          "aab",       5,   1);
	test_strnstr("faux depart long",           "MZIRIBMZIRIBMZE123", "MZIRIBMZE", 15, 6);
	test_strnstr("faux depart long, len - 1",  "MZIRIBMZIRIBMZE123", "MZIRIBMZE", 14, -1);

	section("atoi");
	test_atoi("42");
	test_atoi("0");
	test_atoi("-42");
	test_atoi("+42");
	test_atoi("   42");
	test_atoi("\t\n\v\f\r 42");
	test_atoi("42abc");
	test_atoi("abc42");
	test_atoi("");
	test_atoi("   ");
	test_atoi("-");
	test_atoi("+");
	test_atoi("--42");
	test_atoi("+-42");
	test_atoi("-+42");
	test_atoi("- 42");
	test_atoi("0042");
	test_atoi("-0");
	test_atoi("2147483647");
	test_atoi("-2147483648");
	test_atoi("12 34");

	section("memset");
	test_memset("remplit 10 octets au milieu", 4, 'A', 10);
	test_memset("n == 0 (rien ne change)", 4, 'A', 0);
	test_memset("valeur 0", 0, 0, BUF);
	test_memset("valeur > 255 (0x141 -> 'A')", 0, 0x141, 8);
	test_memset("valeur negative (-1 -> 0xFF)", 0, -1, 8);
	test_memset("tout le buffer", 0, 'Z', BUF);
	test_memset("dernier octet seulement", BUF - 1, 'Z', 1);

	section("memchr");
	test_memchr("trouve 'o'", str, 'o', sizeof str);
	test_memchr("premier octet", str, 'h', sizeof str);
	test_memchr("trouve le \\0 final", str, '\0', sizeof str);
	test_memchr("introuvable", str, 'z', sizeof str);
	test_memchr("n coupe juste avant le char", str, 'w', 6);
	test_memchr("n pile sur le char", str, 'w', 7);
	test_memchr("n == 0", str, 'h', 0);
	test_memchr("c > 255 ('l' + 256)", str, 'l' + 256, sizeof str);
	test_memchr("\\0 au milieu des donnees", bin, 0, sizeof bin);
	test_memchr("octet 0xff", bin, 0xff, sizeof bin);
	test_memchr("dernier octet", bin, 5, sizeof bin);

	section("memcmp");
	test_memcmp("identiques", "hello", "hello", 5);
	test_memcmp("difference au milieu", "abc", "abd", 3);
	test_memcmp("difference s1 > s2", "abd", "abc", 3);
	test_memcmp("n avant la difference", "abcX", "abcY", 3);
	test_memcmp("n == 0", "abc", "xyz", 0);
	test_memcmp("ne s'arrete PAS au \\0", "ab\0cd", "ab\0xy", 5);
	test_memcmp("\\0 identiques, n coupe avant", "ab\0cd", "ab\0xy", 3);
	test_memcmp("unsigned char (\\xff > \\x01)", "\xff", "\x01", 1);
	test_memcmp("unsigned char inverse", "\x01", "\xff", 1);
	test_memcmp("1 octet egal", "a", "a", 1);

	section("memcpy");
	test_memcpy("copie normale (\"Luka\" + \\0)", "Luka", 5, 0);
	test_memcpy("n == 0", "Luka", 0, 0);
	test_memcpy("avec des \\0 au milieu", bin_cpy, sizeof bin_cpy, 3);
	test_memcpy("1 octet en fin de buffer", "Z", 1, BUF - 1);
	test_memcpy("32 octets", big, BUF, 0);

	section("memmove");
	test_memmove("chevauchement dst > src", 2, 0, 6);
	test_memmove("chevauchement dst < src", 0, 2, 6);
	test_memmove("decalage de 1 vers l'avant", 1, 0, 15);
	test_memmove("decalage de 1 vers l'arriere", 0, 1, 15);
	test_memmove("dst colle apres src", 4, 0, 4);
	test_memmove("sans chevauchement", 8, 0, 8);
	test_memmove("dst == src", 4, 4, 8);
	test_memmove("n == 0", 2, 0, 0);


	section("calloc");
	test_calloc("5 int", 5, sizeof(int));
	test_calloc("1 octet", 1, 1);
	test_calloc("100 char", 100, sizeof(char));
	test_calloc("1000 long", 1000, sizeof(long));
	test_calloc("gros bloc (1 Mo)", 1024, 1024);
	test_calloc_dirty("tas sale (256 octets)", 256);
	test_calloc_zero("nmemb == 0", 0, 4);
	test_calloc_zero("size == 0", 4, 0);
	test_calloc_zero("nmemb == 0 et size == 0", 0, 0);
	test_calloc_overflow("overflow SIZE_MAX * 2", SIZE_MAX, 2);
	test_calloc_overflow("overflow 2 * SIZE_MAX", 2, SIZE_MAX);
	test_calloc_overflow("overflow pile (SIZE_MAX/2 + 1) * 2", SIZE_MAX / 2 + 1, 2);

	
	section("split");
	test_split("deux mots", "hello world", ' ',(const char *[]){"hello", "world", NULL});
	test_split("trois mots", "a b c", ' ',(const char *[]){"a", "b", "c", NULL});
	test_split("mots d'un caractere", "a b c d e f", ' ',(const char *[]){"a", "b", "c", "d", "e", "f", NULL});
	test_split("separateurs multiples", "hello   world", ' ',(const char *[]){"hello", "world", NULL});
	test_split("separateurs en debut", "   hello world", ' ',(const char *[]){"hello", "world", NULL});
	test_split("separateurs en fin", "hello world   ", ' ',(const char *[]){"hello", "world", NULL});
	test_split("separateurs debut et fin", "  hello  world  ", ' ',(const char *[]){"hello", "world", NULL});
	test_split("aucun separateur dans la chaine", "hello", ' ',(const char *[]){"hello", NULL});
	test_split("separateur absent (c = 'z')", "lorem ipsum", 'z',(const char *[]){"lorem ipsum", NULL});
	test_split("un seul caractere", "a", ' ',(const char *[]){"a", NULL});
	test_split("chaine vide", "", ' ',(const char *[]){NULL});
	test_split("un seul separateur", " ", ' ',(const char *[]){NULL});
	test_split("que des separateurs", "     ", ' ',(const char *[]){NULL});
	test_split("autre separateur (',')", "a,b,,c", ',',(const char *[]){"a", "b", "c", NULL});
	test_split("separateur tab", "a\tb", '\t',(const char *[]){"a", "b", NULL});
	test_split("separateur '\\0' (un seul mot)", "hello world", '\0',(const char *[]){"hello world", NULL});
	test_split("classique 42", "split  ||this|for|me|||||!|", '|',(const char *[]){"split  ", "this", "for", "me", "!", NULL});
	

	section("strdup");
	test_strdup("mot simple", "hello");
	test_strdup("Luka", "Luka");
	test_strdup("avec espaces", "hello world 42");
	test_strdup("1 caractere", "a");
	test_strdup("chaine vide", "");
	test_strdup("\\0 au milieu (copie jusqu'au premier)", "ab\0cd");
	test_strdup("octets > 127", "\xff\x80\xc3\xa9");
	test_strdup("caracteres speciaux", "\t\n\\\"'%s%d");
	test_strdup("grande chaine (4000 caracteres)", long_str);
	
	section("substr");
	/*          nom                         s              start      len   attendu */
	test_substr("debut",                    "hello world", 0,         5,    "hello");
	test_substr("milieu",                   "hello world", 6,         3,    "wor");
	test_substr("fin pile",                 "hello world", 6,         5,    "world");
	test_substr("len depasse la fin",       "hello world", 6,         100,  "world");
	test_substr("len == SIZE_MAX",          "hello world", 6,         SIZE_MAX, "world");
	test_substr("chaine entiere",           "hello world", 0,         11,   "hello world");
	test_substr("1 caractere",              "hello world", 4,         1,    "o");
	test_substr("dernier caractere",        "hello world", 10,        1,    "d");
	test_substr("len == 0",                 "hello world", 3,         0,    "");
	test_substr("start == strlen(s)",       "hello world", 11,        5,    "");
	test_substr("start > strlen(s)",        "hello world", 50,        5,    "");
	test_substr("start == UINT_MAX",        "hello world", UINT_MAX,  5,    "");
	test_substr("chaine vide",              "",            0,         5,    "");
	test_substr("chaine vide, len == 0",    "",            0,         0,    "");

	section("strjoin");
	/*           nom                      s1        s2       attendu */
	test_strjoin("deux mots",             "hello",  "world", "helloworld");
	test_strjoin("avec espace",           "hello ", "world", "hello world");
	test_strjoin("Luka + 42",             "Luka",   "42",    "Luka42");
	test_strjoin("1 caractere chacun",    "a",      "b",     "ab");
	test_strjoin("s1 vide",               "",       "world", "world");
	test_strjoin("s2 vide",               "hello",  "",      "hello");
	test_strjoin("les deux vides",        "",       "",      "");
	test_strjoin("\\0 au milieu de s1",   "ab\0cd", "ef",    "abef");
	test_strjoin("\\0 au milieu de s2",   "ab",     "cd\0ef", "abcd");
	test_strjoin("octets > 127",          "\xff\x80", "\xc3\xa9", "\xff\x80\xc3\xa9");
	test_strjoin("grande chaine",         long_str, "END",   long_exp);
	
	section("strtrim");
	/*           nom                          s1               set      attendu */
	test_strtrim("espaces des deux cotes",    "   hello   ",   " ",     "hello");
	test_strtrim("debut seulement",           "   hello",      " ",     "hello");
	test_strtrim("fin seulement",             "hello   ",       " ",     "hello");
	test_strtrim("rien a retirer",            "hello",          " ",     "hello");
	test_strtrim("espaces du milieu gardes",  "  hello world  ", " ",    "hello world");
	test_strtrim("set de plusieurs chars",    "xyhelloyx",      "xy",    "hello");
	test_strtrim("ordre quelconque dans set", "abchellocba",    "abc",   "hello");
	test_strtrim("char du set au milieu",     "xxhexxlloxx",    "x",     "hexxllo");
	test_strtrim("tab et newline",            "\t\n hello \n\t", " \t\n", "hello");
	test_strtrim("set sans rapport",          "  hello  ",      "x",     "  hello  ");
	test_strtrim("set vide",                  "  hello  ",      "",      "  hello  ");
	test_strtrim("tout est dans le set",      "aaaa",           "a",     "");
	test_strtrim("tout dans le set (2 chars)", "abab",          "ab",    "");
	test_strtrim("s1 == set",                 "hello",          "hello", "");
	test_strtrim("1 caractere retire",        "a",              "a",     "");
	test_strtrim("1 caractere conserve",      "a",              "b",     "a");
	test_strtrim("s1 vide",                   "",               " ",     "");
	test_strtrim("s1 vide et set vide",       "",               "",      "");
	test_strtrim("octets > 127",              "\xff\x80hi\x80\xff", "\xff\x80", "hi");
	test_strtrim("grande chaine",             long_pad,         " ",     long_str);

#if TEST_PART2
	section("itoa");
	test_itoa("zero", 0);
	test_itoa("1 chiffre", 5);
	test_itoa("1 chiffre negatif", -5);
	test_itoa("9", 9);
	test_itoa("10", 10);
	test_itoa("-10", -10);
	test_itoa("42", 42);
	test_itoa("-42", -42);
	test_itoa("100", 100);
	test_itoa("12345", 12345);
	test_itoa("-12345", -12345);
	test_itoa("1000000000 (10 chiffres)", 1000000000);
	test_itoa("-1000000000", -1000000000);
	test_itoa("INT_MAX", INT_MAX);
	test_itoa("INT_MAX - 1", INT_MAX - 1);
	test_itoa("INT_MIN + 1", INT_MIN + 1);
	test_itoa("INT_MIN", INT_MIN);
	test_itoa_range("tous les entiers de -10000 a 10000", -10000, 10000);
	test_itoa_two_calls();

	section("strmapi");
	/*            nom                            s             f          attendu */
	test_strmapi("majuscules",                   "hello",      map_upper, "HELLO");
	test_strmapi("identite",                     "Luka",       map_ident, "Luka");
	test_strmapi("c + 1",                        "HAL",        map_next,  "IBM");
	test_strmapi("utilise l'indice",             "xxxxx",      map_index, "abcde");
	test_strmapi("indice > 9",                   "xxxxxxxxxxxx", map_index, "abcdefghijkl");
	test_strmapi("indice pair / impair",         "abcdef",     map_alt,   "aBcDeF");
	test_strmapi("indice pair / impair (2)",     "HELLO",      map_alt,   "hElLo");
	test_strmapi("1 caractere",                  "a",          map_upper, "A");
	test_strmapi("chaine vide",                  "",           map_upper, "");
	test_strmapi("octets > 127",                 "\xff\x80",   map_ident, "\xff\x80");
	test_strmapi_calls("f appelee strlen(s) fois", "hello");
	test_strmapi_calls("0 appel sur chaine vide", "");
	test_strmapi_calls("30 appels", "abcdefghijklmnopqrstuvwxyz0123");

	section("striteri");
	/*             nom                             s               f         attendu */
	test_striteri("majuscules",                    "hello",        it_upper, "HELLO");
	test_striteri("deja en majuscules",            "ABC",          it_upper, "ABC");
	test_striteri("c + 1",                         "HAL",          it_next,  "IBM");
	test_striteri("ecrase avec l'indice",          "xxxxx",        it_index, "abcde");
	test_striteri("indice > 9",                    "xxxxxxxxxxxx", it_index, "abcdefghijkl");
	test_striteri("1 caractere",                   "a",            it_upper, "A");
	test_striteri("chaine vide",                   "",             it_upper, "");
	test_striteri("n'ecrit pas apres le \\0",      "ab",           it_upper, "AB");
	test_striteri_calls("f appelee 5 fois, indices 0..4 dans l'ordre", "hello");
	test_striteri_calls("1 appel", "a");
	test_striteri_calls("0 appel sur chaine vide", "");

	section("putchar_fd");
	test_putchar("lettre minuscule", 'a');
	test_putchar("lettre majuscule", 'Z');
	test_putchar("chiffre", '0');
	test_putchar("espace", ' ');
	test_putchar("newline", '\n');
	test_putchar("tabulation", '\t');
	test_putchar("'\\0' (1 octet nul ecrit)", '\0');
	test_putchar("octet 0x80", '\x80');
	test_putchar("octet 0xff", '\xff');

	section("putstr_fd");
	test_putstr("mot simple", "hello");
	test_putstr("avec espaces", "hello world 42");
	test_putstr("avec newline et tab", "line1\nline2\ttab");
	test_putstr("1 caractere", "a");
	test_putstr("chaine vide (rien ecrit)", "");
	test_putstr("s'arrete au \\0", "ab\0cd");
	test_putstr("octets > 127 (UTF-8)", "\xc3\xa9\xe2\x82\xac");
	test_putstr("grande chaine (4000 caracteres)", long_str);

	section("putendl_fd");
	test_putendl("mot simple", "hello");
	test_putendl("avec espaces", "hello world 42");
	test_putendl("1 caractere", "a");
	test_putendl("chaine vide (juste le \\n)", "");
	test_putendl("s'arrete au \\0 puis \\n", "ab\0cd");
	test_putendl("grande chaine (4000 caracteres)", long_str);

	section("putnbr_fd");
	test_putnbr("zero", 0);
	test_putnbr("1 chiffre", 7);
	test_putnbr("1 chiffre negatif", -5);
	test_putnbr("10", 10);
	test_putnbr("-10", -10);
	test_putnbr("42", 42);
	test_putnbr("-42", -42);
	test_putnbr("-1", -1);
	test_putnbr("100", 100);
	test_putnbr("1000000", 1000000);
	test_putnbr("1000000000 (10 chiffres)", 1000000000);
	test_putnbr("-1000000000", -1000000000);
	test_putnbr("INT_MAX", INT_MAX);
	test_putnbr("INT_MIN + 1", INT_MIN + 1);
	test_putnbr("INT_MIN", INT_MIN);
	test_putnbr_range("tous les entiers de -300 a 300", -300, 300);

	section("fd invalide");
	test_invalid_fd();
#endif

#if TEST_LIST
	section("lstnew");
	test_lstnew("pointeur sur int", &g_nb);
	test_lstnew("chaine", "hello");
	test_lstnew("chaine vide", "");
	test_lstnew("pointeur sur struct", &g_dummy);
	test_lstnew("content == NULL", NULL);
	test_lstnew_dirty("tas sale, content non NULL", &g_nb);
	test_lstnew_dirty("tas sale, content == NULL", NULL);
	test_lstnew_two();

	section("lstadd_front");
	/*               nom                      liste de depart      ajouts (dans l'ordre)   liste attendue */
	test_add_front("liste vide + 1 ajout",    (const char *[]){NULL},
		(const char *[]){"a", NULL}, (const char *[]){"a", NULL});
	test_add_front("1 element + 1 ajout",     (const char *[]){"b", NULL},
		(const char *[]){"a", NULL}, (const char *[]){"a", "b", NULL});
	test_add_front("3 elements + 1 ajout",    (const char *[]){"x", "y", "z", NULL},
		(const char *[]){"w", NULL}, (const char *[]){"w", "x", "y", "z", NULL});
	test_add_front("liste vide + 3 ajouts",   (const char *[]){NULL},
		(const char *[]){"a", "b", "c", NULL}, (const char *[]){"c", "b", "a", NULL});
	test_add_front("1 element + 2 ajouts",    (const char *[]){"c", NULL},
		(const char *[]){"b", "a", NULL}, (const char *[]){"a", "b", "c", NULL});
	test_add_front_many("1000 ajouts devant", 1000);

	section("lstsize");
	test_lstsize("liste vide (NULL)", (const char *[]){NULL}, 0);
	test_lstsize("1 noeud", (const char *[]){"a", NULL}, 1);
	test_lstsize("2 noeuds", (const char *[]){"a", "b", NULL}, 2);
	test_lstsize("5 noeuds", (const char *[]){"a", "b", "c", "d", "e", NULL}, 5);
	test_lstsize_big("10000 noeuds", 10000);

	section("lstlast");
	test_lstlast("liste vide (retourne NULL)", (const char *[]){NULL});
	test_lstlast("1 noeud (retourne ce noeud)", (const char *[]){"a", NULL});
	test_lstlast("2 noeuds", (const char *[]){"a", "b", NULL});
	test_lstlast("5 noeuds", (const char *[]){"a", "b", "c", "d", "e", NULL});

	section("lstadd_back");
	/*              nom                       liste de depart      ajouts (dans l'ordre)   liste attendue */
	test_add_back("liste vide + 1 ajout",     (const char *[]){NULL},
		(const char *[]){"a", NULL}, (const char *[]){"a", NULL});
	test_add_back("1 element + 1 ajout",      (const char *[]){"a", NULL},
		(const char *[]){"b", NULL}, (const char *[]){"a", "b", NULL});
	test_add_back("3 elements + 1 ajout",     (const char *[]){"a", "b", "c", NULL},
		(const char *[]){"d", NULL}, (const char *[]){"a", "b", "c", "d", NULL});
	test_add_back("liste vide + 3 ajouts",    (const char *[]){NULL},
		(const char *[]){"a", "b", "c", NULL}, (const char *[]){"a", "b", "c", NULL});
	test_add_back("1 element + 3 ajouts",     (const char *[]){"a", NULL},
		(const char *[]){"b", "c", "d", NULL}, (const char *[]){"a", "b", "c", "d", NULL});
	test_add_back_many("1000 ajouts a la fin", 1000);
	test_lst_mix();
#endif

	printf("\n%s (%d echec%s)\n",
		g_fail ? "Des tests ont echoue" : "Tous les tests passent",
		g_fail, g_fail > 1 ? "s" : "");
	return (g_fail != 0);
}