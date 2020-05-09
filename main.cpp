#include <cstring>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <regex>

using namespace std;

int main()
{
    ifstream fin1, fin2;
    fin1.open("spSequence");
    fin2.open("ace2Sequence");

    if(!fin1)
        cout << "Can not open spSequence" << endl;
    if(!fin2)
        cout << "Can not open ace2Sequence" << endl;
    string ace2Sequence, spSequence, input;
    
    while(getline(fin1, input))
        spSequence += input;
    int spLen = spSequence.length();
    
    while(getline(fin2, input))
        ace2Sequence += input;
    int ace2Len = ace2Sequence.length();
    
    
    #ifdef DEBUG
    cout << "========================" << endl;
    cout << "Spike Protein Sequence:" << endl;
    cout << spSequence << endl;
    cout << "========================" << endl;
    cout << "Ace2 Protein Sequence:" << endl;
    cout << ace2Sequence << endl;
    cout << "========================" << endl;
    
    #endif
    while(true)
    {
        string cutSequence;
        cout << "Enter the cleavage sequence of choice" << endl;
        cin >> cutSequence;
        if(cutSequence == "quit")
            break;
        if(cutSequence.find("*") != string::npos)
        {
            int index = cutSequence.find("*");
            cutSequence.replace(index, 1, "[A-Z]");     
        }
        #ifdef DEBUG
        cout << "cutSequence " << cutSequence << endl;
        #endif
        regex e(cutSequence.c_str()); 
        smatch res;
        
        
        string::const_iterator searchStart( spSequence.cbegin() );
        bool found = false;
        cout << "========================" << endl;
        cout << "Found in the Spike protein sequence" << endl;
        while (regex_search( searchStart, spSequence.cend(), res, e ))
        {
            found = true;
            int start = spSequence.find(res[0].str());
            cout << "from " << start + 1 << " to " << start + res[0].str().length() << "\t";
            cout << res[0] << endl;  
            searchStart = res.suffix().first;
        }
        if(!found)
            cout << "NOT FOUND!!" << endl;
        cout << "========================" << endl << endl;

        searchStart = ace2Sequence.cbegin();
        found = false;
        cout << "========================" << endl;
        cout << "Found in the Ace2 protein sequence" << endl;
        while (regex_search( searchStart, ace2Sequence.cend(), res, e ))
        {
            found = true;
            int start = ace2Sequence.find(res[0].str());
            cout << "from " << start + 1 << " to " << start + res[0].str().length() << "\t";
            cout << res[0] << endl;  
            searchStart = res.suffix().first;
        }
        if(!found)
            cout << "NOT FOUND!!" << endl;
        cout << "========================" << endl;
    }
    fin1.close(); fin2.close();
    return 0;
}