// Copyright (c) 2023-2024 Infinium Developers
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "checkpoints.h"
#include "misc_log_ex.h"

#define ADD_CHECKPOINT(h, hash)  CHECK_AND_ASSERT(checkpoints.add_checkpoint(h,  hash), false)

namespace currency
{

  inline bool create_checkpoints(currency::checkpoints& checkpoints)
  {
#ifdef TESTNET

#else
  ADD_CHECKPOINT(0,  "029f9443ff4fd829b784c83beef82bf4d3f24c2242cdd51191666fe728c27188");
  ADD_CHECKPOINT(1,  "ace9959c79e25a1fb57c9c08c81ef6932282ef8fa96ce17eda92540b14e74609");
  ADD_CHECKPOINT(50,  "0ac771e876f890d573283953378ec55eebeaefb4965e162c4e43b906b545816e");
  ADD_CHECKPOINT(100,  "4522c766900549ab1455aed66134cf716d20128e4043b0d7179dae06bb9184d4");
  ADD_CHECKPOINT(150,  "ac6de6b5aac3644165dc79ea36cf8e1f88397ea2f9a021d3997d0577759084f7");
  ADD_CHECKPOINT(200,  "0d4f8c6c821dd3bc850bd1808d5ba22e322721d9050dcaaaa5b099b0f995c145");

#endif

    return true;
  }

} // namespace currency 
