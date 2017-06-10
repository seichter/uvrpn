#ifndef UVRPN_EXPORTS_HPP
#define UVRPN_EXPORTS_HPP

#if defined(_WIN32)
#define UVRPN_PINVOKE_API __declspec(dllexport)
#elif defined(__clang__) || defined(__GCC)
#define UVRPN_PINVOKE_API __attribute__ ((visibility("default")))
#else
#define UVRPN_PINVOKE_API
#endif

#define UVRPN_PINVOKE_EXPORT extern "C" UVRPN_PINVOKE_API



#endif
