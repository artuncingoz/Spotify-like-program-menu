
//Including libraries.
#include <iostream>
#include<string>
using namespace std;

//including header files.
#include "LQueue.h"
#include "LinkedList.h"

//Char that store user command.
static char choice;

//Integer that count how many user there are.
static int counterPerson = 0;

//Integer that count how many output from user names or liked songs. (61th line)
static int countNum = 1;

//Total user counter.
const int totPeople = 50;

//Total song counter.
const int totSongs = 100;

//Array that store user names.
static string* names = new string[totPeople];



struct AllData
{
    string namePerson;
    Queue<string> songsLike;

    //Constr.
    AllData(string xnamePerson = "DEFAULT", string xsongsLike = "DEFAULT") {
        songsLike.add(xsongsLike);
        namePerson = xnamePerson;
    }

    bool operator==(const AllData& other) {
        return (namePerson == other.namePerson);
    }



    // << Operator overloding. That print songs in (const AllData& p) variable.
    friend ostream& operator<<(ostream& out, const AllData& p) {

        Queue<string> xsongsLike;
        xsongsLike = p.songsLike;
        int doesCorrect;

        if (!xsongsLike.isEmpty())
        {
            while (!xsongsLike.isEmpty())
            {
                if (countNum == 1)
                    out << " ";
                out <<"  " << countNum << ". " << xsongsLike.front() <<endl;
                xsongsLike.remove();
                countNum++;
            }
        }
        return out;

    }

};

class Person
{
public:

    friend void update(Person headArray[], Person likedSongs);

    Person() {}
    ~Person() {}

    //Copy constr.
    Person(const Person& old_str)
    {
        names = old_str.names;
        informations = old_str.informations;
    }
private:

    LinkedList<string> names;
    LinkedList<AllData> informations;
};


