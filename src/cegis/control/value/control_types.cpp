/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#include <util/std_types.h>
#include <util/namespace.h>
#include <util/symbol.h>

#include <cegis/control/value/control_vars.h>
#include <cegis/control/value/control_types.h>

const symbol_typet &control_solution_type(const namespacet &ns)
{
  return to_symbol_type(ns.lookup(CEGIS_CONTROL_SOLUTION_VAR_NAME).type);
}

const array_typet &control_vector_solution_type(const namespacet &ns)
{
  return to_array_type(ns.lookup(CEGIS_CONTROL_VECTOR_SOLUTION_VAR_NAME).type);
}

namespace
{
const struct_typet::componentt &get_comp(
  const namespacet &ns,
  const char * const name)
{
  const typet &type=ns.lookup(control_solution_type(ns).get_identifier()).type;
  return to_struct_type(type).get_component(name);
}
}

const typet &control_float_value_type(const namespacet &ns)
{
  const struct_typet::componentt &c=get_comp(ns, CEGIS_CONTROL_A_MEMBER_NAME);
  return to_array_type(c.type()).subtype();
}

const typet &control_array_size_type(const namespacet &ns)
{
  const struct_typet::componentt &c=get_comp(ns, CEGIS_CONTROL_A_MEMBER_NAME);
  return to_array_type(c.type()).size().type();
}

const typet &control_runtime_array_size_type(const namespacet &ns)
{
  const char * const name=CEGIS_CONTROL_A_SIZE_MEMBER_NAME;
  const struct_typet::componentt &c=get_comp(ns, name);
  return c.type();
}
