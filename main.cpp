#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

///Converts a string of text into a number (does no checking)
int Int(string num) {
    int num_i = 0;

    while (num.size() > 0) {
        num_i *= 10;
        num_i += num[0] - '0';
        num = num.substr(1);
    }

    return num_i;
}

int Binary(string data, int min_val, int max_val, char first_half, char last_half) {
    char chr;

    for (int c = 0; c < data.size(); c++) {
        chr = data[c];

        //cout << chr << " " << min_val << " " << max_val << "\t";
        if (chr == first_half) {
            max_val = ((max_val - min_val)/2) + min_val;
            //cout << min_val << " " << max_val << "\n";
        }
        else if (chr == last_half) {
            min_val = ((max_val - min_val)/2) + min_val + 1;    //plus one because it is in the last place of the first half
            //cout << min_val << " " << max_val << "\n";
        }
        else {
            cout << "uh oh, I've done goofed! D:\n";
        }
     //   system("pause");
    }

    return max_val; //could return either max or min, they should end up being the same value
}

int Get_Row(string data) {
    int row = Binary(data.substr(0, 7), 0, 127, 'F', 'B');

    return row;
}

int Get_Col(string data) {
    int col = Binary(data.substr(7, 3), 0, 7, 'L', 'R');

    return col;
}

///Gets the max value of an ID
int Get_Max_ID(map<int, bool> *ids, int *min_id) {
    ifstream file;
    string line;
    int max_id = -1;
    int cur_id;
    int row;
    int col;
    int mult = 8;

    file.open("seats.txt");

    getline(file, line);
    while (file) {
        row = Get_Row(line);
        col = Get_Col(line);
        cur_id = (row * mult) + col;

        (*ids)[cur_id] = true;

        if (cur_id > max_id) {
            max_id = cur_id;
        }

        if (cur_id < *min_id) {
            *min_id = cur_id;
        }

        getline(file, line);
    }

    file.close();

    return max_id;
}


///Finds the missing id from min_id to max_id
int Get_ID(map<int, bool> ids, int max_id, int min_id) {
    for (int i = min_id; i <= max_id; i++) {
        if (!ids[i]) {
            return i;
        }
    }

    return -1;
}

int main()
{
    int max_id = -1;
    int my_id = -1;
    int min_id = 65535;
    map<int, bool> ids;

    max_id = Get_Max_ID(&ids, &min_id);

    cout << "The max id is " << max_id << endl;

    my_id = Get_ID(ids, max_id, min_id);

    cout << "My id is " << my_id << endl;

    return 0;
}
