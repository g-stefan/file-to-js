// File to JS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_LICENSE_HPP
#define XYO_FILETOJS_LICENSE_HPP

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#	include <XYO/FileToJS/Dependency.hpp>
#endif

namespace XYO::FileToJS::License {
	XYO_FILETOJS_EXPORT const char *licenseHeader();
	XYO_FILETOJS_EXPORT const char *licenseBody();
	XYO_FILETOJS_EXPORT const char *shortLicense();
};

#endif
