#ifndef STINGER_STREAMING_PAGERANK_H_
#define STINGER_STREAMING_PAGERANK_H_

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include "stinger_net/stinger_alg.h"
#include "streaming_algorithm.h"
namespace gt {
  namespace stinger {
    class StreamingPagerank : public IStreamingAlgorithm
    {
    private:
        const char *type_str;
        int type_specified;
        int directed;
        double epsilon;
        double dampingfactor;
        int64_t maxiter;

        double * pr;
        double * tmp_pr;
    public:
        StreamingPagerank(
          const char * type_str,
          int type_specified,
          int directed,
          double epsilon,
          double dampingfactor,
          int64_t maxiter);

        ~StreamingPagerank();

        // Overridden from IStreamingAlgorithm
        std::string getName();
        int64_t getDataPerVertex();
        std::string getDataDescription();
        void onInit(stinger_registered_alg * alg);
        void onPre(stinger_registered_alg * alg);
        void onPost(stinger_registered_alg * alg);
    };
  }
}

#endif