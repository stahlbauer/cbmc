/*******************************************************************\

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#include <algorithm>
#include <cstdlib>

#include <util/namespace.h>

#include <cegis/jsa/options/jsa_program_info.h>
#include <cegis/jsa/genetic/jsa_random.h>

jsa_randomt::jsa_randomt(
  const namespacet &ns,
  std::function<size_t()> pred_ops_count,
  std::function<size_t()> const_pred_ops_count) :
  ns(ns),
  pred_ops_count(pred_ops_count),
  const_pred_ops_count(const_pred_ops_count)
{
}

void jsa_randomt::havoc(jsa_genetic_solutiont &individual) const
{
  individual.fitness=0;
  havoc(individual.invariant);
  havoc(individual.predicates);
  havoc(individual.query);
}

namespace
{
template<class containert>
void havoc_size(containert &container, const size_t max, const size_t min=1u)
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  const size_t size=rand()%(max+1);
  container.resize(std::max(min, size));
}
}

void jsa_randomt::havoc(jsa_genetic_solutiont::predicatest &predicates) const
{
  predicates.resize(get_num_jsa_preds(ns));
  for (jsa_genetic_solutiont::predicatet &predicate : predicates)
    havoc(predicate);
}

void jsa_randomt::havoc(jsa_genetic_solutiont::predicatet &predicate) const
{
  havoc_size(predicate, get_max_pred_size(ns));
  for (jsa_genetic_solutiont::predicatet::value_type &instr : predicate)
    havoc(instr);
}

void jsa_randomt::havoc(
    jsa_genetic_solutiont::predicatet::value_type &instr) const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  instr.opcode=rand()%get_pred_instruction_set_size();
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  instr.op0=rand()%const_pred_ops_count();
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  instr.op1=rand()%const_pred_ops_count();
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  instr.result_op=rand()%pred_ops_count();
}

void jsa_randomt::havoc(jsa_genetic_solutiont::invariantt &invariant) const
{
  invariant.resize(get_max_inv_size());
  for (jsa_genetic_solutiont::invariantt::value_type &instr : invariant)
    havoc(instr);
}

void jsa_randomt::havoc(
    jsa_genetic_solutiont::invariantt::value_type &instr) const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  instr.opcode=rand()%get_invariant_instruction_set_size();
}

#define MIN_QUERY_SIZE 2u

void jsa_randomt::havoc(jsa_genetic_solutiont::queryt &query) const
{
  havoc_size(query, get_max_query_size(ns), MIN_QUERY_SIZE);
  for (size_t i=0; i < query.size(); ++i)
    havoc(query[i], i);
}

#define QUERY_PREFIX_OP1_VALUE 0u

void jsa_randomt::havoc(jsa_genetic_solutiont::queryt::value_type &instr,
    const size_t index) const
{
  if (index == 0)
  {
    havoc_list(instr.opcode);
    havoc_iterator(instr.op0);
    instr.op1=QUERY_PREFIX_OP1_VALUE;
  } else
  {
    // NOLINTNEXTLINE(runtime/threadsafe_fn)
    instr.opcode=rand()%get_query_instruction_set_size();
    havoc_pred(instr.op0);
    switch(instr.opcode)
    {
      case __CPROVER_jsa_query_idt::FILTER:
        instr.op1=__CPROVER_jsa_null;
        break;
      case __CPROVER_jsa_query_idt::MAP_IN_PLACE:
        instr.op1=__CPROVER_jsa_null;
        break;
      default:
        havoc_list(instr.op1);
    }
  }
}

// NOLINTNEXTLINE(runtime/threadsafe_fn)
unsigned int jsa_randomt::rand() const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  return ::rand();
}

void jsa_randomt::havoc_iterator(__CPROVER_jsa_opt &it) const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  it=rand()%get_max_iterators(ns);
}

void jsa_randomt::havoc_list(__CPROVER_jsa_opt &list) const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  list=rand()%get_max_lists(ns);
}

void jsa_randomt::havoc_pred(__CPROVER_jsa_opt &pred) const
{
  // NOLINTNEXTLINE(runtime/threadsafe_fn)
  pred=rand()%get_num_jsa_preds(ns);
}
