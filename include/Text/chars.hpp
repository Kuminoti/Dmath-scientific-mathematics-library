#pragma once

#ifndef DMATH_CHARS_HPP
#define DMATH_CHARS_HPP

#include"../Types/dMap.hpp"

NAMESPACESTART


//Тhe (serbian) cyrillic alphabet (Yes I can read that lol)
//љњертзуиопшђжасдфгхјклчћѕџцвбнм 
//ЉЊЕРТЗУИОПШЂЖАСДФГХЈКЛЧЋЅЏЦВБНМ
static Dmath::MapD<std::string, std::string> CyrillicLetters = {
    {"A" , "А"}, {"a" , "а"},
    {"B" , "Б"}, {"b" , "б"},
    {"V" , "В"}, {"v" , "в"},
    {"G" , "Г"}, {"g" , "г"},
    {"D" , "Д"}, {"d" , "д"},
    {"Đ" , "Ђ"}, {"đ" , "ђ"},
    {"E" , "Е"}, {"e" , "е"},
    {"Ž" , "Ж"}, {"ž" , "ж"},
    {"Z" , "З"}, {"z" , "з"},
    {"I" , "И"}, {"i" , "и"},
    {"J" , "Ј"}, {"j" , "ј"},
    {"K" , "К"}, {"k" , "к"},
    {"L" , "Л"}, {"l" , "л"},
    {"Lj", "Љ"}, {"lj", "љ"},
    {"M" , "М"}, {"m" , "м"},
    {"N" , "Н"}, {"n" , "н"},
    {"Nj", "Њ"}, {"nj", "њ"},
    {"O" , "О"}, {"o" , "о"},
    {"P" , "П"}, {"p" , "п"},
    {"R" , "Р"}, {"r" , "р"},
    {"S" , "С"}, {"s" , "с"},
    {"T" , "Т"}, {"t" , "т"},
    {"Ć" , "Ћ"}, {"ć" , "ћ"},
    {"U" , "У"}, {"u" , "у"},
    {"F" , "Ф"}, {"f" , "ф"},
    {"H" , "Х"}, {"h" , "х"},
    {"C" , "Ц"}, {"c" , "ц"},
    {"Č" , "Ч"}, {"č" , "ч"},
    {"Dž", "Џ"}, {"dž", "џ"},
    {"Š" , "Ш"}, {"š" , "ш"}
};

//The Greek alphabet Yes I can read this too lol :)
static Dmath::MapD<std::string, std::string> GreekLetters = {

    {"alpha",   "α"}, {"Alpha",   "Α"},
    {"beta",    "β"}, {"Beta",    "Β"},
    {"gamma",   "γ"}, {"Gamma",   "Γ"},
    {"delta",   "δ"}, {"Delta",   "Δ"},
    {"epsilon", "ε"}, {"Epsilon", "Ε"},
    {"zeta",    "ζ"}, {"Zeta",    "Ζ"},
    {"eta",     "η"}, {"Eta",     "Η"},
    {"theta",   "θ"}, {"Theta",   "Θ"},
    {"iota",    "ι"}, {"Iota",    "Ι"},
    {"kappa",   "κ"}, {"Kappa",   "Κ"},
    {"lambda",  "λ"}, {"Lambda",  "Λ"},
    {"mu",      "μ"}, {"Mu",      "Μ"},
    {"nu",      "ν"}, {"Nu",      "Ν"},
    {"xi",      "ξ"}, {"Xi",      "Ξ"},
    {"omicron", "ο"}, {"Omicron", "Ο"},
    {"pi",      "π"}, {"Pi",      "Π"},
    {"rho",     "ρ"}, {"Rho",     "Ρ"},
    {"sigma",   "σ"}, {"Sigma",   "Σ"},
    {"tau",     "τ"}, {"Tau",     "Τ"},
    {"upsilon", "υ"}, {"Upsilon", "Υ"},
    {"phi",     "φ"}, {"Phi",     "Φ"},
    {"chi",     "χ"}, {"Chi",     "Χ"},
    {"psi",     "ψ"}, {"Psi",     "Ψ"},
    {"omega",   "ω"}, {"Omega",   "Ω"}
};
   
   // → ∀ ∃ ∄ ∅ ∈ ∉ ∛ ∜ ∬ ∯ ∩ ∟ ∰ ∭ ∧ ∨ ∫ ∮ ∵ ∶ ∴ ≔ ≙ ≡ ⊆ ⊇ ⊂

static Dmath::MapD<std::string, std::string> SpecialChars = {
    {"infinity",    u8"∞"},
    
    {"integral",    u8"∫"},
    {"loopIntegral", u8"∮"},
    {"doubleIntegral",  u8"∬"},
    {"tripleIntegral",  u8"∭"},
    {"surfaceIntegral", u8"∯"},

    {"proportional",    u8"∝"},

    {"derivative", "d/dx"}
    {"partial",     u8"∂"},
    {"nabla",       u8"∇"},

    {"sqrt",        u8"√"},
    {"cbrt",        u8"∛"},
    {"fourthRoot",  u8"∜"},

    {"sum",         u8"∑"},
    {"product",     u8"∏"},

    {"rightarrow",  u8"→"},

    {"forall",      u8"∀"},
    {"exists",      u8"∃"},
    {"notExists",   u8"∄"},

    {"emptySet",    u8"∅"},
    {"element",     u8"∈"},
    {"notElement",  u8"∉"},

    {"intersection", u8"∩"},
    {"angle",        u8"∟"},

    {"logicalAnd",  u8"∧"},
    {"logicalOr",   u8"∨"},

    {"therefore",   u8"∴"},
    {"because",     u8"∵"},
    {"ratio",       u8"∶"},

    {"assign",      u8"≔"},
    {"corresponds", u8"≙"},
    {"equivalent",  u8"≡"},

    {"subset",      u8"⊂"},
    {"subsetEq",    u8"⊆"},
    {"superset",    u8"⊃"},
    {"supersetEq",  u8"⊇"},

    {"geq",         u8"≥"},
    {"leq",         u8"≤"},
    {"neq",         u8"≠"},
    {"approx",      u8"≈"},

    {"plusminus",   u8"±"},
    {"times",       u8"×"},
    {"divide",      u8"÷"},
    {"degree",      u8"°"}
};





NAMESPACEEND

#endif