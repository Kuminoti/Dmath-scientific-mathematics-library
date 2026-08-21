#include"../include/Types/StringHelper.hpp"


bool Dmath::StringHelper::exsitsIn(const std::string& mainString, const std::string& find){
    bool exsits = false;

    size_t foundAt = mainString.find(find);
    if(foundAt != std::string::npos){
        exsits = true;
    }

    return exsits;
}

bool Dmath::StringHelper::exsitsInC(const std::string& mainString, const char& find){
    bool exsits = false;

    size_t foundAt = mainString.find(find);
    if(foundAt != std::string::npos){
        exsits = true;
    }

    return exsits;
}


bool Dmath::StringHelper::isNumeric(const std::string& str) {
    std::string cleaned;
    
    // Entferne Leerzeichen
    for (char c : str) {
        if (!std::isspace(c)) {
            cleaned += c;
        }
    }

    if (cleaned.empty()) return false;

    bool hasDecimal = false;
    bool hasDigit = false;
    size_t start = 0;

    // Prüft negatives Vorzeichen am Anfang
    if (cleaned[0] == '-') {
        if (cleaned.length() == 1) return false; // Nur "-" ist ungültig
        start = 1;
    }

    for (size_t i = start; i < cleaned.length(); ++i) {
        if (std::isdigit(cleaned[i])) {
            hasDigit = true;
        } else if (cleaned[i] == '.') {
            if (hasDecimal) return false; // Mehr als ein Punkt ist ungültig
            hasDecimal = true;
        } else {
            return false; // Ungültiges Zeichen gefunden
        }
    }

    return hasDigit; // Mindestens eine Ziffer muss enthalten sein
}



std::string Dmath::StringHelper::getInBrackets(const std::string& s) {

    static const std::unordered_map<char, char> brackets{
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {'<', '>'}
    };

    if (s.size() < 2)
        throw std::invalid_argument("String too short");

    char open = s.front();

    // C++17 replacement for contains()
    auto it = brackets.find(open);
    if (it == brackets.end())
        throw std::invalid_argument("No opening bracket");

    char close = it->second;

    int depth = 0;
    size_t start = std::string::npos;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (c == open) {
            if (depth == 0)
                start = i + 1;
            ++depth;
        }
        else if (c == close) {
            --depth;
            if (depth == 0)
                return s.substr(start, i - start);
        }
        else {
            // reject mismatched brackets
            if (brackets.find(c) != brackets.end() ||
                std::any_of(brackets.begin(), brackets.end(),
                    [c](const auto& p) { return p.second == c; }))
            {
                throw std::invalid_argument("Mismatched brackets");
            }
        }
    }

    throw std::invalid_argument("Unclosed bracket");
}

std::vector<Dmath::Scalar>
Dmath::StringHelper::getNumbersInBrackets( std::string input){
   
    std::vector<Dmath::Scalar> numbers;


    input = this->extractFromTo(input,'(',')');
    
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {

        // Leerzeichen am Anfang/Ende entfernen
        const auto first = token.find_first_not_of(" \t\n\r");
        const auto last  = token.find_last_not_of(" \t\n\r");

        if (first == std::string::npos)
            throw std::invalid_argument(
                "Empty number in brackets: " + input
            );

        token = token.substr(first, last - first + 1);

        try {
            size_t pos = 0;
            Dmath::Scalar value = std::stod(token, &pos);

            // Sicherstellen, dass wirklich der komplette Token
            // eine Zahl war.
            if (pos != token.size()) {
                throw std::invalid_argument(
                    "Invalid number: " + token
                );
            }

            numbers.push_back(value);
        }
        catch (const std::exception&) {
            throw std::invalid_argument(
                "Invalid number in brackets: " + token
            );
        }
    }

    return numbers;
}




std::string Dmath::StringHelper::extractFromTo(const std::string& mainString, char start, char end) {
    std::string stringExtract = "";
    if(!this->exsitsInC(mainString, start) || !this->exsitsInC(mainString, end)){
        return "";
    }
    size_t startPos = mainString.find(start); // Position des Startzeichens
    size_t endPos = mainString.find(end, startPos + 1); // Position des Endzeichens nach Start

    stringExtract = mainString.substr(startPos + 1, endPos - startPos - 1);
    return stringExtract;
}


