// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string>& rec_help(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string word, std::set<std::string>& output);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> output;
    std::string word = "";
    return rec_help(in, floating, dict, word, output);
}

// Define any helper functions here
std::set<std::string>& rec_help(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string word, std::set<std::string>& output){
    //Have full word
    if(in.size() == word.size()){
        //If not in dict -> end
        if(dict.find(word) == dict.end()){
            return output;
        }
        if(floating.size() != 0){
            return output;
        }
        //Otherwise all good
        output.insert(word);
        return output;
    }
    if(in.size() - word.size() < floating.size()){
        return output;
    }
    //If the current character is not '-' no need to itterate
    if(in[word.size()] != '-'){
        return rec_help(in, floating, dict, word+in[word.size()], output);
    }
    for(char i = 'a'; i <= 'z'; i++){
        std::string floating_copy = floating;
        if(floating_copy.find(i) != std::string::npos){
            floating_copy.erase(floating_copy.find(i), 1);
        }
        rec_help(in, floating_copy, dict, word+i, output);
    }
    return output;
}