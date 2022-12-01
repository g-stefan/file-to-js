// File to JS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#define XYO_FILETOJS_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

// -- Export

#ifndef XYO_FILETOJS_INTERNAL
#	ifdef FILE_TO_JS_LIBRARY_INTERNAL
#		define XYO_FILETOJS_INTERNAL
#	endif
#endif

#ifdef XYO_FILETOJS_INTERNAL
#	define XYO_FILETOJS_EXPORT XYO_LIBRARY_EXPORT
#else
#	define XYO_FILETOJS_EXPORT XYO_LIBRARY_IMPORT
#endif

namespace XYO::FileToJS {
	using namespace XYO::System;
};

#endif
