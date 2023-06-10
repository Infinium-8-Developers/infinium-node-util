// Copyright (c) 2023-2024 Infinium Developers
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "genesis_acc.h"

namespace currency
{
#ifndef TESTNET
const std::string ggenesis_tx_pub_key_str = "e48ddb01769084732088767c6cebcd2869ba7887d50872bf939b14a856f3631a";
const crypto::public_key ggenesis_tx_pub_key = epee::string_tools::parse_tpod_from_hex_string<crypto::public_key>(ggenesis_tx_pub_key_str);
extern const genesis_tx_dictionary_entry ggenesis_dict[1];
const genesis_tx_dictionary_entry ggenesis_dict[1] = {
{12950756864913537035ULL,0}
};

#else 
const std::string ggenesis_tx_pub_key_str = "e48ddb01769084732088767c6cebcd2869ba7887d50872bf939b14a856f3631a";
const crypto::public_key ggenesis_tx_pub_key = epee::string_tools::parse_tpod_from_hex_string<crypto::public_key>(ggenesis_tx_pub_key_str);
extern const genesis_tx_dictionary_entry ggenesis_dict[1];
const genesis_tx_dictionary_entry ggenesis_dict[1] = {
{12950756864913537035ULL,0}
};

#endif 

}