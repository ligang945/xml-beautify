# xml-beautify

A lightweight tool for formatting XML files.

## Features

- Beautifies and formats XML files
- Configurable indentation
- In-place editing or output to file/stdout
- Simple command-line interface
- Cross-platform support (Linux, macOS, Windows)

## Building

### Prerequisites

- **Linux**: `g++` and `scons`
- **macOS**: `clang` and `scons` (install via `brew install scons`)
- **Windows**: MSVC and `scons` (install via `pip install scons`)

### Compile

```bash
scons
```

## Usage

```
xml-beautify [OPTIONS] INPUT_FILE
```

### Options

| Option | Description |
|--------|-------------|
| `-h, --help` | Show help message and exit |
| `-o, --output FILE` | Output file (default: print to stdout) |
| `-i, --indent NUM` | Indentation spaces (default: 4) |
| `-v, --verbose` | Enable verbose output |
| `--inplace` | Edit input file in place (overwrites original) |

### Examples

#### Print to stdout
```bash
./xml-beautify input.xml
```

#### Save to output file
```bash
./xml-beautify input.xml -o output.xml
```

####`Edit in place
```bash
./xml-beautify input.xml --inplace
```

#### Custom indentation (2 spaces)
```bash
./xml-beautify input.xml -i 2
```

## Example

Input file (`input.xml`):

```xml
<?xml version="1.0"?><root><child>text</child></root>
```

Output:

```xml
<?xml version="1.0"?>
<root>
    <child>text</child>
</root>
```

## Releases

Download pre-built binaries for your platform from the [GitHub Releases](https://github.com/your-username/xml-beautify/releases) page:

- `xml-beautify-linux-amd64.tar.gz` - Linux x86_64
- `xml-beautify-linux-arm64.tar.gz` - Linux ARM64
- `xml-beautify-darwin-amd64.tar.gz` - macOS Intel
- `xml-beautify-darwin-arm64.tar.gz` - macOS Apple Silicon
- `xml-beautify-windows-amd64.zip` - Windows x86_64

## License

See [LICENSE](LICENSE) file.
