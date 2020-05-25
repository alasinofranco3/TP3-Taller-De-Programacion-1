#include "commonOSError.h"

OSError::OSError(const char *format, ...) noexcept {
	int _errno = errno;

	va_list args;
	va_start(args, format);
	int s = vsnprintf(errorMessage, BUF_LEN, format, args);
	va_end(args);

	strncpy(errorMessage + s, strerror(_errno), BUF_LEN - s);
	errorMessage[BUF_LEN - 1] = 0;

}

const char* OSError::what() const noexcept {
	return errorMessage;
}

OSError::~OSError() noexcept {}
