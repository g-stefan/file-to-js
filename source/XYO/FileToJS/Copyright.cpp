// File to JS
// Copyright (c) 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToJS/Copyright.hpp>
#include <XYO/FileToJS/Copyright.rh>

namespace XYO::FileToJS::Copyright {

	static const char *copyright_ = XYO_FILETOJS_COPYRIGHT;
	static const char *publisher_ = XYO_FILETOJS_PUBLISHER;
	static const char *company_ = XYO_FILETOJS_COMPANY;
	static const char *contact_ = XYO_FILETOJS_CONTACT;

	std::string copyright() {
		return copyright_;
	};

	std::string publisher() {
		return publisher_;
	};

	std::string company() {
		return company_;
	};

	std::string contact() {
		return contact_;
	};

};
