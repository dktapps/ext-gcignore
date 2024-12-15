/* gcignore extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_gcignore.h"
#include "gcignore_arginfo.h"
#include "Zend/zend_gc.h"

zend_object_handlers gcignore_object_handlers;

#define ONE_OBJECT_PARAM() \
	zend_object *object; \
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1) \
		Z_PARAM_OBJ(object) \
	ZEND_PARSE_PARAMETERS_END();

PHP_FUNCTION(gc_ignore) {
	ONE_OBJECT_PARAM();

	if (object->handlers == &gcignore_object_handlers) {
		RETURN_TRUE;
	}
	if (object->handlers == zend_get_std_object_handlers()) {
		object->handlers = &gcignore_object_handlers;
		RETURN_TRUE;
	}

	php_error_docref(NULL, E_WARNING, "Cannot ignore object of class %s because it has custom object handlers (PHP or extension provided)", ZSTR_VAL(object->ce->name));
	RETURN_FALSE;
}

PHP_FUNCTION(gc_unignore) {
	ONE_OBJECT_PARAM();

	if (object->handlers == &gcignore_object_handlers) {
		object->handlers = zend_get_std_object_handlers();
	}
}

PHP_FUNCTION(gc_is_ignored) {
	ONE_OBJECT_PARAM();
	RETURN_BOOL(object->handlers == &gcignore_object_handlers);
}

HashTable* gcignore_fake_gc_handler(zend_object* object, zval** table, int* n) {
	*n = 0;
	*table = NULL;
	return NULL;
}

PHP_MINIT_FUNCTION(gcignore) {
	memcpy(&gcignore_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	gcignore_object_handlers.get_gc = gcignore_fake_gc_handler;
	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(gcignore) {
#if defined(ZTS) && defined(COMPILE_DL_GCIGNORE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(gcignore)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gcignore support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ gcignore_module_entry */
zend_module_entry gcignore_module_entry = {
	STANDARD_MODULE_HEADER,
	"gcignore",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(gcignore),			/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(gcignore),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(gcignore),			/* PHP_MINFO - Module info */
	PHP_GCIGNORE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GCIGNORE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(gcignore)
#endif
