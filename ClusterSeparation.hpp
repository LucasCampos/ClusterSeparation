/*
 * Separation_Clusters.hpp
 * Copyright (C) 2016 lucas <lucas@localhost.localdomain>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEPARATION_CLUSTERS_HPP
#define SEPARATION_CLUSTERS_HPP

#include <algorithm>
#include <set>

typedef std::pair<unsigned, unsigned> Connection;
typedef std::set<unsigned> Cluster;

namespace {

	bool isIn(unsigned elem, const Cluster& a) {
	    return a.find(elem) != a.end();
	}


    //TODO: Redo in favour of std::remove_if
    template <template <typename Type> class Container>
	void ClearUsed(Container<Connection>& p, const Cluster& s) {

	    //Remove any trace of the set in the connections
	    for(auto it = p.begin(); it != p.end(); it++) {
		if ((isIn(it->first, s)) &&
		    (isIn(it->second, s))) {
		        p.erase(it);
		        ClearUsed(p, s);
		        return;
		    }
	    }
	}

}

template <template <typename Type> class Container>
Container<Cluster> IdentifyClusters(const Container<Connection>& pairs) {

    Container<Cluster> clusters;

    while(pairs.size() > 0){
        Cluster s;
        
        //Bootstrap the new cluster
        s.insert(pairs[0].first);
        s.insert(pairs[0].second);

        //If one of the particles in the cluster is in the connection
        //both particles of the connection are in the cluster
        bool hasMore = false;
        do{
            hasMore = false;
            for(auto& p: pairs) {
                if( isIn(p.first, s) || isIn(p.second, s)) {
                    s.insert(p.first);
                    s.insert(p.second);
                    hasMore = true;
                }
            }

            //Remove the used pairs. I avoided doing it on-the-fly
            //due to iterator invalidation
            ClearUsed(pairs, s);
        } while(hasMore);

        clusters.push_back(s);
    }

    return clusters;

}
#endif /* !SEPARATION_CLUSTERS_HPP */
