/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CPROVER_CEGIS_JSA_PREPROCESSING_CLONE_HEAP_H
#define CPROVER_CEGIS_JSA_PREPROCESSING_CLONE_HEAP_H

#include <goto-programs/goto_program.h>

/**
 * @brief
 *
 * @details
 *
 * @param gf
 * @return
 */
const class symbol_exprt &get_user_heap(const class goto_functionst &gf);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 * @return
 */
symbol_exprt get_queried_heap(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 * @return
 */
symbol_exprt get_org_heap(const namespacet &ns);

/**
 * @brief
 *
 * @details
 *
 * @param prog
 */
void clone_heap(class jsa_programt &prog);

/**
 * @brief
 *
 * @details
 *
 * @param ns
 * @param body
 * @param pos
 * @param heap_ptr
 */
goto_programt::targett assume_valid_heap(
  const namespacet &ns,
  goto_programt &body,
  goto_programt::targett pos,
  const exprt &heap_ptr);

#endif // CPROVER_CEGIS_JSA_PREPROCESSING_CLONE_HEAP_H
