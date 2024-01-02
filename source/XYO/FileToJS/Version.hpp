// File to JS
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_VERSION_HPP
#define XYO_FILETOJS_VERSION_HPP

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#	include <XYO/FileToJS/Dependency.hpp>
#endif

namespace XYO::FileToJS::Version {
	XYO_FILETOJS_EXPORT const char *version();
	XYO_FILETOJS_EXPORT const char *build();
	XYO_FILETOJS_EXPORT const char *versionWithBuild();
	XYO_FILETOJS_EXPORT const char *datetime();
};

#endif
