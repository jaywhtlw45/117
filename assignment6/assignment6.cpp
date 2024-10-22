// Jason Whitlow
// This program reads a list of id's and DNA sequences from input.txt.
// All matching DNA strings are stored in an unordered map.
// The map is then formated and copied to output.txt

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;
unordered_map<string, vector<int>> dna_map;

// loads input file into an unordered map
void load_input_file(const string &file_name)
{
    fstream file(file_name, ios::in);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }

    string value, key;
    while (getline(file, value))
    {
        if (!getline(file, key))
        {
            cerr << "Error in load_input_file" << endl;
            break;
        }
        dna_map[key].push_back(stoi(value));
    }
    file.close();
}

// formats and copys the ordered map to the output file
void save_to_output_file(string output_file_name)
{
    ofstream output_file(output_file_name);
    if (!output_file.is_open())
    {
        cerr << "Error opening output file: " << output_file_name << endl;
    }

    // add each pair to the output file
    for (const auto &pair : dna_map)    
    {
        if (pair.second.size() == 1)
        {
            output_file << pair.second[0] << endl;
            output_file << pair.first << endl;
        }
        else
        {
            char suffix = 'a';
            for (size_t i = 0; i < pair.second.size(); ++i)
            {
                output_file << pair.second[i] << suffix;
                if (i < pair.second.size() - 1) 
                    output_file << ", ";
                suffix++;
            }
            output_file << endl;
            output_file << pair.first << endl;
        }
    }
    output_file.close();
}

int main()
{
    string file_name = "input.txt";
    string output_file_name = "output.txt";

    load_input_file(file_name);
    save_to_output_file(output_file_name);

    return 0;
}