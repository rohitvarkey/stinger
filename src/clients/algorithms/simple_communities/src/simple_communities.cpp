#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "stinger_core/stinger.h"
#include "stinger_core/stinger_error.h"
#include "stinger_net/stinger_alg.h"
#include "stinger_net/stinger_alg_client.h"
#include "stinger_alg/streaming_simple_communities.h"
using namespace gt::stinger;

int
main(int argc, char *argv[])
{
  StreamingSimpleCommunities alg;
  run_alg_as_client(alg);
  return 0;
}
