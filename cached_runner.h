#ifndef CACHED_RUNNER_H
#define CACHED_RUNNER_H

#include "cache.h"
#include <fstream>
#include <iostream>
#include <string>

class CachedRunner {
  private:
    // TODO: private 멤버 변수와 함수 추가 가능
    Cache &cach;
    int hitscount;
    int missescount;

    // 문자열이 팰린드롬인지 검사한다
    bool isPalindrome(std::string str);

  public:
    CachedRunner(Cache &cache);

    // 파일의 숫자를 전부 곱하여 반환한다
    double multiply(std::string filename);

    // 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
    int palindrome(std::string filename);

    // 캐시에 히트한 횟수를 반환한다
    int hits();

    // 캐시에 미스한 횟수를 반환한다
    int misses();
};

#endif