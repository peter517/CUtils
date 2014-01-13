#include "stdafx.h"
#include "webrtc/system_wrappers/interface/cpu_info.h"

#if defined(_WIN32)
#include <Windows.h>
#elif defined(WEBRTC_MAC)
#include <sys/sysctl.h>
#include <sys/types.h>
#else // defined(WEBRTC_LINUX) or defined(WEBRTC_ANDROID)
#include <unistd.h>
#endif

namespace webrtc {

uint32_t CpuInfo::number_of_cores_ = 0;

uint32_t CpuInfo::DetectNumberOfCores() {
  if (!number_of_cores_) {
#if defined(_WIN32)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    number_of_cores_ = static_cast<uint32_t>(si.dwNumberOfProcessors);
  

#elif defined(WEBRTC_LINUX) || defined(WEBRTC_ANDROID)
    number_of_cores_ = static_cast<uint32_t>(sysconf(_SC_NPROCESSORS_ONLN));
   

#elif defined(WEBRTC_MAC)
    int name[] = {CTL_HW, HW_AVAILCPU};
    int ncpu;
    size_t size = sizeof(ncpu);
    if (0 == sysctl(name, 2, &ncpu, &size, NULL, 0)) {
      number_of_cores_ = static_cast<uint32_t>(ncpu);
      
    } else {
      
      number_of_cores_ = 1;
    }
#else
   
    number_of_cores_ = 1;
#endif
  }
  return number_of_cores_;
}

}  // namespace webrtc
