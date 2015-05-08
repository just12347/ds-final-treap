#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
const int MAX_SIZE = 10000000;
typedef string KeyType;

class ItemException : public exception
{
    public:
        ItemException(string msg = "") : message(msg){}
        string what(){return message;}
    private:
        string message;
}; 

class ItemList{

    public:
        struct Movie_Information{
            string movie_id;
            string movie_information;
        };
        typedef Movie_Information ItemType;

        void insertItem(ItemType& item) throw (ItemException);
        void deleteItem(KeyType& item) throw (ItemException);
        ItemType retrieveItem(KeyType key) throw (ItemException);

};

ItemList  List;

int main()
{
    char filename[256];
    scanf("%s", filename);
    ifstream fin(filename,ifstream::in);
    string line, movie_id, movie_information;
    while(getline(fin, line))
    {
        ItemList::ItemType newItem;
        stringstream ss(line);
        getline(ss, newItem.movie_id, '|');
        getline(ss, newItem.movie_information, '\n');
        List.insertItem(newItem);
    }
    //Calling Functions To Check Answer
    fin.close();
    return 0;
}

