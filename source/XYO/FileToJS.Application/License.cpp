// File to JS
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToJS.Application/License.hpp>

namespace XYO::FileToJS::Application::License {

	std::string license() {
		return XYO::FileToJS::License::license();
	};

	std::string shortLicense() {
		return XYO::FileToJS::License::shortLicense();
	};

};
