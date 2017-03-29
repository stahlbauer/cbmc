/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CPROVER_CEGIS_JSA_OPTIONS_JSA_PROGRAM_INFO_H
#define CPROVER_CEGIS_JSA_OPTIONS_JSA_PROGRAM_INFO_H

#include <cstddef>

/**
 * @brief
 *
 * @details
 */
#define JSA_PREDS "__CPROVER_JSA_PREDICATES"

/**
 * @brief
 *
 * @details
 *
 * @param st
 * @param symbol_name
 *
 * @return
 */
size_t get_array_size(
    const class symbol_tablet &st,
    const char * const symbol_name);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
size_t get_max_pred_size(const class namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
size_t get_max_query_size(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @return
 */
size_t get_max_inv_size();

/**
 * @brief
 *
 * @details
 *
 * @return
 */
size_t get_pred_instruction_set_size();

/**
 * @brief
 *
 * @details
 *
 * @return
 */
size_t get_query_instruction_set_size();

/**
 * @brief
 *
 * @details
 *
 * @return
 */
size_t get_invariant_instruction_set_size();

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
size_t get_num_jsa_preds(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
size_t get_max_iterators(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
size_t get_max_lists(const namespacet &ns);

#endif // CPROVER_CEGIS_JSA_OPTIONS_JSA_PROGRAM_INFO_H
