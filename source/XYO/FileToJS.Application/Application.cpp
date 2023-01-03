// File to JS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToJS.hpp>
#include <XYO/FileToJS.Application/Application.hpp>
#include <XYO/FileToJS.Application/Copyright.hpp>
#include <XYO/FileToJS.Application/License.hpp>
#include <XYO/FileToJS.Application/Version.hpp>

namespace XYO::FileToJS::Application {

	void Application::showUsage() {
		printf("FileToJS - Convert file to JS source\n");
		showVersion();
		printf("%s\n\n", FileToJS::Application::Copyright::copyright());

		printf("%s",
		       "options:\n"
		       "    --usage             this info\n"
		       "    --license           show license\n"
		       "    --version           show version\n"
		       "    --name=name         string variable name\n"
		       "    --file-in=file      input file\n"
		       "    --file-out=file     output file\n"
		       "    --touch=file        touch file if changed input file\n"
		       "    --append            append content\n");
		printf("\n");
	};

	void Application::showLicense() {
		printf("%s", FileToJS::Application::License::license());
	};

	void Application::showVersion() {
		printf("version %s build %s [%s]\n", FileToJS::Application::Version::version(), FileToJS::Application::Version::build(), FileToJS::Application::Version::datetime());
	};

	void Application::initMemory() {
		String::initMemory();
		TDynamicArray<String>::initMemory();
	};

	int Application::main(int cmdN, char *cmdS[]) {
		int i;
		String opt;
		size_t optIndex;
		String optValue;
		TDynamicArray<String> cmdLine;

		String stringName;
		String fileNameIn;
		String fileNameOut;
		bool append = false;
		bool isTouch = false;
		String touchFileName;

		for (i = 1; i < cmdN; ++i) {
			if (StringCore::beginWith(cmdS[i], "@")) {
				String content;
				if (Shell::fileGetContents(&cmdS[i][1], content)) {
					int cmdNX;
					char **cmdSX;
					int m;
					Shell::mainArgsSet(content, cmdNX, cmdSX);
					for (m = 0; m < cmdNX; ++m) {
						cmdLine.push(cmdSX[m]);
					};
					Shell::mainArgsDelete(cmdNX, cmdSX);
					continue;
				};
				printf("Error: file not found - %s\n", &cmdS[i][1]);
				return 1;
			};
			cmdLine.push(cmdS[i]);
		};

		for (i = 0; i < cmdLine.length(); ++i) {
			if (StringCore::beginWith(cmdLine[i], "--")) {
				opt = cmdLine[i].index(2);
				optValue = "";
				if (String::indexOf(opt, "=", 0, optIndex)) {
					optValue = String::substring(opt, optIndex + 1);
					opt = String::substring(opt, 0, optIndex);
				};
				if (opt == "usage") {
					showUsage();
					return 0;
				};
				if (opt == "license") {
					showLicense();
					return 0;
				};
				if (opt == "version") {
					showVersion();
					return 0;
				};
				if (opt == "name") {
					stringName = optValue;
					if (stringName.length() == 0) {
						printf("Error: name is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "file-in") {
					fileNameIn = optValue;
					if (fileNameIn.length() == 0) {
						printf("Error: file-in is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "file-out") {
					fileNameOut = optValue;
					if (fileNameOut.length() == 0) {
						printf("Error: file-out is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "touch") {
					isTouch = true;
					touchFileName = optValue;
					if (touchFileName.length() == 0) {
						printf("Error: touch filename is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "append") {
					append = true;
					continue;
				};
				continue;
			};
		};

		// ---

		if ((stringName.length() == 0) ||
		    fileNameIn.length() == 0 ||
		    fileNameOut.length() == 0) {
			showUsage();
			return 1;
		};

		if (isTouch) {
			if (Shell::fileExists(fileNameOut)) {
				if (Shell::compareLastWriteTime(fileNameIn, fileNameOut) <= 0) {
					return 0;
				};			
			};
		};

		if (!fileToJS(stringName, fileNameIn, fileNameOut, append)) {
			return 1;
		};

		if (isTouch) {
			Shell::touchIfExists(touchFileName);
		};

		return 0;
	};
};

#ifndef XYO_FILETOJS_APPLICATION_LIBRARY
XYO_APPLICATION_MAIN(XYO::FileToJS::Application::Application);
#endif