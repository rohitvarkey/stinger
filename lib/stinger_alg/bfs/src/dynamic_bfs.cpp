#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <stinger_net/stinger_alg.h>

#include "stinger_core/stinger.h"
#include "stinger_core/stinger_atomics.h"
#include "stinger_core/xmalloc.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
extern "C" {
#include "stinger_alg/bfs.h"
}
#include "dynamic_bfs.h"

using namespace gt::stinger;

std::string
BreadthFirstSearch::getName() { return "bfs"; }

int64_t
BreadthFirstSearch::getDataPerVertex() { return sizeof(int64_t); }

std::string
BreadthFirstSearch::getDataDescription() { return "l level"; }

BreadthFirstSearch::BreadthFirstSearch(int64_t sources)
{
    this->source = source;
}

void
BreadthFirstSearch::onInit(stinger_registered_alg * alg)
{
    level = (int64_t*)alg->alg_data;
}

void
BreadthFirstSearch::onPre(stinger_registered_alg * alg)
{
    /* nothing to do */
}

void
BreadthFirstSearch::onPost(stinger_registered_alg * alg)
{
    int64_t *marks = (int64_t *)xcalloc(sizeof(int64_t), stinger_max_nv(alg->stinger));
    int64_t *queue = (int64_t *)xcalloc(sizeof(int64_t), stinger_max_nv(alg->stinger));
    int64_t *Qhead = (int64_t *)xcalloc(sizeof(int64_t), stinger_max_nv(alg->stinger));

    int64_t levels = parallel_breadth_first_search(
            alg->stinger,
            stinger_max_nv(alg->stinger),
            source,
            marks,
            queue,
            Qhead,
            level
    );
    
    xfree(marks);
    xfree(queue);
    xfree(Qhead);
}
