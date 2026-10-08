# File to JS Source

Utility and C++ library to convert a file to JS source
- Embeds any file in a script as `var name=[0x89,0x50,...];`, an array of
byte values to turn into a `Uint8Array`, a `Blob` or text.
- `file-to-js` command line tool: `--name`, `--file-in`, `--file-out`,
`--append` (several `var`s in one file), `--touch` (regenerate only when the
input changed, then touch a dependent file), `@file` response files.
- Library `XYO::FileToJS`: `fileToJS`, and the tool as a class to embed in
other programs.

Built on `xyo-system`; part of `xyo-sdk` and built into fabricare as
`fileToJS(...)`.

## Documentation

- [Overview](docs/README.md) - purpose and design
- [Getting started](docs/getting-started.md) - build, depend on it, use it in a build, first program
- [Command line](docs/command-line.md) - `file-to-js` options, `--touch`, `--append`, exit codes, examples
- [Output format](docs/output-format.md) - exact output, using it from JavaScript, pitfalls
- [Library](docs/library.md) - `fileToJS`, embedding the tool
- [API reference](docs/reference.md)

A Claude Code skill for this library is in
[.claude/skills/file-to-js](.claude/skills/file-to-js/SKILL.md).

## License

Copyright (c) 2020-2026 Grigore Stefan
Licensed under the [MIT](LICENSE) license.
