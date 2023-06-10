// Copyright (c) 2023-2024 Infinium Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#pragma once

#include "epee/include/misc_log_ex.h"
#include "crypto-sugar.h"

namespace crypto
{

  // returns x + x^2 + x^3 + ... + x^(2^f)
  // == x * (x + 1) * (x^2 + 1) * (x^4 + 1) * ...(x^(f+1) + 1)
  inline scalar_t sum_of_powers(scalar_t x, size_t f)
  {
    scalar_t result = x;
    for (size_t i = 0; i < f; ++i)
    {
      result.assign_muladd(result, x, result);
      x *= x;
    }
    return result;
  }


  // returns greatest k, s.t. 2**k <= v
  // tests in crypto_tests_range_proofs.h
  constexpr size_t constexpr_floor_log2(size_t v)
  {
    return v <= 1 ? 0 : constexpr_floor_log2(v >> 1) + 1;
  }

  // returns smallest k, s.t. v <= 2**k
  // tests in crypto_tests_range_proofs.h
  constexpr size_t constexpr_ceil_log2(size_t v)
  {
    return v <= 1 ? 0 : constexpr_floor_log2(v - 1) + 1;
  }



  // returns least significant bit uing de Bruijn sequence
  // http://graphics.stanford.edu/~seander/bithacks.html
  inline uint8_t calc_lsb_32(uint32_t v)
  {
    static const uint8_t multiply_de_bruijn_bit_position[32] =
    {
      0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
      31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    return multiply_de_bruijn_bit_position[((uint32_t)((v & -(int32_t)v) * 0x077CB531U)) >> 27];
  }

  
  ////////////////////////////////////////
  // crypto trait for infinium
  ////////////////////////////////////////
  template<size_t N = 64, size_t values_max = 16>
  struct bpp_crypto_trait_infinium
  {
    static constexpr size_t c_bpp_n           = N;                           // the upper bound for the witness's range
    static constexpr size_t c_bpp_values_max  = values_max;                  // maximum number of elements in BP+ proof, i.e. max allowed BP+ outputs
    static constexpr size_t c_bpp_log2_n      = constexpr_ceil_log2(c_bpp_n);
    static constexpr size_t c_bpp_mn_max      = c_bpp_n * c_bpp_values_max;

    static void calc_pedersen_commitment(const scalar_t& value, const scalar_t& mask, point_t& commitment)
    {
      commitment = value * c_point_G + mask * c_point_H;
    }

    static void calc_pedersen_commitment_2(const scalar_t& value, const scalar_t& mask1, const scalar_t& mask2, point_t& commitment)
    {
      commitment = value * c_point_G + mask1 * c_point_H + mask2 * c_point_H2;
    }

    static const scalar_t& get_initial_transcript()
    {
      static scalar_t value = hash_helper_t::hs("infinium BP+ initial transcript");
      return value;
    }

    // assumes hsc is cleared
    static void update_transcript(hash_helper_t::hs_t& hsc, scalar_t& e, const std::vector<point_t>& points)
    {
      hsc.add_scalar(e);
      hsc.add_points_array(points);
      e = hsc.calc_hash();
    }

    // TODO: refactor with proper OOB handling
    static const point_t& get_generator(bool select_H, size_t index)
    {
      if (index >= c_bpp_mn_max)
        return c_point_0; // out of bound

      static std::vector<point_t> generators(2 * c_bpp_mn_max);
      static bool calculated = false;
      if (!calculated)
      {
        scalar_t hash_buf[2] = { hash_helper_t::hs("infinium BP+ generator"), 0 };
        for (size_t i = 0; i < 2 * c_bpp_mn_max; ++i)
        {
          hash_buf[1].m_u64[0] = i;
          ge_bytes_hash_to_ec(&generators[i].m_p3, &hash_buf, sizeof hash_buf);
        }
        calculated = true;
      }

      return generators[2 * index + (select_H ? 1 : 0)];
    }

    static const scalar_t& get_2_to_the_power_of_N_minus_1()
    {
      static scalar_t result = scalar_t::power_of_2(c_bpp_n) - 1;
      return result;
    }

    static const point_t& bpp_H;
    static const point_t& bpp_H2;
  }; // struct bpp_crypto_trait_infinium

  template<size_t N, size_t values_max>
  const point_t& bpp_crypto_trait_infinium<N, values_max>::bpp_H = c_point_H;

  template<size_t N, size_t values_max>
  const point_t& bpp_crypto_trait_infinium<N, values_max>::bpp_H2 = c_point_H2;

  
  // efficient multiexponentiation (naive stub implementation atm, TODO)
  template<typename CT>
  bool multiexp_and_check_being_zero(const scalar_vec_t& g_scalars, const scalar_vec_t& h_scalars, const point_t& summand)
  {
    CHECK_AND_ASSERT_MES(g_scalars.size() < CT::c_bpp_mn_max, false, "g_scalars oversized");
    CHECK_AND_ASSERT_MES(h_scalars.size() < CT::c_bpp_mn_max, false, "h_scalars oversized");

    point_t result = summand;

    for (size_t i = 0; i < g_scalars.size(); ++i)
      result += g_scalars[i] * CT::get_generator(false, i);

    for (size_t i = 0; i < h_scalars.size(); ++i)
      result += h_scalars[i] * CT::get_generator(true, i);

    if (!result.is_zero())
    {
      LOG_PRINT_L0("multiexp result is non zero: " << result);
      return false;
    }
    return true;
  }


} // namespace crypto

#include "range_proof_bpp.h"
#include "range_proof_bppe.h"
