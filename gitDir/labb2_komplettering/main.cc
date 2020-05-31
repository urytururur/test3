#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>

using namespace std;

std::vector<string>::iterator getLongestWord(vector<string> & words);

ostream& operator<<(std::ostream &os, std::pair<std::string, int> const &v);

int main(int argc, char *argv[])
{
    vector<string> args {argv, argv + argc};

    ifstream inFileStream{args.at(1)};
    std::vector<string> words{std::istream_iterator<string>{inFileStream}, std::istream_iterator<string>{}};

    stringstream ss{};

        transform(words.begin(), words.end(), words.begin(), [&words, &ss](string word)
        {
            auto it {find_if(word.begin(),word.end(),[](char & c){return isalpha(c);})};
            
            if ( any_of(word.begin(), it, [](char c){return c != '\"' && c != '(';}))
            {
                return "";
            }
            return word.c_str();
        });

        transform(words.begin(), words.end(), words.begin(), [&words, &ss](string word)
        {
            auto it {find_if(make_reverse_iterator(word.end()),make_reverse_iterator(word.begin()),[](char & c){return isalpha(c);})};
            
            if ( any_of(make_reverse_iterator(word.end()), it, [](char c){return c != '"' && c != '\'' && c != ')' && c != '!' && c != '?' && c != ';' && c != ',' && c != ':' && c != '.';}))
            {
                return "";
            }
            return word.c_str();
        });


        transform(words.begin(), words.end(), words.begin(), [](string word)
        {   
            auto firstLetter = find_if(word.begin(), word.end(), [](char & c)
            {
                return isalpha(c);
            });
            auto lastLetter = find_if(make_reverse_iterator(word.end()),make_reverse_iterator(word.begin()),[](char & c)
            {
                return isalpha(c);
            });
            if ( any_of(lastLetter, make_reverse_iterator(firstLetter), [](char c){return !isalpha(c) && c != '-' && c != '\'';}))
            {
                return "";
            }
            return word.c_str();
        });
    
        //TA BORT SKRÄP I SLUTET
        transform(words.begin(), words.end(), words.begin(), [&words](string word)
        {
            //ERSÄTTER ALLA SKRÄP-TECKEN MED MELLANRUM DÄR VI TAR BORT TECKEN
            auto current{word.begin()};
            auto it{find_if(word.begin(),word.end(),[&current,&word](char & c)
                {
                    if(c == '-')
                    {
                        //ERSÄTTER INTE '-' OM BOKSTÄVER BREVID
                        if(isalpha(*prev(current)) && isalpha(*next(current)))
                        {
                            ++current;
                            return false;
                        }
                        return true;
                    }
                    else if(c == '\'')
                    {
                        auto lastLetter = find_if(make_reverse_iterator(word.end()),make_reverse_iterator(word.begin()),[](char & c)
                        {
                            return isalpha(c);
                        });
                        if(*lastLetter == 's')
                        {
                            if(*next(lastLetter) == '\'')
                            {
                                return false;
                            }
                            return true;
                        }
                    }
                    ++current;
                    return false;
                }
            )};
            if (it != word.end())
            {
                return "";
            }
            return word.c_str();
        });

    transform(words.begin(), words.end(), words.begin(), [](string word)
        {
            auto it = remove_if(word.begin(), word.end(), [](char& c)
                {
                    if (c != '-' && c != '\'' && !isalpha(c))
                    {
                        return true;
                    }
                    return false;
                });
            word.erase(it,word.end());

            string tmp{"'s"};
            word.erase(search(word.begin(), word.end(), tmp.begin(), tmp.end()), word.end());
            
            return word;
        }
    );

    transform(words.begin(), words.end(), words.begin(), [](string word)
    {
        transform(word.begin(),word.end(), word.begin(),[](char & c)
        {
            if(isupper(c))
            {
                return static_cast<char>(c + 32);
            }
            return c;
        });
    
    return word.c_str();
    });

    auto it = remove_if(words.begin(), words.end(), [](string & word)
    {
        return word == "" || word.size() < 3;
    });

    words.erase(it,words.end());

    try
    {
        if(args.at(2) == "-a")
        {
            
            auto longestWord{getLongestWord(words)};

            transform(words.begin(), words.end(), words.begin(), [&words, &longestWord](string & word)
            {

                word.insert(word.end(),longestWord->size() - word.size(),' ');

                return word;
            });

            //VECTOR AV PAR
            vector<pair<string, int>> pairs{words.size()};
            
            transform(words.begin(), words.end(), pairs.begin(), [&words](string & word)
            {
                return pair<string, int>(word, count(words.begin(), words.end(), word));
            });

            //VECTOR AV PAR TILL MAP
            map<string, int> m{pairs.begin(), pairs.end()};

            std::copy( m.begin(), m.end(), ostream_iterator<pair<string, int>>(cout, "\n") );
        }
        else if(args.at(2) == "-f")
        {
            auto longestWord{getLongestWord(words)};

            transform(words.begin(), words.end(), words.begin(), [&words,&longestWord](string & word)
            {
                word.insert(word.begin(),longestWord->size() - word.size(),' ');

                return word;
            });

            //VECTOR AV PAR
            vector<pair<string, int>> pairs{words.size()};
            
            transform(words.begin(), words.end(), pairs.begin(), [&words](string & word)
            {
                return pair<string, int>(word, count(words.begin(), words.end(), word));
            });

            //VECTOR AV PAR TILL MAP
            sort(pairs.begin(), pairs.end(), [](pair<string,int> pair1, pair<string,int> pair2)
            {
                return pair1.second > pair2.second;
            });

            pairs.erase(unique(pairs.begin(),pairs.end()), pairs.end());

            vector<pair<string, int>> v{pairs.begin(),pairs.end()};

            std::copy( v.begin(), v.end(), ostream_iterator<pair<string, int>>(cout , "\n") );
        }
        else if(args.at(2) == "-o")
        {
            int maxRowLength{stoi(args.at(3))};
            for_each(words.begin(), words.end(), [&maxRowLength, &args](string & word)
            {
                if(word.size() < maxRowLength)
                {
                    cout << word << " ";
                    maxRowLength -= (word.size() + 1);
                }
                else
                {
                    cout << '\n';
                    maxRowLength = stoi(args.at(3));
                    if(!(word.size() >= maxRowLength))
                    {
                        cout << word << " ";
                        maxRowLength -= (word.size() + 1);
                    }
                }
            });
            cout << endl;
        }
        else
        {
            cout << "OLILTIG FLAGGA." << endl;
        }
    }
    catch(const std::exception& e)
    {
        cout << "OLILTIGT ARGUMENT." << endl;
    }
    
}

std::vector<string>::iterator getLongestWord(vector<string> & words)
{
    auto longestWord{words.begin()};
    auto it{words.begin()};
    transform(words.begin(), words.end(), words.begin(), [&words, &longestWord, &it](string & word)
    {
        if(longestWord->size() < word.size())
        {
            longestWord = it;
        }
        ++it;
        return word;
    });
    return longestWord;
}

namespace std
{
    ostream& operator<<(ostream &os, pair<string, int> const &v) {
        os << v.first << setw(3) << v.second;
        return os;
    }
}




































































































