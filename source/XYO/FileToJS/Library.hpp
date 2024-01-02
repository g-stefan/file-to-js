// File to JS
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_LIBRARY_HPP
#define XYO_FILETOJS_LIBRARY_HPP

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#	include <XYO/FileToJS/Dependency.hpp>
#endif

namespace XYO::FileToJS {

	XYO_FILETOJS_EXPORT bool fileToJS(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append);

};

#endif
