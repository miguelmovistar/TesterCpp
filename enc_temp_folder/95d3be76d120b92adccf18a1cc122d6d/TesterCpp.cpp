#include <iostream>
#include <pugixml.hpp>
#include <filesystem>
#include <unordered_map>
#include <functional>

using namespace std;
using namespace pugi;

// ENUMS
enum class FileStatus {created, modified, erased};

// LAS CLASES VAN PRIMERO
class FileWatcher {
private:
    bool bRuninng = true; // Nunca ocupa esta variable

    // Variables públicas
public:
    std::string path_to_watch;
    std::unordered_map<std::string, std::filesystem::file_time_type> _paths;

    // Constructor
    // Recorre el directorio en busca de archivos. Y por qué no solo apunta a uno y ya?
    FileWatcher(std::string path_to_watch) {
        for (auto& file : std::filesystem::recursive_directory_iterator(path_to_watch)) {
            _paths[file.path().string()] = std::filesystem::last_write_time(file);            
        }
    }

    //Método
    void start(const std::function<void(std::string, FileStatus)>& action) 
    {
        // Obtiene el primer archivo de la lista
        auto it = _paths.begin();

        // Checa si el archivo fue borrado
        while (it != _paths.end()) // Itera mientras no llegue al final de la lista
        {
            // Si no existe
            if (!std::filesystem::exists(it->first)) 
            {
                action(it->first, FileStatus::erased);
                it = _paths.erase(it);
            }
            else // Si existe
            {
                it++;
            }
        }

        // Checha si el archivo fue creado o modificado
        // Recorre el directorio en busca de archivos. Y por qué no solo apunta a uno y ya?
        for (auto& file : std::filesystem::recursive_directory_iterator(path_to_watch))
        {
            auto current_file_last_write_time = std::filesystem::last_write_time(file);

            if (!_paths.contains(file.path().string()))
            {
                _paths[file.path().string()] = current_file_last_write_time;
                action(file.path().string(), FileStatus::created); //File created
            }
            else
            {
                if (_paths[file.path().string()] != current_file_last_write_time)
                {
                    _paths[file.path().string()] = current_file_last_write_time;
                    action(file.path().string(), FileStatus::modified);
                }
            }
        }

    }
};


FileWatcher fileWatcher{ "C:\\CLEARX\\Config" };
xml_document configurationFile;

int main()
{
    std::cout << "Hello World!\n";
    std::cout << "Otra manera!\n" << std::endl;

    //configurationFile.load_file("C:\\CLEARX\\Config\\UserConfigV2.xml");
    if (!fileWatcher._paths.empty())
    {
        configurationFile.load_file(fileWatcher._paths.begin()->first.data());
    }
}

void GetConfigFile() 
{
    if (!fileWatcher._paths.empty()) 
    {
        configurationFile.load_file(fileWatcher._paths.begin()->first.data());
    }
}




