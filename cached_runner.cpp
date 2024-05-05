#include "cached_runner.h"

CachedRunner::CachedRunner(Cache &cache):cach(cache) {
    hitscount = 0;
    missescount = 0;

}
// 문자열이 팰린드롬인지 검사한다
bool CachedRunner::isPalindrome(std::string str) {
    for (int i = 0; i < str.size() / 2; i++) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename) {
    double val;
    if (cach.get(filename, val)) {
        hitscount++;
        return val;
    }
    std::ifstream file(filename);
    double result = 1;
    double number;
    while (file >> number) {
        result *= number;
    }
    
    cach.add(filename, result);
    missescount++;
    return result;
}

// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename) {
    int val;
    if (cach.get(filename, val)) {
        hitscount++;
        return val;
    }
    std::ifstream file(filename);
    std::string fullText;
    std::string line;
    while (std::getline(file, line)) {
        fullText += line;
    }

    int maxLength = 0;
    int maxIndex = 0;
    std::string maxPalindrome;
    for (int i = 0; i < fullText.size(); i++) {
        for (int j = i + 1; j < fullText.size(); j++) {
            std::string sub = fullText.substr(i, j - i + 1);
            if (isPalindrome(sub) && sub.size() > maxLength) {
                maxLength = sub.size();
                maxIndex = i;
                maxPalindrome = sub;
            }
        }
    }
    
    cach.add(filename, maxIndex);
    
    missescount++;
    return maxIndex;
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits() { return hitscount; }

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses() { return missescount; }