// File to JS
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToJS.Application/Copyright.hpp>
#include <XYO/FileToJS.Application/Copyright.rh>

namespace XYO::FileToJS::Application::Copyright {

	static const char *copyright_ = XYO_FILETOJS_APPLICATION_COPYRIGHT;
	static const char *publisher_ = XYO_FILETOJS_APPLICATION_PUBLISHER;
	static const char *company_ = XYO_FILETOJS_APPLICATION_COMPANY;
	static const char *contact_ = XYO_FILETOJS_APPLICATION_CONTACT;

	const char *copyright() {
		return copyright_;
	};

	const char *publisher() {
		return publisher_;
	};

	const char *company() {
		return company_;
	};

	const char *contact() {
		return contact_;
	};

};
