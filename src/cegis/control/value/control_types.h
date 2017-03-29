/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CPROVER_CEGIS_CONTROL_VALUE_CONTROL_TYPES_H
#define CPROVER_CEGIS_CONTROL_VALUE_CONTROL_TYPES_H

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
const class symbol_typet &control_solution_type(const class namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
const class array_typet &control_vector_solution_type(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
const typet &control_float_value_type(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
const typet &control_array_size_type(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 *
 * @return
 */
const typet &control_runtime_array_size_type(const namespacet &ns);

#endif // CPROVER_CEGIS_CONTROL_VALUE_CONTROL_TYPES_H
