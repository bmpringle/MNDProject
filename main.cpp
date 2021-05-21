#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

class Quote {
    public:
        Quote(std::string quote, std::string speaker, std::string listener, std::string reasoning) : quote(quote), speaker(speaker), listener(listener), reasoning(reasoning) {

        }

        std::string getQuote() {
            return quote;
        }

        std::string getSpeaker() {
            return speaker;
        }

        std::string getListener() {
            return listener;
        }

        std::string getReasoning() {
            return reasoning;
        }

    private:
        std::string quote;
        std::string speaker;
        std::string listener;
        std::string reasoning;
};

void readQuotesFromFile(std::vector<Quote>& quotes) {
    const std::string filename = "quotes.txt";

    std::fstream fs = std::fstream(filename);

    std::string linebuffer;
    while(std::getline(fs, linebuffer)) {
        linebuffer.erase(std::remove(linebuffer.begin(), linebuffer.end(), '\n'), linebuffer.end());
        linebuffer.erase(std::remove(linebuffer.begin(), linebuffer.end(), '\r'), linebuffer.end());

        int sindex = 0;
        while(sindex < linebuffer.size() - 1) {
            if(linebuffer.at(sindex) == '\\') {
                if(linebuffer.at(sindex + 1) == 'n') {
                    linebuffer.erase(linebuffer.begin() + sindex);
                    linebuffer.at(sindex) = '\n';
                }
            }
            ++sindex;
        }

        std::string quote;
        std::string speaker;
        std::string listener;
        std::string reasoning;
        int i = 0;

        std::stringstream ss = std::stringstream(linebuffer);
        std::string linebuffer2;
        while(std::getline(ss, linebuffer2, '|')) {
            bool brk = false;

            switch(i) {
                case 0:
                    quote = linebuffer2;
                    ++i;
                    break;
                case 1:
                    speaker = linebuffer2;
                    ++i;
                    break;
                case 2:
                    listener = linebuffer2;
                    ++i;
                    break;
                case 3:
                    reasoning = linebuffer2;
                    ++i;
                    break;
                case 4:
                    brk = true;
                    break;
            }
            
            if(brk) {
                break;
            }
        }
        quotes.push_back(Quote(quote, speaker, listener, reasoning));
    }
}

void practiceQuotes(std::vector<Quote>& quotes) {
    std::string flushstring;

    std::getline(std::cin, flushstring); //flush the cin buffer
    
    std::cout << "When presented with a quote, enter a name like this:\nSnug\nEnter the name of the character as it appears in the book." << std::endl; 
    std::cout << "When you want to exit, just type exit" << std::endl;
    while(true) {  
        int random = rand() % quotes.size();
        Quote& quote = quotes.at(random);

        std::cout << "The quote is:" << std::endl;
        std::cout << quote.getQuote() << std::endl;

        std::string guessedSpeaker;
        std::string guessedListener;

        std::cout << "Who is the speaker?" << std::endl;

        std::getline(std::cin, guessedSpeaker);

        if(guessedSpeaker == "exit") {
            break;
        }

        std::cout << "Who is the listener?" << std::endl;

        std::getline(std::cin, guessedListener);

        if(guessedListener == "exit") {
            break;
        }

        if(guessedSpeaker == quote.getSpeaker()) {
            std::cout << "You were right! The speaker was " << guessedSpeaker << std::endl;
        }else {
            std::cout << "You were wrong. The speaker was " << quote.getSpeaker() << " not " << guessedSpeaker << std::endl;
        }

        if(guessedListener == quote.getListener()) {
            std::cout << "You were right! The listener was " << guessedListener << std::endl;
        }else {
            std::cout << "You were wrong. The listener was " << quote.getListener() << " not " << guessedListener << std::endl;
        }
    }
}

int main() {
    srand(time(NULL));

    std::vector<Quote> quotes = std::vector<Quote>();

    readQuotesFromFile(quotes);

    std::cout << "This program can be used to practice figuring out who said a specific line to whom in A Midsummer Night's Dream" << std::endl;

    while(true) {
        std::cout << "Enter a number to choose:" << std::endl;
        std::cout << "1. Start Practicing Quotes" << std::endl;
        std::cout << "2. Exit" << std::endl;

        std::string input;
        std::cin >> input;

        if(input != "1" && input != "2") {
            std::cout << "You didn't enter a valid option, try again." << std::endl;
        }else {
            if(input == "1") {
                practiceQuotes(quotes);
                return 0;
            }else {
                return 0;
            }
        }
    }
}