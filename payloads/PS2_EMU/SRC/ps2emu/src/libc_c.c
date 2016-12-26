#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	
	return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char uc1, uc2;
	/* Nothing to compare?  Return zero.  */
	if (n == 0)
		return 0;
	/* Loop, comparing bytes.  */
	while (n-- > 0 && *s1 == *s2) {
		/* If we've run out of bytes or hit a null, return zero
		since we already know *s1 == *s2.  */
		if (n == 0 || *s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	uc1 = (*(unsigned char *) s1);
	uc2 = (*(unsigned char *) s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

int memcmp(const void *s1, const void *s2, size_t n)
 {
	 const unsigned char *p1 = s1;
	 const unsigned char *p2 = s2;
	 
	 for (int i = 0; i < n; i++)
	 {
		 if (p1[i] != p2[i])
		 {
			 return (p1[i] < p2[i]) ? -1 : 1;
		 }
	 }
	 
	 return 0;
}

char *strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return 0;
	
	return (char *)s;
}
 
char *strstr(const char *haystack, const char *needle)
{
	size_t needlelen;
	/* Check for the null needle case.  */
	if (*needle == '\0')
		return (char *) haystack;
     
	needlelen = strlen(needle);
	for (; (haystack = strchr(haystack, *needle)) != NULL; haystack++)
		if (strncmp(haystack, needle, needlelen) == 0)
			return (char *) haystack;
	
	return NULL;
}

