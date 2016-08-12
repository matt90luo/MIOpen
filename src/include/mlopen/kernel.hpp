#ifndef GUARD_MLOPEN_KERNEL_HPP
#define GUARD_MLOPEN_KERNEL_HPP

#if MLOPEN_BACKEND_OPENCL
#include <mlopen/oclkernel.hpp>

namespace mlopen {
using KernelInvoke = OCLKernelInvoke;
}

#elif MLOPEN_BACKEND_HIP

#endif


#endif
