
/* File: DmathFile.cpp 
 * Header: DmathFile.hpp
*/




#include"../include/Types/DmathFile.hpp"





Dmath::Trio<std::string, std::string, std::string>
Dmath::functionData(const std::string& FunctionString){
    std::string funcName;
    std::string usedVar;
    std::string term;

    // remove spaces
    std::string s;
    for (char c : FunctionString)
        if (!std::isspace(static_cast<unsigned char>(c)))
            s += c;

    // split at '='
    size_t equalPos = s.find('=');
    if (equalPos == std::string::npos)
        throw std::invalid_argument("Function must contain '='");

    funcName = s.substr(0, equalPos);
    term     = s.substr(equalPos + 1);

    // find '(' and ')'
    size_t l = funcName.find('(');
    size_t r = funcName.find(')');

    if (l == std::string::npos || r == std::string::npos || r <= l + 1)
        throw std::invalid_argument("Invalid function signature");

    usedVar = funcName.substr(l + 1, r - l - 1);

    return { funcName, usedVar, term };
}





Dmath::DmathFile::DmathFile() {
    content = getDmathTemplate();
}


//
void Dmath::DmathFile::writeDmathBinary(const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    if (!out)
        throw std::runtime_error("Cannot open file for writing");

    // Magic header
    const char magic[5] = {'D','M','A','T','H'};
    out.write(magic, sizeof(magic));

    // Version
    uint16_t version = 1;
    out.write(reinterpret_cast<char*>(&version), sizeof(version));

    // String length
    uint32_t length = static_cast<uint32_t>(this->content.size());
    out.write(reinterpret_cast<char*>(&length), sizeof(length));

    // String bytes
    out.write(this->content.data(), length);
}


void Dmath::DmathFile::addFunction(std::string FunctionString){
    //{ funcName, used var, data}
    Dmath::Trio<std::string, std::string, std::string> FunctionData = functionData(FunctionString);
    std::string mainString = "Function: " + FunctionData.one   + "<" + FunctionData.three + ">;";
    insertIntoBlock(mainString);
}



std::string Dmath::DmathFile::getContent() const {
    return content;
}




void Dmath::DmathFile::saveToFile(const std::string& path) const {
    std::ofstream out(path);
    if (!out)
        throw std::runtime_error("Could not open file: " + path);
    out << content;
}





std::string Dmath::DmathFile::getDmathTemplate() const {
    return "<Dmath::Version_" + std::string(FILE_VERSION) +
            "[CARTESIAN3D, CARTESIAN2D]>\n"
            "<{\n}>";
}


std::string Dmath::DmathFile::getFunctionString (std::string line){

    // Muss mit "Function:" beginnen
    if (line.find("Function:") != 0)
        std::cerr << "Not a function line" << std::endl;

    // Positionen
    size_t nameStart = line.find(':') + 1;
    size_t exprStart = line.find('<');
    size_t exprEnd   = line.find('>');

    if (exprStart == std::string::npos || exprEnd == std::string::npos)
        std::cerr << "Malformed function line" << std::endl;

    // f(x)
    std::string functionHead = line.substr(nameStart, exprStart - nameStart);
    trim(functionHead);

    // Ausdruck
    std::string expression = line.substr(exprStart + 1, exprEnd - exprStart - 1);
    trim(expression);

    // Ergebnis
    return functionHead + " = " + expression;
}



void Dmath::DmathFile::insertIntoBlock(const std::string& text) {

    size_t open = content.find("<{");
    size_t close = content.find("}>");

    if (open == std::string::npos || close == std::string::npos || close <= open)
        throw std::runtime_error("Invalid Dmath template structure");

    open += 2; // after <{

    content.insert(open, "\n" + text);
}



std::string Dmath::DmathFile::readDmathBinary(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in)
        throw std::runtime_error("Cannot open file for reading");

    // Magic header
    char magic[5];
    in.read(magic, sizeof(magic));
    if (std::string(magic, 5) != "DMATH")
        throw std::runtime_error("Invalid DMATH file");

    // Version
    uint16_t version;
    in.read(reinterpret_cast<char*>(&version), sizeof(version));

    // String length
    uint32_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));

    // String data
    std::string content(length, '\0');
    in.read(content.data(), length);

    return content;
}




Dmath::DmathFile Dmath::DmathFile::loadBinary(const std::string &path){
    Dmath::DmathFile newFile;
    std::string binContent = readDmathBinary(path);
    newFile.setContent(binContent);
    return newFile;
}

Dmath::DmathFile Dmath::DmathFile::loadTextFile(const std::string &path){
    Dmath::DmathFile newFile;
    std::string fileType = this->strH.getFileExtension(path);

    //Check for binary files
    if(fileType == "Dmath" || fileType == ".Dmath"){
        return this->loadBinary(path);
    }
    //check for textfiles
    else if(fileType == "dmath" || fileType == ".dmath"){
     
    

    // Open the file using ifstream
    std::ifstream file(path);

    // confirm file opening
    if (!file.is_open()) {
        // print error message and return
        std::cerr << "Failed to open file: " << path << std::endl;

        //return Emptyfile
        return newFile;
    }

    std::string content = "";
    std::string line;
    while (getline(file, line)) {
        content += line + "\n";
    }

    // Close the file
    file.close();

    newFile.setContent(content);
    
    return newFile;
    }

    std::cerr << "Error wrong file! returning empty damth-file" << std::endl;
    return newFile;
}
