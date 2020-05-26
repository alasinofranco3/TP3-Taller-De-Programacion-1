#ifndef COMMONOSERROR_H
#define COMMONOSERROR_H

#include <typeinfo>
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#define BUF_LEN 256

class OSError : public std::exception {
	private:
		char errorMessage [BUF_LEN];
	public:
		explicit OSError(const char * format, ...) noexcept;
		virtual const char *what() const noexcept;
		virtual ~OSError() noexcept;
};

#endif
