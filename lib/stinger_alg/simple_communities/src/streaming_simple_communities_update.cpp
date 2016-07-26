#include <stdint.h>

#include "stinger_core/stinger.h"
#include "stinger_core/xmalloc.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
extern "C" {
#include "stinger_alg/simple_communities/simple_communities.h"
}
#include "streaming_simple_communities_update.h"

using namespace gt::stinger;

#define UPDATE_EXTERNAL_CMAP(CS) do {                   \
    OMP("omp parallel for")                             \
      for (intvtx_t k = 0; k < CS.graph_nv; ++k)        \
        cmap[k] = CS.cmap[k];                           \
  } while (0)

std::string
StreamingSimpleCommunitiesUpdating::getName() { return "simple_communities"; }

int64_t
StreamingSimpleCommunitiesUpdating::getDataPerVertex() { return sizeof(int64_t); }

std::string
StreamingSimpleCommunitiesUpdating::getDataDescription() { return "l community_label"; }

void
StreamingSimpleCommunitiesUpdating::onInit(stinger_registered_alg * alg)
{
  const struct stinger * S = alg->stinger;
  if (initial_compute)
    comm_time = init_cstate_from_stinger (&cstate, S);
  else {
    comm_time = 0;
    init_empty_community_state (&cstate, nv, (1+stinger_total_edges(S))/2);
  }
  UPDATE_EXTERNAL_CMAP(cstate);
}

void
StreamingSimpleCommunitiesUpdating::onPre(stinger_registered_alg * alg)
{
  /* Must be here to find the removal weights. */
  cstate_preproc_alg (&cstate, alg);
}

void
StreamingSimpleCommunitiesUpdating::onPost(stinger_registered_alg * alg)
{
  cstate_update (&cstate, alg->stinger);
  UPDATE_EXTERNAL_CMAP(cstate);
}
