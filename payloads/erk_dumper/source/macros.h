#ifndef __MACROS_H__
#define __MACROS_H__

#define STRINGIFY(x) STRINGIFY_HELPER(x)
#define STRINGIFY_HELPER(x) #x

#define JOIN(a, b) JOIN_HELPER(a, b)
#define JOIN_HELPER(a, b) a##b

#define COUNT_OF(x) (sizeof(x) / sizeof(x[0]))

#define S2I_INTERNAL(s) (s "\0\0\0\0\0\0\0\0")
#define S2I(s) ( \
	(((uint64_t)S2I_INTERNAL(s)[0]) << 56) | \
	(((uint64_t)S2I_INTERNAL(s)[1]) << 48) | \
	(((uint64_t)S2I_INTERNAL(s)[2]) << 40) | \
	(((uint64_t)S2I_INTERNAL(s)[3]) << 32) | \
	(((uint64_t)S2I_INTERNAL(s)[4]) << 24) | \
	(((uint64_t)S2I_INTERNAL(s)[5]) << 16) | \
	(((uint64_t)S2I_INTERNAL(s)[6]) <<  8) | \
	(((uint64_t)S2I_INTERNAL(s)[7]) <<  0) \
)

#define FIELD_FIRST(s, i) ((S2I(s) >> 32) + (i))
#define FIELD(s, i) (S2I(s) + (i))

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

#endif