void update(Person headArray[], Person likedSongs) {

    //Node that used to accessing struct and information.
    LLNode<AllData>* copyArr;


    //Two string which first one store the name of the song.
    string songName;
    //and second one store the name of the user.
    string namePeople;


    //CopyName is a string that adding some char after or before some important strings.
    string copyName;


    //xcountSongsNumber is used to count how many songs have been added. But if the songs have the same name, they will only be counted once.
    int xcountSongsNumber;


    //They are some integer, first one check when the loop execute
    int doesFinish = true;
    //and second one for some if statement.
    bool doesCorrect;


    //Program Loop Start
    while (doesFinish)
    {
        //Menu Start
        cout << "\n   C: Creates a person\n   S: Sets the <Name> likes the <Song>\n   E: Erases the song\n   L: Lists the songs person <Name> likes." << endl;
        cout << "   N: List the names of all of the registered people\n   M: List all the songs that are liked by anyone\n   Q: Quit" << endl;
        //Menu end

        //Taking Input for commands
        cin >> choice;

        //Switch statement for commands Start
        switch (choice)
        {

            //Case C or c for creating new user.
        case 'C':
        case 'c':
            cout << "   Enter your name: ";
            cin >> namePeople;

            //If there is not an any name same with input.
            if (!headArray->names.search(namePeople))
            {
                //Adding this name(namePeople) to string name in AllData Struct.
                headArray[counterPerson].informations.insertFirst(AllData(namePeople));

                //Adding this name(namePeople) to names linked list in Person Class.
                copyName = "\n   " + to_string(counterPerson + 1) + ".";
                headArray->names.insertLast(copyName);
                headArray->names.insertLast(namePeople);

                //Removing default songsname from AllData struct which belong to this name.
                copyArr = headArray[counterPerson].informations.search(AllData(namePeople));
                copyArr->data.songsLike.remove();

                //Adding this name(namePeople) to names Array that will used while Case M or m.
                names[counterPerson] = namePeople;

                //Increasing person counter.
                counterPerson++;

                //Print text if succesfully adding user name.
                cout << "   Person created!" << endl;
            }
            else
            {

                cout << "   Name is already exist! Try again.\n";
            }
            break;

            //Case S or s for creating song for specific user.
        case 'S':
        case 's':
            cout << "   Enter your name: ";
            cin >> namePeople;

            //If there is an any name same with input.
            if (headArray->names.search(namePeople))
            {

                //For loop that size of person count to search songs name of each person liked.
                for (int i = 0; i < counterPerson; i++)
                {
                    //Checking its the right person.
                    if (headArray[i].informations.search(AllData(namePeople)))
                    {

                        //Getting song name from user.
                        cout << "   Set the song name: ";

                        //Using cin.ignore() because if I do not it cause error.
                        //getline() does not work properly it can not get string if there is a space between.
                        cin.ignore();
                        getline(cin, songName);



                        //Copy all information that belongs user name (namePeople).
                        copyArr = headArray[i].informations.search(AllData(namePeople));

                        int doesHave = 0;
                        //If sonsLike Queue is not empty enter the if statemant.
                        while (copyArr->next != NULL)
                        {
                            //check is there a song with same name.
                            if (copyArr->data.songsLike.front() == songName)
                            {
                                cout << "   Song Name is invalid! Try again\n";
                                doesHave = 1;
                            }

                            //Accessing other address
                            copyArr = copyArr->next;
                        }

                        //If there is no such a song insert the song name to sonsLike Queue.
                        if (doesHave == 0) {
                            headArray[i].informations.insertFirst(AllData(namePeople, songName));
                            //Print text if succesfully adding song name.
                            cout << "\n   Song added!\n   Person Name: " << namePeople << "\n   Song: " << songName << endl;
                        }

                    }
                    else
                    {
                        cout << "   Name is not belong it! Try again.\n";
                    }
                }
            }
            else
            {
                //If there is no such name like namePeople.
                cout << "   Name is invalid! Try again.\n";
            }

            break;

            //Case E or e for erase the song for specific user.
        case 'E':
        case 'e':

            doesCorrect = false;

            //Get user name that who wants to delete song.
            cout << "   Enter your name: ";
            cin >> namePeople;

            //If there is an any name same with the input.
            if (headArray->names.search(namePeople))
            {
                //For loop that size of person count to search songs name of each person liked.
                for (int i = 0; i < counterPerson; i++)
                {
                    //Checking its the right person.
                    if (headArray[i].informations.search(AllData(namePeople)))
                    {
                        //Copy all informations that belongs user name (namePeople).
                        copyArr = headArray[i].informations.search(AllData(namePeople));

                        //Check queue is empty.
                        if (!copyArr->data.songsLike.isEmpty())
                        {

                            cout << "   Enter song name to delete: ";

                            //I explained why ı was use cin.ignore() in line 191.
                            cin.ignore();
                            getline(cin, songName);

                            //String array that store songs belongs the this user name.
                            string songsArr[totSongs];

                            //Counter that count how many song have been added.
                            int countSongsNumber = 0;

                            //Loop does not exist while there is no song anymore.
                            while (copyArr->next != NULL)
                            {
                                //Copying songs name belongs to this name in songsArr[].
                                songsArr[countSongsNumber] = copyArr->data.songsLike.front();

                                //Accessing other address
                                copyArr = copyArr->next;
                                countSongsNumber++;
                            }

                            //Clearing existing list to insert later.
                            headArray[i].informations.clearList();

                            //Adding this name to the linkedList. If ı do not add the name. I can not access this name's information again.
                            headArray[i].informations.insertFirst(AllData(namePeople));

                            //Copy all information that belongs user name (namePeople).
                            copyArr = headArray[i].informations.search(AllData(namePeople));

                            //Removing default song name prevent some errors.
                            copyArr->data.songsLike.remove();

                            //That loop checks and delete if there is a song same with the input which we want to delete.
                            for (int x = 0; x < countSongsNumber; x++)
                            {
                                //Check there is a song name that same with the input.
                                if (songsArr[x] == songName) {
                                    doesCorrect = true;
                                }
                                else
                                {
                                    //Adding songs to information list that does not match with the input.
                                    headArray[i].informations.insertFirst(AllData(namePeople, songsArr[x]));
                                }
                            }

                            //If there is a song which same with the input doesCorrect will be 'true'.
                            if (doesCorrect == true)
                            {
                                //and program will print the text that means succesfully deleted.
                                cout <<"\n   '" << songName << "' deleted succesfully" << endl;
                                cout <<"   " << namePeople << " doesn't like the song '" << songName << "' anymore\n";
                            }
                            else
                            {
                                //If there is no song name same with the input.
                                cout << "   Invalid song name! Try again.\n";
                            }
                        }
                        else
                        {
                            //If the songsLike queue is empty.
                            cout << "\n   List is empty!\n";
                        }
                        break;
                    }


                }
            }
            else
            {
                //If there is no such name like namePeople.
                cout << "Name is invalid! Try again.\n";
            }
            break;

            //Case L or l for list the song(s) for specific user.
        case 'L':
        case 'l':

            //Get user name that who wants to delete song.
            cout << "   Enter your name: ";
            cin >> namePeople;

            //If there is an any name same with the input.
            if (headArray->names.search(namePeople))
            {

                int doesFirst;

                //For loop that size of person count to search songs name of each person liked.
                for (int i = 0; i < counterPerson; i++)
                {
                    //Check if is the first time of the output.
                    doesFirst = 0;

                    //This one reset the variable in line 20(countNum) which important to print songs name in order in line 380 (cout << headArray[i].informations).
                    countNum = 1;

                    //Checking its the right person.
                    if (headArray[i].informations.search(AllData(namePeople)))
                    {

                        //Copy all information that belongs user name (namePeople).
                        copyArr = headArray[i].informations.search(AllData(namePeople));

                        //Check queue is empty.
                        if (!copyArr->data.songsLike.isEmpty()) {

                            //Check if is the first time of the output.
                            if (doesFirst == 0) {
                                cout << "\n   " << copyArr->data.namePerson << "'s Liked Songs:\n" << endl;
                                doesFirst = 1;
                            }

                            //Printing the songs names.
                            cout << headArray[i].informations;

                        }
                        else
                        {
                            //If the songsLike queue is empty.
                            cout << "   List is empty!";
                        }
                        break;
                    }



                }
                cout << "\n";
            }
            else
            {
                //If there is no such name like namePeople.
                cout << "   Name is invalid! Try again.\n";
            }
            break;

            //Case N or n for list the user(s) names.
        case 'N':
        case 'n':

            //This one reset the variable in line 20(countNum) which important to print songs name in order
            countNum = 1;

            cout << "   All registered People names:\n";

            //Checking the information list if it is empty.
            if (!headArray->informations.isEmpty()) {

                //Printing all exists names.
                cout << headArray->names;
            }
            else
            {
                //If the songsLike queue is empty.
                cout << "   List is empty!";
            }
            cout << "\n";

            break;

            //Case M or m for list the song(s) liked by user.
        case 'M':
        case 'm':

            cout << "   All Liked Songs:\n";

            //Deleting all the liked songs.
            likedSongs.names.clearList();

            //Variable that count how many songs have been liked.
            //Default 1
            xcountSongsNumber = 1;

            //Variable that check list is empty or not. Default false (EMPTY).
            doesCorrect = false;

            //This one reset the variable in line 20(countNum) which important to print songs name in order.
            countNum = 1;

            //For loop that size of person count to search songs name of each person liked.
            for (int i = 0; i < counterPerson; i++)
            {

                //Copy all information that belongs user name (names[i]).
                copyArr = headArray[i].informations.search(AllData(names[i]));

                //Check queue is empty.
                if (!copyArr->data.songsLike.isEmpty())
                {

                    //Loop does not exist while there is no song anymore.
                    while (copyArr->next != NULL)
                    {

                        //Here program check if this song name already exist in likedSongs linked list.
                        //If it is not, program inserts the song name in linked list.
                        if (!likedSongs.names.search(copyArr->data.songsLike.front())) {

                            //Inserting string.
                            copyName = "\n   " + to_string(xcountSongsNumber) + ".";
                            likedSongs.names.insertLast(copyName);
                            likedSongs.names.insertLast(copyArr->data.songsLike.front());
                            xcountSongsNumber++;

                        }

                        //Accessing other address
                        copyArr = copyArr->next;
                    }
                    //doesCorrect = true means likedSongs list is not empty.
                    doesCorrect = true;
                }

            }

            //If liked songs list is empty.
            if (doesCorrect == false)
            {
                //If the songsLike queue is empty.
                cout << "   List is empty!";
            }
            else
            {
                //Printing all information in likedSongs linked list.
                cout << likedSongs.names;
            }

            cout << "\n";

            break;

            //Case Q or q for exit the loop.
        case 'Q':
        case 'q':
            doesFinish = false;
            break;

            //That case for invalid input that is not on menu.
        default:
            cout << "   Invalid input try again!\n";
            break;
        }
        //Switch statement for commands End

    }
    //Program Loop End

    //Deleting all names in names array
    delete[] names;

    //And inserting Null to array variable.
    names = NULL;

}


int main()
{
    Person headArray[totPeople], likedSongs;

    //Printing welcome text message. This part can be modified by programmer and user requests.
    cout << "\n\n      Welcome to app\n";

    //Function call which run all the program.
    update(headArray, likedSongs);

    //Ending message. This part can be removed.
    cout << "\n      Program End. Bye!\n";
}

