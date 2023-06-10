// Copyright (c) 2023-2024 Infinium Developers
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "genesis.h"

namespace currency
{
#ifndef TESTNET
const genesis_tx_raw_data ggenesis_tx_raw = {{
0xb680800100000101,0x45cf030cb7cee88b,0x236ca43707cb3fce,0x66ee1faf3d9416a7,0xa99103ed5b6af374,0x05004f842e5c3c32,0x84907601db8de416,0xcdeb6c7c76882073,0x7208d58778ba6928,0x63f356a8149b93bf,0x463643453228131a,0x3444334346323639,0x4332433739383036,0x3033443135454645,0x3043363641413739,0xc5020b0015423030},
{0x27,0x0e,0x0a,0x00,0x00}};

#else
const genesis_tx_raw_data ggenesis_tx_raw = {{
0xb680800100000101,0x45cf030cb7cee88b,0x236ca43707cb3fce,0x66ee1faf3d9416a7,0xa99103ed5b6af374,0x05004f842e5c3c32,0x84907601db8de416,0xcdeb6c7c76882073,0x7208d58778ba6928,0x63f356a8149b93bf,0x463643453228131a,0x3444334346323639,0x4332433739383036,0x3033443135454645,0x3043363641413739,0xc5020b0015423030},
{0x27,0x0e,0x0a,0x00,0x00}};

#endif
}
