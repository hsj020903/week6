#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <iostream>
#include <sstream>
#define CACHE_SIZE 10

class Cache {
  private:
    int cachesize;   //캐쉬 크기
    // TODO: private inner struct/class 선언 가능

    //캐쉬 리스트
    struct Cachelist {
        std::string key;
        double doubleval;
        int intval;
        bool isIntTpye; 
        Cachelist *prvLink;     //이전 캐쉬
        Cachelist *nextLink;    //다음 캐쉬
    };

    //해쉬 리스트
    struct hashList{
        Cachelist* cash;    //캐쉬
        hashList* nextcash; //다음 해쉬
    };

    // TODO: private 멤버 변수와 함수 추가 가능


    Cachelist* body;        // 캐쉬 리스트의 시작
    hashList* hashmap[7];  // 해쉬 리스트

    //초과한 캐쉬 삭제
    void cashedelete();
    //삭제된 캐쉬를 연결한 해쉬 삭제
    void hashedelete(std::string key);
    // double 값을 문자열로 변환한다
    std::string doubleToString(double value);
    
  public:
    Cache();
    ~Cache();
    // int를 cache에 추가한다
    void add(std::string key, int value);
    // double을 cache에 추가한다
    void add(std::string key, double value);
    // key에 해당하는 value를 cache에서 가져온다
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    bool get(std::string key, int &value);
    // key에 해당하는 value를 cache에서 가져온다.
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    bool get(std::string key, double &value);

    // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
    // 다음과 같이 표현된 문자열을 반환한다
    // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
    std::string toString();
};

#endif