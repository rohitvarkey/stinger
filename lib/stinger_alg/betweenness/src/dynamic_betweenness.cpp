#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "stinger_core/stinger.h"
#include "stinger_core/stinger_atomics.h"
#include "stinger_core/xmalloc.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
extern "C" {
#include "stinger_alg/betweenness.h"
}
#include "dynamic_betweenness.h"

using namespace gt::stinger;

std::string
BetweennessCentrality::getName() { return "betweenness_centrality"; }

int64_t
BetweennessCentrality::getDataPerVertex() { return sizeof(int64_t) + sizeof(double); }

std::string
BetweennessCentrality::getDataDescription() { return "dl bc times_found"; }

BetweennessCentrality::BetweennessCentrality(int64_t num_samples, double weighting, uint8_t do_weighted)
{
    this->num_samples = num_samples;
    this->weighting = weighting;
    old_weighting = 1 - weighting;
    this->do_weighted = do_weighted;
}

void
BetweennessCentrality::onInit(stinger_registered_alg * alg)
{
    bc = (double *)alg->alg_data;
    times_found = (int64_t *)(bc + alg->stinger->max_nv);
    sample_bc = NULL;

    if(do_weighted) {
        sample_bc = (double *)xcalloc(sizeof(double), alg->stinger->max_nv);
    }

    if (stinger_max_active_vertex(alg->stinger) > 0)
    {
        sample_search(alg->stinger, stinger_max_active_vertex(alg->stinger) + 1, num_samples, bc, times_found);
    }
}

void
BetweennessCentrality::onPre(stinger_registered_alg * alg)
{
    /* nothing to do */
}

void
BetweennessCentrality::onPost(stinger_registered_alg * alg)
{
    int64_t nv = (stinger_mapping_nv(alg->stinger))?stinger_mapping_nv(alg->stinger)+1:0;
    if (nv > 0) {
        if(do_weighted) {
            sample_search(alg->stinger, nv, num_samples, sample_bc, times_found);

            OMP("omp parallel for")
            for(int64_t v = 0; v < nv; v++) {
                bc[v] = bc[v] * old_weighting + weighting* sample_bc[v];
            }
        } else {
            sample_search(alg->stinger, nv, num_samples, bc, times_found);
        }
    }
}

BetweennessCentrality::~BetweennessCentrality()
{
    if(do_weighted) {
        xfree(sample_bc);
    }
}
