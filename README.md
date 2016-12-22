# ClusterSeparation
Identify the clusters [i.e., graphs] from a container of connections 

To use this tiny library, simply import the ``ClusterSeparation.hpp`` header. The only requirement is a c++11 compiler. In your source code, call the function ``IdentifyClusters``. This function has signature

```c++
std::vector<Cluster> IdentifyClusters(const Container<Connection>& pairs);
```

where

```c++
typedef std::set<unsigned> Cluster;
typedef std::pair<unsigned, unsigned> Connection;
```

The ``Connection`` type will hold the indexes to two nodes, which form a connection. The ``Cluster`` type holds the indexes of all nodes that belong to the cluster.

How the connections will be found depends on the use case. For instance, to build the connections of a system composed of particles, we could use the following function

```c++
std::vector<Connection> FindConnections(const std::vector<float2>& p, float condition) {
    std::vector<Connection> pairs;
    for(unsigned i=0; i<p.size()-1; i++){
        for(unsigned j=i+1; j<p.size(); j++) {
            float dx = p[i].x - p[j].x;
            float dy = p[i].y - p[j].y;

            float r2 = dx*dx + dy*dy;
            
            if (r2 <= condition2){
                pairs.emplace(pairs.end(), i, j);
            }
        }
    }
    return pairs;
}
```
