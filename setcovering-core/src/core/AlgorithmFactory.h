//
//  Factory.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-26.
//
//

#ifndef __setcovering_core__Factory__
#define __setcovering_core__Factory__

#include <stdio.h>
#include <map>
#include "../metaheuristics/Algorithm.h"

template <class T=Algorithm, class Key=std::string>
class AlgorithmFactory {
    static std::map<Key, T*> _map;

public:
    static void Register(Key key, T* algorithm);
    T* Create(const Key& key);
};

#endif /* defined(__setcovering_core__Factory__) */
