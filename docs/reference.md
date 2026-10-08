# API reference

## Headers

| Header | Contents |
|--------|----------|
| `<XYO/FileToJS.hpp>` | the library: `Dependency.hpp` + `Library.hpp` |
| `<XYO/FileToJS/Copyright.hpp>`, `License.hpp`, `Version.hpp` | library metadata (not included by `FileToJS.hpp`) |
| `<XYO/FileToJS.Application.hpp>` | the library + `XYO::FileToJS::Application::Application` |

## Macros

| Macro | Meaning |
|-------|---------|
| `XYO_FILETOJS_EXPORT` | `dllexport` / `dllimport` / nothing |
| `XYO_FILETOJS_DLL_INTERNAL` | building the DLL (exports); set from `FILE_TO_JS_DLL_INTERNAL`, which xyo-cc defines from the project name |
| `XYO_FILETOJS_INTERNAL` | set from `FILE_TO_JS_INTERNAL`; not used by the sources |
| `XYO_FILETOJS_LIBRARY` | static use, `XYO_FILETOJS_EXPORT` is empty (set by `file-to-js.static`) |
| `XYO_FILETOJS_APPLICATION_LIBRARY` | build the tool without `main` (set by `file-to-js.application.static`) |

## namespace XYO::FileToJS

`using namespace XYO::System;`

| Function | Writes | Returns |
|----------|--------|---------|
| `bool fileToJS(const char *variableName, const char *fileNameIn, const char *fileNameOut, bool append)` | `var name=[\n\t0xHH,...\n];\n`, 32 bytes per line; appends if `append` | `false` if input or output can not be opened |

Details: [Output format](output-format.md).

## namespace XYO::FileToJS::Version / Copyright / License

```cpp
const char *XYO::FileToJS::Version::version();
const char *XYO::FileToJS::Version::build();
const char *XYO::FileToJS::Version::versionWithBuild();
const char *XYO::FileToJS::Version::datetime();

const char *XYO::FileToJS::Copyright::copyright();
const char *XYO::FileToJS::Copyright::publisher();
const char *XYO::FileToJS::Copyright::company();
const char *XYO::FileToJS::Copyright::contact();

std::string XYO::FileToJS::License::license();
std::string XYO::FileToJS::License::shortLicense();
```

The same functions exist for the tool in
`XYO::FileToJS::Application::Version`, `Copyright` and `License`.

## class XYO::FileToJS::Application::Application

```cpp
class Application : public virtual IApplication {
	public:
		void showUsage();
		void showLicense();
		void showVersion();
		int main(int cmdN, char *cmdS[]);
		static void initMemory();
};
```

The `file-to-js` command line tool; `main` returns the exit code. See
[Command line](command-line.md).

## Command line options

`--help`, `--usage`, `--license`, `--version`, `--name=name`,
`--file-in=file`, `--file-out=file`, `--append`, `--touch=file`, `@file`.

| Exit code | Meaning |
|-----------|---------|
| `0` | written, up to date (`--touch`), or an info option |
| `1` | missing / empty option, response file not found, read or write failed (no message) |

## fabricare projects

| Project | Kind | Defines exported to the consumer |
|---------|------|----------------------------------|
| `file-to-js` | DLL / shared library (`dll-or-lib`: static library on a `.static` platform), version key `file-to-js.library` | |
| `file-to-js.static` | static library, static CRT | `XYO_FILETOJS_LIBRARY` |
| `file-to-js.application.static` | static library, tool without `main` | `XYO_FILETOJS_APPLICATION_LIBRARY` |
| `file-to-js` | executable | |
