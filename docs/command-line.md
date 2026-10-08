# Command line

```
file-to-js [options] [@file ...]
```

## Options

| Option | Effect |
|--------|--------|
| `--help`, `--usage` | print usage, exit 0 |
| `--license` | print the license, exit 0 |
| `--version` | print the tool's own version, exit 0 |
| `--name=name` | name of the generated `var`; required |
| `--file-in=file` | input file, any content; required |
| `--file-out=file` | output file; required; its folder must exist |
| `--append` | add the `var` to the end of the output instead of replacing it |
| `--touch=file` | regenerate only if the input is newer than the output; afterwards touch `file` |
| `@file` | read more arguments from `file` (a response file) |

`--help`, `--usage`, `--license` and `--version` act as soon as they are
seen. Arguments that do not start with `--` (other than `@file`) and
unknown options are ignored. An empty `--name=`, `--file-in=`,
`--file-out=` or `--touch=` is an error. When a required option is
missing, the usage is printed and the exit code is `1`.

The exact output is in [Output format](output-format.md).

## Order of work

1. Expand the `@file` response files, then read the options.
2. Check `--name`, `--file-in`, `--file-out`.
3. `--touch`: if the output exists and the input is **not newer** than it,
   stop with exit code `0`; nothing is written or touched.
4. Write the output, replacing it or (`--append`) appending to it.
5. `--touch`: touch the file if it exists (a missing one is not an error).

## --touch

`--touch=file` keeps a build incremental:

- input not newer than output → nothing happens, the output keeps its
  time;
- input newer, or no output yet → the output is written and `file` gets
  the current time, so whatever depends on `file` (a bundle, a `.cpp` that
  embeds the script, ...) is rebuilt.

The check compares the last write time of `--file-in` and `--file-out`
(`Shell::compareLastWriteTime`, nanoseconds on Linux).

A **missing input** with an existing output counts as "not newer": the
tool exits `0` and does nothing. Without `--touch` a missing input is an
error (exit `1`).

Do not combine `--touch` with `--append` on a shared output: once the
first input has written the file, the next ones are compared against it
and skipped.

## --append

```
file-to-js --name=iconOpen --file-in=open.png --file-out=icons.js
file-to-js --name=iconSave --file-in=save.png --file-out=icons.js --append
file-to-js --name=iconExit --file-in=exit.png --file-out=icons.js --append
```

The first call replaces the output, the next ones add to it. Every run of
an `--append` call adds again: start the sequence with a call without
`--append` (or remove the output first), or the file collects duplicate
`var`s (valid JavaScript, the last one wins, but the file keeps growing).

## Exit codes

| Code | Meaning |
|------|---------|
| `0` | written; also up to date (`--touch`), and `--help` / `--usage` / `--license` / `--version` |
| `1` | missing or empty required option, response file not found, input can not be read, output can not be written |

Messages go to `stdout`: `Error: name is empty`, `Error: file-in is
empty`, `Error: file-out is empty`, `Error: touch filename is empty`, and
`Error: file not found - <file>` for a response file.

A failed conversion (input missing, output folder missing, no access)
**prints nothing**: the exit code `1` is the only signal. Check it in the
build script.

## Response files

`@file` is replaced by the arguments read from `file`, split like a command
line (quotes group words). Several `@file` and normal arguments can be
mixed:

```
--name=logoPng
--file-in=logo.png
"--file-out=web/logo.js"
```

```
file-to-js @logo.args --touch=web/bundle.js
```

## From fabricare

In a `fabricare/*.js` script the tool is on the `PATH` of the build:

```js
runInPath("web", function() {
	exitIf(Shell.system("file-to-js --touch=bundle.js --file-in=logo.png --file-out=logo.js --name=logoPng"));
});
```

Inside fabricare itself the tool is linked in
(`file-to-js.application.static`) and is also available to scripts as the
function `fileToJS(...)`, which takes the same arguments as strings, one
per parameter, and returns the exit code:

```js
exitIf(fileToJS("--touch=bundle.js", "--file-in=logo.png", "--file-out=logo.js", "--name=logoPng"));
```

## Examples

A binary file:

```
file-to-js --name=logoPng --file-in=logo.png --file-out=logo.js
```

Several files in one script:

```
file-to-js --name=fontRegular --file-in=regular.woff2 --file-out=fonts.js
file-to-js --name=fontBold --file-in=bold.woff2 --file-out=fonts.js --append
```

Only when the input changed:

```
file-to-js --touch=bundle.js --file-in=logo.png --file-out=logo.js --name=logoPng
```
