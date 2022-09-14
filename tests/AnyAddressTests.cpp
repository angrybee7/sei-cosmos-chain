// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "AnyAddress.h"
#include "HexCoding.h"

#include <gtest/gtest.h>

namespace TW::tests {

constexpr auto ANY_ADDRESS_TEST_ADDRESS = "bc1qcj2vfjec3c3luf9fx9vddnglhh9gawmncmgxhz";
constexpr auto ANY_ADDRESS_TEST_PUBKEY = "02753f5c275e1847ba4d2fd3df36ad00af2e165650b35fe3991e9c9c46f68b12bc";

TEST(AnyAddress, createFromString) {
    std::unique_ptr<AnyAddress> addr(AnyAddress::createAddress(ANY_ADDRESS_TEST_ADDRESS, TWCoinTypeBitcoin));
    EXPECT_EQ(ANY_ADDRESS_TEST_ADDRESS, addr->address);
}

TEST(AnyAddress, createFromPubKey) {
    const Data key = parse_hex(ANY_ADDRESS_TEST_PUBKEY);
    PublicKey publicKey(key, TWPublicKeyTypeSECP256k1);
    std::unique_ptr<AnyAddress> addr(AnyAddress::createAddress(publicKey, TWCoinTypeBitcoin));
    EXPECT_EQ(ANY_ADDRESS_TEST_ADDRESS, addr->address);
}

TEST(AnyAddress, createFromWrongString) {
    std::unique_ptr<AnyAddress> addr(AnyAddress::createAddress("1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaax", TWCoinTypeBitcoin));
    EXPECT_EQ(nullptr, addr);
}

} // namespace TW::tests
