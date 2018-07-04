/**
 * uvrpn - a minimal wrapper for VRPN in Unity
 *
 * Copyright (c) 2013-2018 Hartmut Seichter
 *
 * This file is part of uvrpn and licensed under the terms of the MIT License
 *
 */

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
