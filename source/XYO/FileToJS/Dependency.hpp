// File to JS
// Copyright (c) 2020-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#define XYO_FILETOJS_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

// -- Export

#ifdef FILE_TO_JS_INTERNAL
#	ifndef XYO_FILETOJS_INTERNAL
#		define XYO_FILETOJS_INTERNAL
#	endif
#endif

#ifdef FILE_TO_JS_DLL_INTERNAL
#	ifndef XYO_FILETOJS_DLL_INTERNAL
#		define XYO_FILETOJS_DLL_INTERNAL
#	endif
#endif

#ifdef XYO_FILETOJS_DLL_INTERNAL
#	define XYO_FILETOJS_EXPORT XYO_PLATFORM_LIBRARY_EXPORT
#else
#	define XYO_FILETOJS_EXPORT XYO_PLATFORM_LIBRARY_IMPORT
#endif
#ifdef XYO_FILETOJS_LIBRARY
#	undef XYO_FILETOJS_EXPORT
#	define XYO_FILETOJS_EXPORT
#endif

namespace XYO::FileToJS {
	using namespace XYO::System;
};

#endif