std::string Dmath::StringHelper::extractWords(
    const std::string& mainString,
    const std::string& start,
    const std::string& end)
{
    if (!this->exsitsIn(mainString, start) ||
        !this->exsitsIn(mainString, end))
    {
        return "";
    }

    size_t startPos = mainString.find(start);
    size_t endPos = mainString.find(end, startPos + start.size());

    if (endPos == std::string::npos)
        return "";

    // Alles zwischen start und end
    size_t contentStart = startPos + start.size();

    std::string result =
        mainString.substr(
            contentStart,
            endPos - contentStart
        );

    // Whitespace und ':' am Anfang/Ende entfernen
    size_t first = result.find_first_not_of(" \t\n\r:");
    size_t last  = result.find_last_not_of(" \t\n\r:");

    if (first == std::string::npos)
        return "";

    return result.substr(first, last - first + 1);
}

std::vector<std::string>
Dmath::StringHelper::extractAfter(
    const std::string& mainString,
    char symbol)
{
    std::vector<std::string> sentences;
    std::string sentence;

    for (char c : mainString)
    {
        sentence += c;

        if (c == symbol)
        {
            // Führende Whitespaces entfernen
            const size_t start =
                sentence.find_first_not_of(" \t\r\n");

            // Nachlaufende Whitespaces entfernen
            const size_t end =
                sentence.find_last_not_of(" \t\r\n");

            if (start != std::string::npos)
            {
                sentences.push_back(
                    sentence.substr(start, end - start + 1)
                );
            }

            sentence.clear();
        }
    }

    // Falls am Ende kein ';' vorhanden war
    if (!sentence.empty())
    {
        const size_t start =
            sentence.find_first_not_of(" \t\r\n");

        const size_t end =
            sentence.find_last_not_of(" \t\r\n");

        if (start != std::string::npos)
        {
            sentences.push_back(
                sentence.substr(start, end - start + 1)
            );
        }
    }

    return sentences;
}

std::string Dmath::StringHelper::extractFirstWord(const std::string& str) {
        std::string result;

    for (char c : str) {
        if (c == ' ' || c == '.' || c == ',' || c == ';') break; // Stoppe bei Leerzeichen oder Punkt
        result += c;
    }

    return result;
}

std::vector<std::string> Dmath::StringHelper::extractSentences(const std::string& mainString) {
    std::vector<std::string> sentences;
    std::string sentence;

    for (size_t i = 0; i < mainString.size(); ++i) {
        char c = mainString[i];
        sentence += c; 

        if (c == '.' || c == '?' || c == '!') {
            size_t start = sentence.find_first_not_of(" \t\n");
            size_t end = sentence.find_last_not_of(" \t\n");

            if (start != std::string::npos) {
                sentences.push_back(sentence.substr(start, end - start + 1));
            }

        sentence.clear(); 
        }
         if (!sentence.empty()) {
        size_t start = sentence.find_first_not_of(" \t\n");
        size_t end = sentence.find_last_not_of(" \t\n");

        if (start != std::string::npos) {
            sentences.push_back(sentence.substr(start, end - start + 1));
        }
    }

    return sentences;
    }

    if (!sentence.empty()) {
        size_t start = sentence.find_first_not_of(" \t\n");
        size_t end = sentence.find_last_not_of(" \t\n");

        if (start != std::string::npos) {
            sentences.push_back(sentence.substr(start, end - start + 1));
        }
    }

    return sentences;
}


std::string Dmath::StringHelper::replaceWordExact(const std::string& input, const std::string& target, const std::string& replacement) {
    std::string output;
    std::string currentWord;
    std::string delimiters = " +-/*!^%()$=[]";
    
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        // Trennzeichen beenden ein Wort
        if (delimiters.find(c) != std::string::npos) {
            if (!currentWord.empty()) {
                // Prüfe, ob das Wort ersetzt werden muss
                if (currentWord == target) {
                    output += replacement;
                } else {
                    output += currentWord;
                }
                currentWord.clear();
            }

            // Sonderzeichen zählen als eigenes Wort (werden direkt angehängt)
            output += c;
        } else {
            // Buchstaben/Ziffern/etc. -> Teil eines Wortes
            currentWord += c;
        }
    }

    // Letztes Wort verarbeiten
    if (!currentWord.empty()) {
        if (currentWord == target) {
            output += replacement;
        } else {
            output += currentWord;
        }
    }

    return output;
}

