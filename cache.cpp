#include "cache.h"

Cache::Cache() {
    cachesize = 0;
    body = NULL;

    for (int i = 0; i < 7; i++) {
        hashmap[i] = NULL;
    }
}
Cache::~Cache() {}

// int를 cache에 추가한다
void Cache::add(std::string key, int value) {

    Cachelist *newcach = new Cachelist;
    newcach->key = key;
    newcach->intval = value;
    if (body != NULL)
        body->prvLink = newcach;

    newcach->nextLink = body;
    newcach->isIntTpye = true;
    newcach->prvLink = NULL;
    body = newcach;

    hashList *newhashlist = new hashList;
    newhashlist->cash = newcach;
    newhashlist->nextcash = NULL;

    hashList *hashlist;
    hashlist = hashmap[key[key.size() - 5] - '0'];

    if (hashlist == NULL) {
        hashmap[key[key.size() - 5] - '0'] = newhashlist;
    } else {
        while (hashlist->nextcash != NULL) {
            hashlist = hashlist->nextcash;
        }
        hashlist->nextcash = newhashlist;
    }
    if (cachesize == CACHE_SIZE) {
        cashedelete();

    } else {
        cachesize++;
    }
}

// double을 cache에 추가한다
void Cache::add(std::string key, double value) {

    Cachelist *newcach = new Cachelist;
    newcach->key = key;
    newcach->doubleval = value;
    if (body != NULL)
        body->prvLink = newcach;

    newcach->nextLink = body;
    newcach->prvLink = NULL;
    newcach->isIntTpye = false;
    body = newcach;
    hashList *newhashlist = new hashList;
    newhashlist->cash = newcach;
    newhashlist->nextcash = NULL;
    hashList *hashlist;

    hashlist = hashmap[key[key.size() - 5] - '0'];
    if (hashlist == NULL) {
        hashmap[key[key.size() - 5] - '0'] = newhashlist;
    } else {
        while (hashlist->nextcash != NULL) {
            hashlist = hashlist->nextcash;
        }
        hashlist->nextcash = newhashlist;
    }
    if (cachesize == CACHE_SIZE) {
        cashedelete();
    } else {
        cachesize++;
    }
}

// 캐쉬 삭제
void Cache::cashedelete() {
    Cachelist *endcach = body;
    while (endcach->nextLink != NULL) {
        endcach = endcach->nextLink;
    }
    hashedelete(endcach->key);
    endcach = endcach->prvLink;
    delete endcach->nextLink;
    endcach->nextLink = NULL;
}

// 해쉬 삭제
void Cache::hashedelete(std::string key) {

    hashList *endhashlist = hashmap[key[key.size() - 5] - '0'];
    hashList *hashlist = endhashlist;
    while (endhashlist->cash->key != key) {
        hashlist = endhashlist;
        endhashlist = endhashlist->nextcash;
    }
    if (hashlist == endhashlist) {
        hashmap[key[key.size() - 5] - '0'] = hashlist->nextcash;
    } else {
        hashlist->nextcash = endhashlist->nextcash;
    }
    delete endhashlist;
}

// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value) {
    hashList *endhashlist = hashmap[(key[key.size() - 5] - '0')];
    if (endhashlist == NULL) {
        return false;
    } else {
        while (endhashlist->nextcash != NULL && endhashlist->cash->key != key) {
            endhashlist = endhashlist->nextcash;
        }
    }
    if (endhashlist->cash->key == key) {
        value = endhashlist->cash->intval;
        if (endhashlist->cash->prvLink == NULL) {
            return true;
        }
        endhashlist->cash->prvLink->nextLink = endhashlist->cash->nextLink;
        if (endhashlist->cash->nextLink != NULL) {
            endhashlist->cash->nextLink->prvLink = endhashlist->cash->prvLink;
        }
        body->prvLink = endhashlist->cash;
        endhashlist->cash->nextLink = body;
        body = endhashlist->cash;
        body->prvLink = NULL;
        return true;
    }

    return false;
}

// key에 해당하는 value를 cache에서 가져온다.
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, double &value) {
    hashList *endhashlist = hashmap[key[key.size() - 5] - '0'];
    if (endhashlist == NULL) {
        return false;
    } else {
        while (endhashlist->nextcash != NULL && endhashlist->cash->key != key) {
            endhashlist = endhashlist->nextcash;
        }
    }
    if (endhashlist->cash->key == key) {
        value = endhashlist->cash->doubleval;
        if (endhashlist->cash->prvLink == NULL) {
            return true;
        }
        endhashlist->cash->prvLink->nextLink = endhashlist->cash->nextLink;
        if (endhashlist->cash->nextLink != NULL) {
            endhashlist->cash->nextLink->prvLink = endhashlist->cash->prvLink;
        }
        body->prvLink = endhashlist->cash;
        endhashlist->cash->nextLink = body;
        body = endhashlist->cash;
        body->prvLink = NULL;
        return true;
    }

    return false;
}

// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString() {
    int count = 0;
    std::string tostring = "";
    Cachelist *nowcash = body;

    while (count++ < cachesize) {
        if (nowcash->isIntTpye) {

            tostring += "[palindrome(" + nowcash->key +
                        "): " + std::to_string(nowcash->intval) + "]";
        } else
            tostring += "[multiply(" + nowcash->key +
                        "): " + doubleToString(nowcash->doubleval) + "]";

        if (count < cachesize) {
            tostring += " -> ";
        }
        if (nowcash->nextLink != NULL)
            nowcash = nowcash->nextLink;
    }

    return tostring + "\n";
}

// double 값을 문자열로 변환한다
std::string Cache::doubleToString(double value) {
    std::ostringstream ss;
    ss << value;
    return ss.str();
}