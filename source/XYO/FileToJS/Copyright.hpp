// File to JS
// Copyright (c) 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOJS_COPYRIGHT_HPP
#define XYO_FILETOJS_COPYRIGHT_HPP

#ifndef XYO_FILETOJS_DEPENDENCY_HPP
#	include <XYO/FileToJS/Dependency.hpp>
#endif

namespace XYO::FileToJS::Copyright {
	XYO_FILETOJS_EXPORT std::string copyright();
	XYO_FILETOJS_EXPORT std::string publisher();
	XYO_FILETOJS_EXPORT std::string company();
	XYO_FILETOJS_EXPORT std::string contact();
};

#endif
