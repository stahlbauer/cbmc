/*******************************************************************\

Module: Linking: Zero Initialization

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_LINKING_ZERO_INITIALIZER_H
#define CPROVER_LINKING_ZERO_INITIALIZER_H

#include <util/expr.h>

class message_handlert;
class namespacet;
class source_locationt;

exprt zero_initializer(
  const typet &,
  const source_locationt &,
  const namespacet &,
  message_handlert &);

exprt nondet_initializer(
  const typet &,
  const source_locationt &,
  const namespacet &,
  message_handlert &);

// throws a char* in case of failure
exprt zero_initializer(
  const typet &,
  const source_locationt &,
  const namespacet &);

exprt nondet_initializer(
  const typet &type,
  const source_locationt &source_location,
  const namespacet &ns);

#endif // CPROVER_LINKING_ZERO_INITIALIZER_H
