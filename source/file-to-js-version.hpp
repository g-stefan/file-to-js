//
// File to JS
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef FILE_TO_JS_VERSION_HPP
#define FILE_TO_JS_VERSION_HPP

#define FILE_TO_JS_VERSION_ABCD 1,14,0,33
#define FILE_TO_JS_VERSION_STR "1.14.0"
#define FILE_TO_JS_VERSION_STR_BUILD "33"
#define FILE_TO_JS_VERSION_STR_DATETIME "2022-04-04 01:44:47"

#ifndef XYO_RC

namespace FileToJS {
	namespace Version {
		const char *version();
		const char *build();
		const char *versionWithBuild();
		const char *datetime();
	};
};

#endif
#endif
