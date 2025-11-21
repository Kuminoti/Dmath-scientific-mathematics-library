#pragma once

#ifndef D_MAP_HPP
#define D_MAP_HPP

#include "../macros.hpp"
#include"dataTypes.hpp"
#include<optional>
#include<mutex>
#include<initializer_list>

NAMESPACESTART
template <class typeOne, class typeTwo>
class MapD {
private:
    std::vector<Dmath::Duo<typeOne, typeTwo>> mapVec;

public:

    MapD() = default;

    MapD(std::initializer_list<Dmath::Duo<typeOne, typeTwo>> list) {
        for (const auto& p : list) {
            insert(p.one, p.two);   // oder push_back etc.
        }
    }

    // Methode zum parallelen Suchen eines Schlüssels
    std::optional<Dmath::Duo<typeOne, typeTwo>> findKey(typeOne key) {
        std::mutex mtx;
        std::optional<Dmath::Duo<typeOne, typeTwo>> result;
        bool found = false; // zeigt an, ob das Ergebnis bereits gefunden wurde

        auto searchFromFront = [&]() {
            for (size_t i = 0; i < mapVec.size(); i++) {
                std::lock_guard<std::mutex> lock(mtx);
                if (found) return; // Wenn bereits gefunden, abbrechen
                if (mapVec[i].one == key) {
                    result = mapVec[i];
                    found = true;
                    return;
                }
            }
        };

        auto searchFromBack = [&]() {
            for (size_t i = mapVec.size(); i-- > 0; ) {
                std::lock_guard<std::mutex> lock(mtx);
                if (found) return; // Wenn bereits gefunden, abbrechen
                if (mapVec[i].one == key) {
                    result = mapVec[i];
                    found = true;
                    return;
                }
            }
        };

        // Threads starten
        std::thread t1(searchFromFront);
        std::thread t2(searchFromBack);

        // Warten, bis beide Threads beendet sind
        t1.join();
        t2.join();

        return result; // Gibt das Ergebnis zurück, falls gefunden
    }


        std::optional<Dmath::Duo<typeOne, typeTwo>> findValue(typeTwo value) {
        std::mutex mtx;
        std::optional<Dmath::Duo<typeOne, typeTwo>> result;
        bool found = false;

        auto searchFromFront = [&]() {
            for (size_t i = 0; i < mapVec.size(); i++) {
                std::lock_guard<std::mutex> lock(mtx);
                if (found) return;
                if (mapVec[i].two == value) {
                    result = mapVec[i];
                    found = true;
                    return;
                }
            }
        };

        auto searchFromBack = [&]() {
            for (size_t i = mapVec.size(); i-- > 0; ) {
                std::lock_guard<std::mutex> lock(mtx);
                if (found) return;
                if (mapVec[i].two == value) {
                    result = mapVec[i];
                    found = true;
                    return;
                }
            }
        };

        std::thread t1(searchFromFront);
        std::thread t2(searchFromBack);
        t1.join();
        t2.join();

        return result;
    }

    // Methode, um den Wert basierend auf einem Schlüssel zu erhalten
    typeTwo getFromKey(typeOne key) {
        auto result = this->findKey(key);
        if (result) return result->two;
        throw std::runtime_error("Key not found.");
    }

    // Methode zum Hinzufügen eines neuen Schlüssel-Wert-Paars
    void insert(typeOne key, typeTwo value) {
        if (this->findKey(key)) {
            throw std::runtime_error("Duplicate key insertion attempted.");
        }
        mapVec.push_back(Dmath::Duo<typeOne, typeTwo>(key, value));
    }



    void update(typeOne key, typeTwo newValue) {
        for (auto& duo : mapVec) {
            if (duo.one == key) {
                duo.two = newValue;
                return;
            }
        }
        throw std::runtime_error("Key not found for update.");
    }

    inline void clear() {
        mapVec.clear();
    }

    size_t size(){
        return this->mapVec.size();
    }

    void remove(typeOne key) {
        auto it = std::remove_if(mapVec.begin(), mapVec.end(),
                                [key](const Dmath::Duo<typeOne, typeTwo>& duo) { return duo.one == key; });
        if (it != mapVec.end()) {
            mapVec.erase(it, mapVec.end());
        } else {
            throw std::runtime_error("Key not found for removal.");
        }
    }

    bool containsKey(typeOne key) const {
        for (const auto& duo : mapVec) {
            if (duo.one == key) return true;
        }
        return false;
    }

    bool containsValue(typeTwo value) const {
        for (const auto& duo : mapVec) {
            if (duo.two == value) return true;
        }
        return false;
    }
    
   Dmath::Duo<typeOne, typeTwo> operator[](size_t index) {
        if (index >= this->mapVec.size()) {
            throw std::out_of_range("Index out of range");
        }
        return this->mapVec[index];
    }


    template <typename T>
    bool contains() {
        return Dmath::contains_type_two<T, typeOne, typeTwo>::value;
    }
    
};


NAMESPACEEND
#endif //D_MAP_HPP