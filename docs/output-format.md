# Output format

The example below uses this 23 byte input, `script.js`:

```
print("hi");
	x="a\bb";
```

(the `\b` is a backspace byte, `0x08`, to show that control bytes are
copied like any other).

## The `var`

```
file-to-js --name=data --file-in=script.js --file-out=data.js
```

```js
var data=[
	0x70,0x72,0x69,0x6E,0x74,0x28,0x22,0x68,0x69,0x22,0x29,0x3B,0x0A,0x09,0x78,0x3D,0x22,0x61,0x08,0x62,0x22,0x3B,0x0A
];
```

- `var name=[`, one `0xHH` (upper case hex) per input byte, 32 per line,
  tab indented, `\n` line ends, closed by `];` and a newline.
- The bytes are copied exactly: no text mode, no encoding, no terminator.
  `data.length` is the file size.
- It is a plain array of numbers, valid in every JavaScript version
  (ES3 and later, browsers, Node.js, quantum-script). `--name` is only
  the name of the variable; its value is always the array, never a string.
- A file whose size is a multiple of 32 (and an empty file) ends with an
  extra line holding only a tab; that is valid JavaScript.

An empty input gives an empty array:

```js
var empty=[
	
];
```

## Using it from JavaScript

As bytes:

```js
var bytes = new Uint8Array(data);                          // browsers, Node.js
var blob = new Blob([bytes], {type: "image/png"});         // browsers
var image = URL.createObjectURL(blob);
var buffer = Buffer.from(data);                            // Node.js
```

As text (the input was UTF-8):

```js
var text = new TextDecoder().decode(new Uint8Array(data));  // browsers, Node.js
var text = Buffer.from(data).toString("utf8");              // Node.js
```

As text in older engines, for ASCII / Latin-1 input only:

```js
var text = String.fromCharCode.apply(null, data);           // one char per byte; not UTF-8 aware
```

Load it with a `<script src="data.js">`, concatenate it into a bundle, or
`eval` / `include` it, depending on the environment. To use it as an ES
module or a CommonJS module, wrap it:

```js
// after: file-to-js --name=data ... --file-out=data.js
// append yourself:  export default data;   or   module.exports = data;
```

## Appending

With `--append` (library: `append = true`) the next `var` is written right
after the previous one:

```js
var iconOpen=[
	...
];
var iconSave=[
	...
];
```

Nothing is written between them except the newline that ends the
previous `];`.

## Pitfalls

| Situation | What happens | Do this |
|-----------|--------------|---------|
| a name that is not a JavaScript identifier (`my-logo`, `2d`, a reserved word) | syntax error when the script loads | the name is written as given; sanitize it |
| two `var`s with the same name in one script (or two scripts in one page) | no error, the last one wins | unique `--name` per resource |
| `var` at the top level of a classic script | it becomes a global (`window.data`) | pick names that do not clash, or wrap the file in a function / module |
| loading it as an ES module | `var` stays module local, nothing is exported | append an `export` line |
| large files | 5 bytes of source per input byte, every element is a number in memory | keep embedded files small; serve big ones as files |
| text with `String.fromCharCode` | UTF-8 multi byte characters come out as several Latin-1 characters | use `TextDecoder` |
| `--append` run again on the next build | the output grows with duplicate `var`s | start every sequence with one call without `--append` |
