#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "CPU.h"

using namespace std;

CPU cpu;

int main()
{
/*        FOR LOADING ROMS. CURRENTLY UNUSED. THIS IS ALL FUCKED UP 
    // Prompt for filename
    string filename;
    cout << "Enter the ROM name: ";
    cin >> filename;

    // Check if file opened correctly
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    // Get file size
    file.seekg(0, ios::end);
    streampos size = file.tellg();
    file.seekg(0, ios::beg);

    // Resize ROM to match file and read into ROM
    cpu.rom.resize(static_cast<size_t>(size));
    file.read(reinterpret_cast<char*> (&cpu.rom[0]), size);
    file.close();

    // Report file size and check first 10 bytes for sanity
    cout << "Size of file is: " << size << '\n';
    cout << "The first 10 bytes of ROM are: ";
    ios_base::fmtflags f(cout.flags());
    for (int i = 0; i < 10; ++i)
    {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(cpu.rom[i]);
        cout << ' ';
    }
    cout << endl;
    cout.flags(f);
*/

    cpu.Cycle();
    // Remove later
    cout << "Done\n";
    return 0;
}