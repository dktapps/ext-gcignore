/* gcignore extension for PHP */

#ifndef PHP_GCIGNORE_H
# define PHP_GCIGNORE_H

extern zend_module_entry gcignore_module_entry;
# define phpext_gcignore_ptr &gcignore_module_entry

# define PHP_GCIGNORE_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_GCIGNORE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_GCIGNORE_H */
