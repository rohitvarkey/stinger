#ifndef STINGER_STREAMING_SIMPLE_COMMUNITIES_UPDATE_H_
#define STINGER_STREAMING_SIMPLE_COMMUNITIES_UPDATE_H_

#include <stdint.h>
#include "stinger_net/stinger_alg.h"
#include "streaming_algorithm.h"
namespace gt {
  namespace stinger {
    class StreamingSimpleCommunitiesUpdate : public IStreamingAlgorithm
    {
    private:
        community_state cstate;
        int64_t * restrict cmap;
    public:
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