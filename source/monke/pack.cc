#include "pack.hh"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "cryptopp/cryptlib.h"
#include "cryptopp/pwdbased.h"
#include "cryptopp/sha.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/zlib.h"
#include "cryptopp/osrng.h"
#include "config.hh"

namespace monke {

void Pack::pack(const std::string_view input_path, const std::string_view output_path, const std::string_view password) {
    std::ifstream input_file(input_path.data(), std::ios::binary);
    if (!input_file.is_open()) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::ofstream output_file(output_path.data(), std::ios::binary);
    if (!output_file.is_open()) {
        throw std::runtime_error("Failed to open output file.");
    }

    char dummy_header[MONKE_DUMMY_HEADER_LENGTH] = {0};
    output_file.write(dummy_header, sizeof(dummy_header));

    uint64_t password_index = MONKE_PASSWORD_INDEX;
    output_file.write(reinterpret_cast<const char*>(&password_index), sizeof(password_index));

    CryptoPP::SecByteBlock salt(MONKE_SALT_LENGTH);
    CryptoPP::OS_GenerateRandomBlock(true, salt, salt.size());
    output_file.write(reinterpret_cast<const char*>(salt.BytePtr()), salt.size());

    CryptoPP::byte derived_key[MONKE_KEY_LENGTH + MONKE_IV_LENGTH];
    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA1> pbkdf2;
    pbkdf2.DeriveKey(derived_key, MONKE_KEY_LENGTH + MONKE_IV_LENGTH, 0, reinterpret_cast<const CryptoPP::byte*>(password.data()), password.size(), salt.BytePtr(), salt.size(), MONKE_DERIVE_ITERATIONS, 0.0f);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(derived_key + MONKE_IV_LENGTH, MONKE_KEY_LENGTH, derived_key, MONKE_IV_LENGTH);

    CryptoPP::FileSource(input_file, true, new CryptoPP::ZlibCompressor(new CryptoPP::StreamTransformationFilter(encryptor, new CryptoPP::FileSink(output_file)), MONKE_COMPRESSION_LEVEL, MONKE_COMPRESSION_LOG2_BUFFER_SIZE));
}

void Pack::unpack(const std::string_view input_path, const std::string_view output_path, const std::string_view password) {
    std::ifstream input_file(input_path.data(), std::ios::binary);
    if (!input_file.is_open()) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::ofstream output_file(output_path.data(), std::ios::binary);
    if (!output_file.is_open()) {
        throw std::runtime_error("Failed to open output file.");
    }

    char dummy_header[MONKE_DUMMY_HEADER_LENGTH];
    input_file.read(dummy_header, sizeof(dummy_header));

    uint64_t password_index;
    input_file.read(reinterpret_cast<char*>(&password_index), sizeof(password_index));

    char salt[MONKE_SALT_LENGTH];
    input_file.read(salt, sizeof(salt));

    CryptoPP::byte derived_key[MONKE_KEY_LENGTH + MONKE_IV_LENGTH];
    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA1> pbkdf2;
    pbkdf2.DeriveKey(derived_key, MONKE_KEY_LENGTH + MONKE_IV_LENGTH, 0, reinterpret_cast<const CryptoPP::byte*>(password.data()), password.size(), reinterpret_cast<const CryptoPP::byte*>(salt), sizeof(salt), MONKE_DERIVE_ITERATIONS, 0.0f);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(derived_key + MONKE_IV_LENGTH, MONKE_KEY_LENGTH, derived_key, MONKE_IV_LENGTH);

    CryptoPP::FileSource(input_file, true, new CryptoPP::StreamTransformationFilter(decryptor, new CryptoPP::ZlibDecompressor(new CryptoPP::FileSink(output_file))));
}

} // namespace monke
