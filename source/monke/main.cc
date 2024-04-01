#include <iostream>
#include <string>
#include "pack.hh"
#include "config.hh"

void help() {
  std::cout << "monke v" << MONKE_VERSION_MAJOR << "." << MONKE_VERSION_MINOR << std::endl;
  std::cout << "Copyright 2021 codeshaunted" << std::endl << std::endl;
  std::cout << "Usage: monke <command> [arguments]" << std::endl << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  pack <input path> <output path> <password>" << std::endl;
  std::cout << "  unpack <input path> <output path> <password>" << std::endl;
}

void packOrUnpack(const std::string& command, const std::string& input, const std::string& output, const std::string& password) {
  if (command == "pack" || command == "p") {
    monke::Pack::pack(input, output, password);
    std::cout << "Packed '" << input << "' with password '" << password << "' to '" << output << "'." << std::endl;
  } else if (command == "unpack" || command == "u") {
    monke::Pack::unpack(input, output, password);
    std::cout << "Unpacked '" << input << "' with password '" << password << "' to '" << output << "'." << std::endl;
  } else {
    help();
  }
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    help();
    return 0;
  }

  const std::string command = argv[1];
  if (argc != 5) {
    help();
    return 0;
  }

  packOrUnpack(command, argv[2], argv[3], argv[4]);

  return 0;
}
