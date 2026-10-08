# Getting started

## 1. Build and install

The library and the tool are built with
[fabricare](https://github.com/g-stefan/fabricare). `xyo-platform`,
`xyo-managed-memory`, `xyo-data-structures`, `xyo-multithreading`,
`xyo-encoding` and `xyo-system` must be installed to the SDK first. From
the repository root:

```bash
fabricare make       # build into output/
fabricare install    # copy output/{bin,include,lib} to ~/.fabricare/<platform>
fabricare clean      # remove output/ and temp/
```

After `install`, `file-to-js` is in `~/.fabricare/<platform>/bin`, which
is on the `PATH` of a fabricare build, so the scripts of other projects
can call it. It is also part of `xyo-sdk`.

Four projects are produced (`fabricare.json`):

| Project | Kind | Use it when |
|---------|------|-------------|
| `file-to-js` | DLL / shared library (`dll-or-lib`), the library | call `fileToJS` from your program |
| `file-to-js.static` | static library, static CRT | self-contained executables |
| `file-to-js.application.static` | static library with the command line tool, no `main` | embed `file-to-js` into another tool (fabricare does) |
| `file-to-js` | executable | the `file-to-js` command |

`dll-or-lib` builds a DLL / shared library on the normal platforms and a
static library on the `.static` ones (`win64-msvc-2026.static`, ...).

The DLL and the executable share the name `file-to-js`, so the library
keeps its version under the key `file-to-js.library` in `version.json`
(`"versionName"`); `file-to-js.static` reuses it and
`file-to-js.application.static` reuses the executable's (`"linkVersion"`).

## 2. Use the tool in a build

The usual case: a web or script project keeps an image, font or data file
in its source folder and wants it inside a `.js` file. In a fabricare
script (or any build script):

```js
runInPath("web", function() {
	exitIf(Shell.system("file-to-js --touch=bundle.js --file-in=logo.png --file-out=logo.js --name=logoPng"));
});
```

and in the page:

```html
<script src="logo.js"></script>
<script>
	var blob = new Blob([new Uint8Array(logoPng)], {type: "image/png"});
	document.getElementById("logo").src = URL.createObjectURL(blob);
</script>
```

`logo.js` is generated: list it in `.gitignore` or commit it, but never
edit it. `--touch=bundle.js` regenerates it only when `logo.png` is newer,
then touches `bundle.js` so whatever is built from it is rebuilt. See
[Command line](command-line.md).

## 3. Depend on the library from another fabricare project

In the consumer's `fabricare.json`:

```json
{
	"name": "my-packer",
	"make": "exe",
	"sourcePath": "XYO/MyPacker",
	"dependency": [
		"file-to-js"
	]
}
```

For the static variant use `"file-to-js.static"`; it exports
`XYO_FILETOJS_LIBRARY` to the consumer (`dependencyDefines`), which turns
`XYO_FILETOJS_EXPORT` into nothing. To embed the command line tool use
`"file-to-js.application.static"` (exports
`XYO_FILETOJS_APPLICATION_LIBRARY`, which leaves out `main`).
`xyo-system` and the layers below come in as transitive dependencies.

## 4. Include

```cpp
#include <XYO/FileToJS.hpp>               // the library
#include <XYO/FileToJS.Application.hpp>   // the library + the command line tool class
```

Namespace `XYO::FileToJS` contains `using namespace XYO::System;`, so
`String`, `Shell::`, `IApplication`, ... are visible inside it.

Call the function qualified, `XYO::FileToJS::fileToJS(...)`. The metadata
namespaces exist in every XYO layer; here the library version is
`XYO::FileToJS::Version::version()` and the tool's is
`XYO::FileToJS::Application::Version::version()`.

## 5. First program

A tool that embeds every `.png` of a folder into one generated script,
one `var` per image:

```cpp
#include <XYO/FileToJS.hpp>

using namespace XYO::System;

class Application : public virtual IApplication {
		XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Application);

	public:
		inline Application(){};

		int main(int cmdN, char *cmdS[]);
};

int Application::main(int cmdN, char *cmdS[]) {
	TDynamicArray<String> fileList;
	Shell::getFileList("images/*.png", fileList);

	String output = "images.js";
	Shell::removeFile(output);

	for (size_t k = 0; k < fileList.length(); ++k) {
		// images/logo.png -> image_logo
		String name = String("image_") + Shell::getFileBasename(Shell::getFileName(fileList[k]));
		// append = true: every call adds one more var to the same file
		if (!XYO::FileToJS::fileToJS(name, fileList[k], output, true)) {
			printf("* Error: %s\n", fileList[k].value());
			return 1;
		};
	};
	return 0;
};

XYO_APPLICATION_MAIN(Application);
```

`XYO_APPLICATION_MAIN` comes from `xyo-system`: it initializes the managed
memory registry and calls `Application::main`. The `var` name must be a
valid JavaScript identifier: a file name such as `my-logo.png` needs its
`-` replaced first.

## 6. Conventions

- **`bool` means success.** `fileToJS` returns `false` when the input can
  not be read or the output can not be written; there are no exceptions
  and no message. The tool returns exit code `1`, also without a message
  (see [Command line](command-line.md#exit-codes)).
- **Paths are used as given**, relative to the current directory. The
  output folder must exist.
- **The output is overwritten** unless `append` / `--append` is used.
- **Names are not checked.** `--name` / `variableName` is written as is: it
  must be a valid, unique JavaScript identifier.
- **Nothing is cached, no locking.** Do not write the same output file from
  two processes at the same time.

## 7. Building without fabricare

The tool is one translation unit plus the XYO layers:

1. Put `source/` of `xyo-platform`, `xyo-managed-memory`,
   `xyo-data-structures`, `xyo-multithreading`, `xyo-encoding`,
   `xyo-system` and `file-to-js` on the include path, with the
   configuration headers of the layers that need them (see their
   documentation).
2. Define `XYO_PLATFORM_LIBRARY`, `XYO_MANAGEDMEMORY_LIBRARY`,
   `XYO_DATASTRUCTURES_LIBRARY`, `XYO_MULTITHREADING_LIBRARY`,
   `XYO_ENCODING_LIBRARY`, `XYO_SYSTEM_LIBRARY` and `XYO_FILETOJS_LIBRARY`
   (static, no DLL export).
3. Compile `FileToJS.Application.Amalgam.cpp` with
   `Platform.Amalgam.cpp`, `ManagedMemory.Amalgam.cpp`,
   `DataStructures.Amalgam.cpp`, `Multithreading.Amalgam.cpp`,
   `Encoding.Amalgam.cpp` and `System.Amalgam.cpp` as C++17.

For the library only, compile `FileToJS.Amalgam.cpp` instead of
`FileToJS.Application.Amalgam.cpp`.
