dnl this defines the LIBTGA_DEBUG macro which adds the --enable-debug
dnl option to ./configure
AC_DEFUN(LIBTGA_DEBUG, [AC_ARG_ENABLE(debug,
   AC_HELP_STRING([--enable-debug], [generate debug symbols (default=no)]),
		  ac_cv_enable_debug=$withval, ac_cv_enable_debug=no)])

