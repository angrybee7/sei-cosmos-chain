// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TWTestUtilities.h"

#include "HexCoding.h"
#include <TrustWalletCore/TWAnyAddress.h>
#include <TrustWalletCore/TWCoinType.h>

#include <gtest/gtest.h>

using namespace TW;

TEST(AnyAddress, InvalidString) {
    auto string = STRING("0x4E5B2e1dc63F6b91cb6Cd759936495434C7e972F");
    auto btcAddress = TWAnyAddressCreateWithString(string.get(), TWCoinTypeBitcoin);
    auto ethAaddress = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeEthereum));

    ASSERT_EQ(btcAddress, nullptr);
    ASSERT_NE(ethAaddress.get(), nullptr);
    ASSERT_EQ(TWAnyAddressCoin(ethAaddress.get()), TWCoinTypeEthereum);
}

TEST(AnyAddress, Data) {
    // ethereum
    {
        auto string = STRING("0x4E5B2e1dc63F6b91cb6Cd759936495434C7e972F");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeEthereum));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "4e5b2e1dc63f6b91cb6cd759936495434c7e972f");
    }
    // bnb address key hash
    {
        auto string = STRING("bnb1hlly02l6ahjsgxw9wlcswnlwdhg4xhx38yxpd5");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeBinance));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "bffe47abfaede50419c577f1074fee6dd1535cd1");
    }
    // segwit witness program
    {
        auto string = STRING("bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeBitcoin));
        auto witness = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(witness, "751e76e8199196d454941c45d1b3a323f1433bd6");
    }
    // cashaddr
    {
        auto string = STRING("bitcoincash:qzxf0wl63ahx6jsxu8uuldcw7n5aatwppvnteraqaw");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeBitcoinCash));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "8c97bbfa8f6e6d4a06e1f9cfb70ef4e9deadc10b");
    }
    // base58 dogecoin
    {
        auto string = STRING("DQkiL71KkuGEgS9QFCKJkBeHmzM5YFYGkG");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeDogecoin));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "d726d32d9ff0560e7df35764987fcf01a6a343cf");
    }
    // decred
    {
        auto string = STRING("Dsb4fb7SfdLPhKVQFapGRGnokncgNiYmkAe");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeDecred));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "6ec8261586091a51ea706a62161eceba4b583b49");
    }
    // zcash
    {
        auto string = STRING("t3PkLgT71TnF112nSwBToXsD77yNbx2gJJY");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeZcash));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "38dfa4066f0032c86024bb5899adfa167c80189c");
    }
    // nano
    {
        auto string = STRING("nano_1ie9ffzo57nh51p53eaiqen8y6mxe1z5etcnpmucyts77qk7mqzm1x7yiyjk");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeNano));
        auto pubkey = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(pubkey, "41876b7f51968f182c30b110bb286f127d603e366954b4f6af6b252de459dff3");
    }
    // zilliqa
    {
        auto string = STRING("zil1l8ddxvejeam70qang54wnqkgtmlu5mwlgzy64z");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeZilliqa));

        auto expectedKeyHash = "F9dad33332CF77E783B3452aE982c85effCa6DDf";
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        auto checksumed = WRAPS(TWStringCreateWithRawBytes(TWDataBytes(keyHash.get()), strnlen(expectedKeyHash, 40)));
        assertStringsEqual(checksumed, expectedKeyHash);
    }
    // kusama
    {
        auto string = STRING("HewiDTQv92L2bVtkziZC8ASxrFUxr6ajQ62RXAnwQ8FDVmg");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeKusama));
        auto pubkey = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(pubkey, "e0b3fcccfe0283cc0f8c105c68b5690aab8c5c1692a868e55eaca836c8779085");
    }
    // polkadot
    {
        auto string = STRING("16fir1SPRAaWGtF4ZkKNDq3S6LnD9mbphGXqL923DoH85Exz");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypePolkadot));
        auto pubkey = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(pubkey, "fab55af5eaaa1a284b615946dc3dd403c44ce3448c15884d61b2dcba3ddb245a");
    }
    // cardano
    {
        auto string = STRING("addr1s3xuxwfetyfe7q9u3rfn6je9stlvcgmj8rezd87qjjegdtxm3y3f2mgtn87mrny9r77gm09h6ecslh3gmarrvrp9n4yzmdnecfxyu59jz29g8j");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeCardano));
        auto pubkey = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(pubkey, "0104204dc3393959139f00bc88d33d4b2582fecc237238f2269fc094b286acdb892295206d0b99fdb1cc851fbc8dbcb7d6710fde28df46360c259d482db679c24c4e50b2");
    }
    // neo
    {
        auto string = STRING("AKmrAHRD9ZDUnu4m3vWWonpsojo4vgSuqp");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeNEO));
        auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(keyHash, "172bdf43265c0adfe105a1a8c45b3f406a38362f24");
    }
    // elrond
    {
        auto string = STRING("erd1l453hd0gt5gzdp7czpuall8ggt2dcv5zwmfdf3sd3lguxseux2fsmsgldz");
        auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeElrond));
        auto pubkey = WRAPD(TWAnyAddressData(addr.get()));
        assertHexEqual(pubkey, "fd691bb5e85d102687d81079dffce842d4dc328276d2d4c60d8fd1c3433c3293");
    }
}
