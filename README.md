# monke

**monke** is a versatile command-line tool designed for packing and unpacking Bloons TD 6 save files and other files encoded using the NinjaKiwi file encoding. However, please be aware that the misuse of this tool may result in the flagging or banning of your NinjaKiwi account. Exercise caution when using it.

## Building
### Disclaimer
Building **monke** from source requires a moderate understanding of C++. If you prefer not to build it yourself, you can download a pre-built binary from the [GitHub releases page](https://github.com/codeshaunted/monke/releases).

### Required Software
To download and build **monke**, you'll need Git, CMake 3.12 or newer, and either MSVC or GCC compilers (Clang is not compatible due to library constraints).

### Cloning the Repository
Clone the repository into your preferred directory using the command below. Ensure to include the `--recursive` flag to avoid build failures.
```bash
git clone --recursive https://github.com/codeshaunted/monke
```

### Building the Repository
Navigate to the cloned repository and execute the following commands:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

If the process completes successfully, you should find a **monke** executable inside the build folder. If you encounter any issues, feel free to open an issue on GitHub with detailed information.

## Usage
**monke** offers two primary commands: `unpack` and `pack`.

### `unpack`
The `unpack` command decodes a NinjaKiwi encoded file into a new file. It requires the input file path, output file path, and the password for decryption. Here's an example of its usage:
```bash
monke unpack Profile.Save Profile.Save.json 11
```

### `pack`
The `pack` command encodes a file into a NinjaKiwi format. It needs the input file path, output file path, and the encryption password. Here's an example:
```bash
monke pack Profile.Save.json Profile.Save 11
```

## Passwords
To operate on save files, you'll need a password. Below is a list of passwords corresponding to various NinjaKiwi games:
| Game          | Password    |
| ------------- | ----------- |
| Tower Keepers | `8`         |
| Bloons TD 6   | `11`        |

Ensure you use the correct password for the respective game's save file.
