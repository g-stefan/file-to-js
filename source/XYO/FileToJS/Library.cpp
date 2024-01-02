// File to JS
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToJS/Library.hpp>

namespace XYO::FileToJS {

	bool fileToJS(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append) {
		FILE *input;
		FILE *output;
		uint8_t ch;
		int index;
		int first;

		input = fopen(fileNameIn, "rb");
		if (input != nullptr) {
			output = fopen(fileNameOut, append ? "ab" : "wb");
			if (output != nullptr) {
				fprintf(output, "var %s=[", stringName);

				ch = 0x00;
				index = 0;
				first = 1;
				while (fread(&ch, 1, 1, input) == 1) {

					if (first) {
						first = 0;
						fprintf(output, "\n\t");
					} else {
						fprintf(output, ",");
						if (index == 0) {
							fprintf(output, "\n\t");
						};
					};

					fprintf(output, "0x%02X", ch);

					++index;
					index %= 32;

					ch = 0;
				};

				if (index == 0) {
					fprintf(output, "\n\t");
				};

				fprintf(output, "\n];\n");
				fclose(output);
				fclose(input);
				return true;
			};
			fclose(input);
		};
		return false;
	};

};
