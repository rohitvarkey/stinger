set(sources

# FIXME move these to subdir
  src/community_on_demand.c
  src/shortest_paths.cpp
  src/diameter.cpp
  src/independent_sets.c
  src/graph_partition.c
  src/hits_centrality.c
  src/diameter.cpp
  src/independent_sets.c
  src/graph_partition.c
  src/hits_centrality.c
  src/modularity.c

  adamic_adar/src/adamic_adar.c
  betweenness/src/betweenness.c
    betweenness/src/streaming_betweenness.cpp
  bfs/src/bfs.c
  clustering/src/clustering.c
    clustering/src/streaming_clustering.cpp
  kcore/src/kcore.c
    kcore/src/streaming_kcore.cpp
  pagerank/src/pagerank.c
    pagerank/src/streaming_pagerank.cpp
  random/src/random.c
  rmat/src/rmat.c
  simple_communities/src/community.c
    simple_communities/src/community-update.c
    simple_communities/src/graph-el.c
    simple_communities/src/sorts.c
    simple_communities/src/streaming_simple_communities.cpp
    simple_communities/src/streaming_simple_communities_updating.cpp
  static_components/src/static_components.c
  streaming_connected_components/src/streaming_connected_components.c
  weakly_connected_components/src/weakly_connected_components.c
)
# Don't include all .h files here, just the ones that contain public definitions
set(headers
# FIXME move these to subdir
  inc/community_on_demand.h
  inc/shortest_paths.h
  inc/diameter.h
  inc/independent_sets.h
  inc/graph_partition.h
  inc/hits_centrality.h
  inc/modularity.h

  adamic_adar/inc/adamic_adar.h
  betweenness/inc/betweenness.h
    betweenness/inc/streaming_betweenness.h
  bfs/inc/bfs.h
  clustering/inc/clustering.h
    clustering/inc/streaming_clustering.h
  kcore/inc/kcore.h
    kcore/inc/streaming_kcore.h
  pagerank/inc/pagerank.h
    pagerank/inc/streaming_pagerank.h
  random/inc/random.h
  rmat/inc/rmat.h
  simple_communities/inc/community.h
    simple_communities/inc/defs.h
    simple_communities/inc/graph-el.h
    simple_communities/inc/community-update.h
    simple_communities/inc/streaming_simple_communities.h
    simple_communities/inc/streaming_simple_communities_updating.h
  static_components/inc/static_components.h
  streaming_connected_components/inc/streaming_connected_components.h
  weakly_connected_components/inc/weakly_connected_components.h
  common/inc/streaming_algorithm.h
)

publish_headers(headers "${CMAKE_BINARY_DIR}/include/stinger_alg")

include_directories("${CMAKE_BINARY_DIR}/include/stinger_alg")
include_directories("${CMAKE_BINARY_DIR}/include/stinger_core")
include_directories("${CMAKE_BINARY_DIR}/include/stinger_net")
include_directories("${CMAKE_BINARY_DIR}/include/stinger_utils")

set_source_files_properties(${config} PROPERTIES GENERATED TRUE)
add_library(stinger_alg SHARED ${sources} ${headers} ${config})
target_link_libraries(stinger_alg stinger_core stinger_net stinger_utils compat)
#target_include_directories(stinger_alg PRIVATE simple_communities/inc)
