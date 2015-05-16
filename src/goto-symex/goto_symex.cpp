/*******************************************************************\

Module: Symbolic Execution

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <util/message.h>
#include <util/simplify_expr.h>

#include <linking/zero_initializer.h>

#include "goto_symex.h"

unsigned goto_symext::nondet_count=0;
unsigned goto_symext::dynamic_counter=0;

/*******************************************************************\

Function: goto_symext::do_simplify

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void goto_symext::do_simplify(exprt &expr)
{
  if(options.get_bool_option("simplify"))
    simplify(expr, ns);
}

/*******************************************************************\

Function: goto_symext::replace_nondet

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void goto_symext::replace_nondet(exprt &expr)
{
  if(expr.id()==ID_side_effect &&
     expr.get(ID_statement)==ID_nondet)
  {
    null_message_handlert null_message;
    exprt nondet=
      nondet_initializer(
        expr.type(),
        expr.source_location(),
        ns,
        null_message);

    if(nondet.id()!=ID_side_effect)
    {
      replace_nondet(nondet);
      expr.swap(nondet);
      return;
    }

    exprt new_expr(ID_nondet_symbol, expr.type());
    new_expr.set(ID_identifier, "symex::nondet"+std::to_string(nondet_count++));
    new_expr.add_source_location()=expr.source_location();
    expr.swap(new_expr);
  }
  else
    Forall_operands(it, expr)
      replace_nondet(*it);
}
