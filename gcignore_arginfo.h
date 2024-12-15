/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 623674ce234292a38d2ec5dfadb3b3a758923d6d */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gc_ignore, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, object, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gc_unignore, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, object, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

#define arginfo_gc_is_ignored arginfo_gc_ignore


ZEND_FUNCTION(gc_ignore);
ZEND_FUNCTION(gc_unignore);
ZEND_FUNCTION(gc_is_ignored);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(gc_ignore, arginfo_gc_ignore)
	ZEND_FE(gc_unignore, arginfo_gc_unignore)
	ZEND_FE(gc_is_ignored, arginfo_gc_is_ignored)
	ZEND_FE_END
};
