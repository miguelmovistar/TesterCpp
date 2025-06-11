#include <iostream>
#include <pugixml.hpp>
#include <filesystem>
#include <unordered_map>
#include <functional>

#include <thread>     // Para std::this_thread::sleep_for
#include <chrono>     // Para std::chrono

using namespace std;
using namespace pugi;

enum class FileStatus { Creado, Eliminado, Modificado };

class FileWatcher {
public:
    std::string path_to_watch;
    std::unordered_map<std::string, std::filesystem::file_time_type> _paths;

    FileWatcher(std::string path_to_watch) : path_to_watch(path_to_watch) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path_to_watch)) {
            if (std::filesystem::is_regular_file(entry)) {
                _paths[entry.path().string()] = std::filesystem::last_write_time(entry);
            }
        }
    }

    // Método para verificar cambios
    void check_for_changes(std::function<void(const std::string&, FileStatus)> callback) {
        
        // 1. Verificar archivos modificados o eliminados
        std::unordered_map<std::string, std::filesystem::file_time_type> current_paths = _paths;

        for (auto it = current_paths.begin(); it != current_paths.end(); ) {
            const std::string& path = it->first;
            if (!std::filesystem::exists(path)) {
                callback(path, FileStatus::Eliminado);
                _paths.erase(path);
                it = current_paths.erase(it);
            }
            else {
                auto last_write_time = std::filesystem::last_write_time(path);
                if (last_write_time != _paths[path]) {
                    callback(path, FileStatus::Modificado);
                    _paths[path] = last_write_time;
                }
                ++it;
            }
        }

        // 2. Verificar archivos nuevos
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path_to_watch)) {
            if (std::filesystem::is_regular_file(entry)) {
                const std::string& path = entry.path().string();
                if (_paths.find(path) == _paths.end()) {
                    // Archivo nuevo
                    callback(path, FileStatus::Creado);
                    _paths[path] = std::filesystem::last_write_time(entry);
                }
            }
        }
    }
};


FileWatcher fileWatcher{"C:\\CLEARX\\Config"};
xml_document configurationFile;

int main()
{
   /* std::cout << "Hello World!\n";
    std::cout << "Otra manera!\n" << std::endl;*/

    while (true) {
        fileWatcher.check_for_changes([&](const std::string& path, FileStatus status) {
            std::cout << "Archivo " << path << " ";
            if (status == FileStatus::Creado) {
                std::cout << "creado.\n";
            }
            else if (status == FileStatus::Eliminado) {
                std::cout << "eliminado.\n";
            }
            else if (status == FileStatus::Modificado) {
                std::cout << "modificado.\n";
                if (path.find("UserConfigV2.xml") != std::string::npos) {
                    if (configurationFile.load_file(path.c_str())) {
                        std::cout << "UserConfigV2.xml recargado debido a modificación.\n";
                        // Aquí podrías procesar el XML actualizado
                    }
                    else {
                        std::cout << "Error al recargar UserConfigV2.xml.\n";
                    }
                }
            }
            });
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 5 segundos antes de volver a verificar
    }

    
}

void GetConfigFile() 
{
    if (!fileWatcher._paths.empty()) 
    {
        configurationFile.load_file(fileWatcher._paths.begin()->first.data());
    }
}




