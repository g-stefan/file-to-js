# Library

```cpp
#include <XYO/FileToJS.hpp>

namespace XYO::FileToJS {
	bool fileToJS(const char *variableName, const char *fileNameIn, const char *fileNameOut, bool append);
};
```

The parameters are `const char *`; a `String` converts to it implicitly.
It returns `true` on success and `false` on any failure, prints nothing
and throws nothing. The exact output is in
[Output format](output-format.md).

## fileToJS

```cpp
// var logoPng=[...];
XYO::FileToJS::fileToJS("logoPng", "logo.png", "logo.js", false);

// var fontBold=[...]; added after what logo.js already holds
XYO::FileToJS::fileToJS("fontBold", "bold.woff2", "logo.js", true);
```

| Parameter | Meaning |
|-----------|---------|
| `variableName` | name of the `var`, written as given (must be a valid JavaScript identifier) |
| `fileNameIn` | input, read as bytes |
| `fileNameOut` | output; its folder must exist |
| `append` | `false`: replace the output; `true`: add to its end (create it if missing) |

Returns `false` if the input can not be opened (the output is then not
touched) or the output can not be opened. Write errors after that (a full
disk) are not detected. It works with C `FILE *` and reads one byte at a
time, so files of any size are converted without loading them into
memory.

This is the function behind the command line tool.

## Regenerate only when changed

The library function always writes. To do what the tool's `--touch` does:

```cpp
if (!Shell::fileExists(out) || Shell::compareLastWriteTime(in, out) > 0) {
	if (!XYO::FileToJS::fileToJS(name, in, out, false)) {
		return false;
	};
	Shell::touchIfExists(dependent);
};
```

## Embedding the command line tool

Depend on `file-to-js.application.static` and call the tool class with an
argument vector:

```cpp
#include <XYO/FileToJS.Application.hpp>

int runFileToJS(TDynamicArray<String> &arguments) {
	int cmdN = (int)arguments.length() + 1;
	char **cmdS = new char *[cmdN];
	cmdS[0] = const_cast<char *>("file-to-js");
	for (int k = 1; k < cmdN; ++k) {
		cmdS[k] = const_cast<char *>(arguments[k - 1].value());
	};
	int retV;
	{
		XYO::FileToJS::Application::Application application;
		retV = application.main(cmdN, cmdS);
	};
	delete[] cmdS;
	return retV;
};
```

`cmdS[0]` is the program name and is skipped. `TDynamicArray` is not
contiguous memory, so build a plain `char *` array. The tool prints to
`stdout` and returns the exit code; it never calls `exit`. The options are
in [Command line](command-line.md).

## Library metadata

As in every XYO library (the headers are not included by
`<XYO/FileToJS.hpp>`):

```cpp
#include <XYO/FileToJS/Version.hpp>
#include <XYO/FileToJS/Copyright.hpp>
#include <XYO/FileToJS/License.hpp>

XYO::FileToJS::Version::version();            // "5.9.0"
XYO::FileToJS::Version::build();
XYO::FileToJS::Version::versionWithBuild();
XYO::FileToJS::Version::datetime();
XYO::FileToJS::Copyright::copyright();
XYO::FileToJS::License::license();            // std::string
```

The tool has the same set in `XYO::FileToJS::Application::Version`,
`Copyright` and `License`.
