#include <stdint.h>

#include "stinger_core/stinger.h"
#include "stinger_core/xmalloc.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
#include "stinger_alg/streaming_kcore.h"
#include "stinger_net/stinger_alg.h"
#include "stinger_net/stinger_alg_client.h"

using namespace gt::stinger;

int
main(int argc, char *argv[])
{
    KCore alg;
    run_alg_as_client(alg);
}
