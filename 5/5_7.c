#include "../lib/tpli_hdr.h"
#include <sys/uio.h>
typedef struct iovec {
  void *iov_base;
  size_t iov_len;
}

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt){

}

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt){

}
