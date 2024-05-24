#ifndef DBG_ASSERT_H
#define DBG_ASSERT_H

#if !defined(__cplusplus) && !defined(bool) && !defined(SP_BOOL_TYPE)
	typedef enum bool { false = 0, true = !false } bool;
	#define SP_BOOL_TYPE
#endif

#ifdef DEBUG
	#define DBG_ASSERT(expr) \
		(void)((expr) || (__dbg_assert(#expr, __FILE__, __LINE__, __func__), 0) )

	#define DBG_LOG(msg, level) \
		__dbg_log(msg, __FILE__, __LINE__, __func__, level)
#else
	#define DBG_ASSERT(expr) (void)0
	#define DBG_LOG(msg, level) (void)0
#endif


#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
	LOG,
	WARNING,
	ERROR
} errorL_t;

void __dbg_assert(const char *expr, const char *file, int line, const char *func);
void __dbg_log(const char *msg, const char *file, int line, const char *func, errorL_t level);

#if defined(__cplusplus)
}
#endif

#endif // DBG_ASSERT_H
