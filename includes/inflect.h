#ifndef INFLECT_H
#define INFLECT_H

#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std;

class Inflect {
    public:
        static string pluralize(const string& stringy) {
            if (stringy.empty())
                return stringy;

            const string lowerString = toLowerCase(stringy);
            if (uncountable.find(lowerString) != uncountable.end()) {
                return lowerString;
            } 

            for (const auto& entry : irregular) {
                const regex pattern(entry.first, regex::icase);
                if (regex_search(lowerString, pattern)) {
                    return regex_replace(lowerString, pattern, entry.second);
                } 
            }

            for (const auto& entry : plural) {
                const regex pattern(entry.first, regex::icase);
                if (regex_search(lowerString, pattern)) {
                    return regex_replace(lowerString, pattern, entry.second);
                }
            }

            for (const auto& entry : plural_nos) {
                const regex pattern(entry.first, regex::icase);
                if (regex_search(lowerString, pattern)) {
                    return regex_replace(lowerString, pattern, entry.second);
                }
            }

            return lowerString;
        }

        static string singularize(const string& stringy) {
            if (stringy.empty())
                return stringy;

            const string lowerString = toLowerCase(stringy);
            if (uncountable.find(lowerString) != uncountable.end()) {
                return stringy;
            }

            for (const auto& entry : irregular) {
                const regex pattern(entry.first, regex::icase);
                if (regex_search(stringy, pattern)) {
                    return regex_replace(stringy, pattern, entry.second);
                }
            }

            for (const auto& entry : singular) {
                const regex pattern(entry.first, regex::icase);
                if (regex_search(stringy, pattern)) {
                    return regex_replace(stringy, pattern, entry.second);
                }
            }

            return stringy;
        }

    private:
        static string toLowerCase(const string& str) {
            string lowerStr = str;
            for (char& c : lowerStr) {
                c = tolower(c);
            }
            return lowerStr;
        }

        static map<string, string> plural;
        static map<string, string> plural_nos;
        static map<string, string> singular;
        static unordered_map<string, string> irregular;
        static unordered_map<string, bool> uncountable;
};

#endif /* INFLECT_H */
