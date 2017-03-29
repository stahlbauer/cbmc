/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#include <ansi-c/expr2c.h>
#include <util/namespace.h>
#include <util/symbol_table.h>
#include <goto-programs/remove_returns.h>

#include <cegis/cegis-util/string_helper.h>
#include <cegis/instrument/literals.h>
#include <cegis/instrument/meta_variables.h>
#include <cegis/refactor/instructionset/processor_types.h>
#include <cegis/refactor/instructionset/processor_symbols.h>

#define VARIABLE_ARRAY_PREFIX CEGIS_PREFIX "variable_array_"

std::string cegis_operand_array_name(const namespacet &ns, const typet &type)
{
  std::string result(VARIABLE_ARRAY_PREFIX);
  return result+=type2c(type, ns);
}

#define OPERAND_ID_MEMBER_NAME_PREFIX "op_"

std::string cegis_operand_base_name(const size_t op)
{
  std::string name(OPERAND_ID_MEMBER_NAME_PREFIX);
  return name+=std::to_string(op);
}

namespace
{
dereference_exprt cegis_instr(
  const namespacet &ns,
  const std::string &func_name)
{
  const char * const prog_base_name=CEGIS_PROC_PROGRAM_PARAM_ID;
  const std::string prog_name(get_local_meta_name(func_name, prog_base_name));
  const symbol_exprt prog(ns.lookup(prog_name).symbol_expr());
  const char * const index_base_name=CEGIS_PROC_INSTR_INDEX;
  const std::string index_name(get_local_meta_name(func_name, index_base_name));
  const symbol_exprt index(ns.lookup(index_name).symbol_expr());
  return dereference_exprt(plus_exprt(prog, index), prog.type().subtype());
}
}

member_exprt cegis_opcode(const namespacet &ns, const std::string &func_name)
{
  const dereference_exprt instr(cegis_instr(ns, func_name));
  const typet member_type(cegis_opcode_type());
  return member_exprt(instr, CEGIS_PROC_OPCODE_MEMBER_NAME, member_type);
}

member_exprt cegis_operand_id(
  const namespacet &ns,
  const std::string &func_name,
  const size_t op)
{
  const dereference_exprt instr(cegis_instr(ns, func_name));
  const std::string member_name(cegis_operand_base_name(op));
  const typet member_type(cegis_operand_type());
  return member_exprt(instr, member_name, member_type);
}

dereference_exprt cegis_operand(
  const namespacet &ns,
  const std::string &func_name,
  const typet &type,
  const size_t op)
{
  const member_exprt operand_id(cegis_operand_id(ns, func_name, op));
  const std::string array_name(cegis_operand_array_name(ns, type));
  const symbol_exprt array(ns.lookup(array_name).symbol_expr());
  return dereference_exprt(index_exprt(array, operand_id), type);
}

namespace
{
#define JAVA_TMP_RETURN "::return_tmp"
}

bool is_refactor_meta_var(const irep_idt &var)
{
  const std::string &var_name=id2string(var);
  return starts_with(var_name, CPROVER_PREFIX)
      || contains(var_name, RETURN_VALUE_SUFFIX)
      || contains(var_name, JAVA_TMP_RETURN);
}
