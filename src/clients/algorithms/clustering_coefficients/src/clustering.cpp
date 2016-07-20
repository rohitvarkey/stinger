#include "stinger_net/stinger_alg_client.h"
#include "stinger_alg/streaming_clustering.h"

using namespace gt::stinger;

int
main(int argc, char *argv[])
{
  StreamingClusteringCoefficients alg;
  run_alg_as_client(alg);
}
