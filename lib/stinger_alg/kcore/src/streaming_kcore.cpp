#include <stdint.h>

#include "stinger_core/stinger.h"
#include "stinger_core/xmalloc.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
extern "C" {
#include "stinger_alg/kcore.h"
}
#include "streaming_kcore.h"

using namespace gt::stinger;

std::string
StreamingKCore::getName() { return "kcore"; }

int64_t
StreamingKCore::getDataPerVertex() { return 2*sizeof(int64_t); }

std::string
StreamingKCore::getDataDescription()
{
    return "ll kcore size\n"
      "  kcore - a label per vertex, the k of the largest core in which that vertex belongs\n"
      "  count - the number of neighbors also in this large core\n"
      "This algorithm gives an indication of the largest k-core to which each\n"
      "vertex belongs by counting the number of neighboring vertices in the k-1 core and its neighbors'\n"
      "counts of how many neighbors they have in a k-1 core. If their are enough, the vertex upgrades\n"
      "itself to k.";
}

void
StreamingKCore::onInit(stinger_registered_alg * alg)
{
    int64_t k;
    kcore = (int64_t *)alg->alg_data;
    count = ((int64_t *)alg->alg_data) + alg->stinger->max_nv;

    LOG_I("Kcore init starting");
    kcore_find(alg->stinger, kcore, count, alg->stinger->max_nv, &k);
    LOG_I_A("Kcore init finished. Largest core is %ld", (long)k);
}

void
StreamingKCore::onPre(stinger_registered_alg * alg)
{
    /* nothing to do */
}

void
StreamingKCore::onPost(stinger_registered_alg * alg)
{
    int64_t k;
    LOG_I("Kcore post starting");
    kcore_find(alg->stinger, kcore, count, alg->stinger->max_nv, &k);
    LOG_I_A("Kcore post finished. Largest core is %ld", (long)k);
}