std::string Dmath::StringHelper::toUpper(const std::string& mainString) {

    std::string result = mainString;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return result;
}

std::string Dmath::StringHelper::toLower(const std::string& mainString) {
    std::string result = mainString;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}

size_t Dmath::StringHelper::howOften(const std::string& mainString, const std::string& find) {
    size_t count = 0;
    size_t pos = mainString.find(find); // Erste Position von "find" suchen

    // Wiederhole, solange "find" im String gefunden wird
    while (pos != std::string::npos) {
        ++count; // Zähler erhöhen
        pos = mainString.find(find, pos + find.length()); // Suche ab der nächsten Position
    }

    return count;
}

Dmath::Duo<std::string, std::string> Dmath::StringHelper::splitString(std::string mainString, size_t position){
    Dmath::Duo<std::string, std::string> mainDuo("-1","-1"); //String of -1 reperesents an  empty value or an errorvalue
    
    if(position < mainString.size()){
        std::string firstPart = mainString.substr(0,position);
        std::string otherPart = mainString.substr(position);
        
        mainDuo.one = firstPart;
        mainDuo.two = otherPart;
    }


    return mainDuo;
}


std::string  Dmath::StringHelper::getFileExtension(const std::string& filename) {
    size_t pos = filename.rfind('.');
    if (pos == std::string::npos || pos == filename.length() - 1) {
        // Kein Punkt gefunden oder Punkt am Ende → keine Extension
        return " ";  // wie gewünscht: " " für kein Format
    }
    return filename.substr(pos);  // inkl. Punkt, z.B. ".exe"
}

std::string Dmath::StringHelper::fixDuplicate(const std::string& duplicate){
    // Bereits vorhandenes _N am Ende erkennen
    size_t underscore = duplicate.rfind('_');

    if (underscore != std::string::npos &&
        underscore + 1 < duplicate.size()){
        std::string suffix = duplicate.substr(underscore + 1);

        // Prüfen, ob hinter '_' ausschließlich Ziffern stehen
        bool isNumber = !suffix.empty();

        for (char c : suffix){
            if (!std::isdigit(static_cast<unsigned char>(c)))
            {
                isNumber = false;
                break;
            }
        }

        if (isNumber)
        {
            std::string base = duplicate.substr(0, underscore);

            unsigned long number = std::stoul(suffix);
            ++number;

            return base + "_" + std::to_string(number);
        }
    }

    // Noch keine Duplikatnummer vorhanden
    return duplicate + "_1";
}


std::string Dmath::StringHelper::fixDuplicates(std::string name, std::vector<std::string> existingNames){
        // Name existiert noch nicht
        if (std::find(existingNames.begin(), existingNames.end(), name) == existingNames.end()){
            return name;
        }

        // Name existiert -> _1, _2, _3, ...
        size_t counter = 1;

        while (true)
        {
            std::string candidate = name + "_" + std::to_string(counter);

            if (std::find(existingNames.begin(), existingNames.end(), candidate)
                == existingNames.end())
            {
                return candidate;
            }

            ++counter;
        }
        return "";
    }

std::string Dmath::StringHelper::removeWhitespace(const std::string& str){
    std::string result;
    result.reserve(str.size()); // Performance-Optimierung

    for (char c : str)
        if (!std::isspace(static_cast<unsigned char>(c)))
            result.push_back(c);

    return result;
}


size_t Dmath::StringHelper::getFirstTopLevelPosition(const std::string& str, char target) {
    int depth = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];

        if (c == '(' || c == '[' || c == '{') depth++;
        else if (c == ')' || c == ']' || c == '}') depth--;
        else if (c == target && depth == 0)
            return i;
    }

    return std::string::npos;
}