---
name: file-to-js
description: >-
  How to use file-to-js, the XYO tool and C++ library (namespace
  XYO::FileToJS) on top of xyo-system that converts any file into
  JavaScript source to embed it in a script: the file-to-js command line
  (--name, --file-in, --file-out, --append, --touch, @response files, exit
  codes, silent failures); the output form var name=[0xHH,...]; (32 bytes
  per line, an array of numbers, not a string) and how to turn it back
  into bytes or text in JavaScript (Uint8Array, Blob, TextDecoder,
  Buffer.from); the function fileToJS; embedding the tool through
  file-to-js.application.static and XYO::FileToJS::Application::Application
  (fabricare's fileToJS(...)). Use when writing or reviewing code that
  includes <XYO/FileToJS.hpp> or <XYO/FileToJS.Application.hpp>, depends
  on "file-to-js" in fabricare.json, calls file-to-js or fileToJS in a
  build script, loads a generated .js file of byte arrays, wants to embed
  an image / font / binary / text file in JavaScript, or when working
  inside the file-to-js repository.
---

# file-to-js

Converts a file into JavaScript source, `var name=[0xHH,...];`, so it ships
inside a script. Two faces:

- the **`file-to-js` command line tool**, run from a build script;
- the **C++ library** `XYO::FileToJS`: `fileToJS`, plus the tool as a
  class.

Built on `xyo-system` (see the `xyo-system` skill and the layers below it:
their rules apply). Sibling of `file-to-cs` (C/C++ source) and
`file-to-rc`, with the same command line conventions.

Full documentation: `docs/` in the file-to-js repository
(`X:\Storage\XYO\Gitea\CPP\file-to-js\docs` on this machine): README,
getting-started, **command-line**, **output-format**, library, reference.
The whole implementation is `source/XYO/FileToJS/Library.cpp` and
`source/XYO/FileToJS.Application/Application.cpp`.

## Usage at a glance

| Need | Command line | C++ |
|------|--------------|-----|
| Embed a file | `file-to-js --name=n --file-in=in --file-out=out.js` | `XYO::FileToJS::fileToJS(n, in, out, false)` |
| Several `var`s in one file | first call plain, the rest `--append` | `append = true` |
| Regenerate only if input newer | `--touch=dependent` | `Shell::compareLastWriteTime(in, out) > 0` |

Output (exact, `\n` line ends):

```js
var n=[
	0x70,0x72,0x69,...   (32 per line, tab indented, upper case hex)
];
```

`n.length` is the file size. An empty file, or a size multiple of 32,
adds a line holding only a tab — valid JS, empty array for an empty file.

## Using the output in JavaScript

```js
var bytes = new Uint8Array(n);                              // bytes
var url = URL.createObjectURL(new Blob([bytes], {type: "image/png"}));
var text = new TextDecoder().decode(new Uint8Array(n));      // UTF-8 text
var buf = Buffer.from(n);                                    // Node.js
```

`String.fromCharCode.apply(null, n)` is only right for ASCII / Latin-1.
`--name` is only the variable name; the value is always an **array of
numbers**, never a string.

## Hard rules

1. **Required options**: `--name`, `--file-in`, `--file-out`. Missing →
   usage printed, exit `1`. Empty value (`--name=`) → `Error: ... is
   empty`, exit `1`.
2. **Failures are silent**: input missing, output folder missing, no
   access → exit `1` with **no message** (the library returns `false`).
   Always `exitIf(...)` / check the result. The output folder is never
   created.
3. **`--touch=f`**: if the output exists and the input is **not newer**,
   exit `0` and do nothing (not even touch). This includes a **missing
   input** with an existing output — no error. Otherwise write, then touch
   `f` only if it exists.
4. **`--append` accumulates**: every run adds again (duplicate `var`s are
   legal JS, last wins, file grows). Start each sequence with one call
   without `--append`. Do not mix `--append` with `--touch` on a shared
   output (later inputs are compared to the already written file and
   skipped).
5. **Names are not checked**: `--name` must be a valid JavaScript
   identifier, not a reserved word (`my-logo` → syntax error at load;
   sanitize).
6. **`var` is global** in a classic `<script>`: pick names that do not
   clash. As an ES module nothing is exported — append `export default n;`
   (or `module.exports = n;`) yourself.
7. **Size**: about 5 bytes of source per input byte; keep embedded files
   small.
8. **Generated `.js` files** are outputs: never edit them, edit the input
   and rebuild.
9. **`@file`** response files are expanded first (split like a command
   line, quotes group words); a missing one → `Error: file not found -
   file`, exit `1`. Unknown options and non `--` arguments are ignored.
10. **Inside fabricare** the tool is built in:
    `exitIf(fileToJS("--file-in=logo.png", "--file-out=logo.js", "--name=logoPng"));`
    (one argument per parameter, returns the exit code). Older fabricare
    builds lack it; `Shell.system("file-to-js ...")` works everywhere.

## Depend on it

```json
"dependency": [ "file-to-js" ]                    // DLL (static lib on .static platforms)
"dependency": [ "file-to-js.static" ]             // static, defines XYO_FILETOJS_LIBRARY
"dependency": [ "file-to-js.application.static" ] // embed the tool, no main
```

```cpp
#include <XYO/FileToJS.hpp>

if (!XYO::FileToJS::fileToJS("logoPng", "logo.png", "logo.js", false)) {
	printf("* Error: logo.png\n");
	return 1;
};
```

Embedded tool: build a plain `char *` array (`cmdS[0]` = program name,
`TDynamicArray` is not contiguous) and call
`XYO::FileToJS::Application::Application application;
application.main(cmdN, cmdS)` — it returns the exit code and prints to
stdout.

Metadata: `XYO::FileToJS::Version::version()` from
`<XYO/FileToJS/Version.hpp>` (not included by `<XYO/FileToJS.hpp>`); the
tool's is `XYO::FileToJS::Application::Version::version()`.

## Working inside this repository

- Four projects in `fabricare.json`: `file-to-js` (`dll-or-lib`, version
  key `file-to-js.library`), `file-to-js.static`,
  `file-to-js.application.static` (linked into fabricare), `file-to-js`
  (exe).
- fabricare bootstraps with this tool compiled in
  (`build/fabricare.compile.json` in the fabricare repository): keep
  `FileToJS.Application.Amalgam.cpp` self-contained.
- `fabricare make`, `fabricare install`. There is no test project; try
  changes with the built `output/bin/file-to-js` on sample inputs and load
  the result with `node`.
- Keep the docs in `docs/` and this skill in step with `Library.hpp` /
  `Application.cpp` when behavior changes.
- Licensing follows REUSE: `source/`, `docs/` and `README.md` are MIT
  (source files also carry SPDX headers); build scripts, config,
  `version.json` and `.claude/` are Unlicense. Every new top level file or
  folder needs a `Files:` entry in `.reuse/dep5` (check with `reuse lint`).
