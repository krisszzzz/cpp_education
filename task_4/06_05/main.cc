#include <print>
#include <iostream>
#include <string>
#include <boost/dll.hpp>

////////////////////////////////////////////////////////////

int main()
{
        std::print("Enter dynamic library filename (library_v1 or library_v2): ");

        std::string library_name;
        std::cin >> library_name;

        std::string library_path;
        if (library_name == "library_v1")
        {
                library_path = "liblibrary_v1.so";
        }
        else if (library_name == "library_v2")
        {
                library_path = "liblibrary_v2.so";
        }
        else
        {
                std::print("Error: Unknown library name\n");
                return 1;
        }

        try
        {
                auto test_function = boost::dll::import_symbol<void()>(
                        library_path,
                        "test"
                );

                test_function();
        }
        catch (const std::exception& exception)
        {
                std::print("Error loading library: {}\n", exception.what());
                return 1;
        }

        return 0;
}

////////////////////////////////////////////////////////////