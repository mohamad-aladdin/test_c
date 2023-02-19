#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;
// تعريف الالوان 
 
string BLACK = "\033[1;30m";
string RED = "\033[1;31m";
string GREEN = "\033[1;32m";
string YELLOY = "\033[1;33m";
string BLUE = "\033[1;34m";
string MAGENTA = "\033[1;35m";
string CYAN = "\033[1;36m";
string WHITE = "\033[1;37m";

// متغيرات للخروج من البرانامج او العودة الى الصفحة الرئيسية
bool EXIT = false;
bool HOMEPAGE = false;

// متغيرات تعبر عن موقع العنوان في المصفوفة 
// مثال : للوصول الى حالة غرفة في حال عدم تعريف هذة المتغيرات  يجب علينا فعل التالي
//  data[0][3]
// بعد تعريف المتغيرات يمكننا فعل هذا 
//  data[0][STATUS]
/* الخلاصة انو نحنا ما لازم نحفظ رقم
   index
   لمخزن عليه حالة الغرفة او اجار الغرفة او عدد الاسرة او رقم الغرفة  
*/ 
int ROOM_NUMBER = 0;
int BEDS_NUMBER = 1;
int RENT = 2;
int STATUS = 3;

// هلق نحنا بما انو مصفوفتنا نوعها اعداد ما منقضر نحط حالة الغرفة انو فارغة 
//لازم نعبر عن كلمة فارغة برقم 
// لهيك عرفناهي المتغيرات هي بتعبر عن حالة الغرفة 

int STATUS_FREE = 1;
int STATUS_RENTED = 2;
int STATUS_RESERVED = 3;

// هدا المتغير عرفنا لنقدر نرجع حالة كل الغرف 
/*
لح نستخدمو مع دالة اسما 
serchRoom
*/
int STATUS_ALL = 4;


// هون عرفنا الداتا تبعنا 
// هي عبارة عن مصفوفة ذات بعدين تتألف من  20 عنصر 
// كل عنصر يتالف من اربع عناصر  
// index = 0 => room number
// index = 1 => beds number
// index = 2 => rent
// index = 4 => status
// ملاحظة يمكن زيادة غرف او تغير اجار الغرفة 

int data[20][4] = {
    {1, 4, 100, 1},
    {2, 2, 50, 1},
    {3, 3, 75, 1},
    {4, 1, 75, 1},
    {5, 4, 100, 1},
    {6, 2, 50, 1},
    {7, 3, 75, 1},
    {8, 1, 75, 1},
    {9, 4, 100, 1},
    {10, 2, 50, 1},
    {11, 3, 75, 1},
    {12, 1, 75, 1},
    {13, 4, 100, 1},
    {14, 2, 50, 1},
    {15, 3, 75, 1},
    {16, 1, 75, 1},
    {17, 4, 100, 1},
    {18, 2, 50, 1},
    {19, 3, 75, 1},
    {20, 1, 75, 1},
};
// هون عرفنا متغير عبارة عن عدد عناصر المصفوفة 
// مشان اذا حبينا نضيف عناصر جديدة ما نغير بلكود 
int dataSize = sizeof(data) / sizeof(data[0]);


// هي الدالة شغلتها انو منعطيها رقم نوعو عدد بتحولو لعدد نوعة نص  مشان الطباعة  

string NumberToString(int number)
{
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}
// هي دالة شغلتا تمسح كل شي مكتوب قبل ما نستدعيها 
// اذا سالتي حالك ليش عملتا دالة مع انا هي امر واحد وكان فيني اكتب هادا المر بلكود وبيعطي نفس النتيجة 
/*
هادا المر لاسمو 
system("clear");
شغلتو انو يحط كلمة 
clear  
بهي الشاشة السود 
(termux in android) or (cmd in windows) or ( terminal in linux)
هي شاشة السودا بس تفرا كلمة 
clear 
لح تمسح  كل شي قبلا هادا الحكي بس ب 
linux and termux 
ع فكرا تناناتن نفس الشي 

هلق بلويندز اذا بدنا نمسح الشاشة لازم نكتب 
cls
وهي الدالة انا مستخدمها 13 مرة بقا  اذا حبيت غير الكلمة تبع المسح وما كنت مستخدم هي الدالة كان لازم غيرها بي صطر
اما هيك لح غيرها بصطر وحاد بس 

*/
void clearConsole()
{
    system("clear");
}

/*
هي دالة شغلتها تطبع النص بلون لبعطيها يا
اول متغير بعبر عن الون 
تاني متغير النص 
تالت متغير بعبرعن اذا بدي انزل ع صطر جديد ولا لا يعني بعبر عن انتهاء الصطر

*/
void print(string color, string text, bool with_end)
{
    // منشوف اذا المتغير لاسمو مع_نهاية في قيمة صحيح لحنفوت وننزل على صطر جديد 
    // صحيح بقصد فيها 
    // true
    if (with_end)
    {
        // كل نص كتبنا وقت عرفنا متغيرات الالوان بعبر عن لون 
        // هادا النص بس تقرا الشاشة السود بتحول كل شي بينكتب بعدا لهادا الون 
        // نحنا ما بدنا نحول كل شي بينكتب ع الشاشة للون لدخلنا للدالة نحنا بس بدنا النص الدخلنا ينكتب بهادا الون
        // لهيك نحنا بعد ما طبعنة النص رجعنا اللون للابيض 
        // فينا نكتبا بطريقة تانية متل هيك 
       
        /*
        هادا الصطر لحبخلي كل شي بينطبع ع الشاشة ينطبع بلون لدخلنا
        cout << color ;
        هون لح نطبع النص لدخلنا 
        cout << text ;
        هون لح نرجع اللون للون الافتراضي لهوي البيض 
        cout << WHITE ;
        وهون لح ننهي الصطر 
        cout << "\n" ;
        */ 

        cout << color << text << WHITE << "\n";
    }
    // اذا ما كانت القيمة صحيح لح نطبع النص بدون ما ننزل لصطر جديد
    else
    {
        cout << color << text << WHITE;
    }
}
// هي الدالة بتبحث عن غرفة بلمعطيات لمندخلها ياها 
// فيكي تقولي كمان انو عم نعمل فلترة للغرف بلمعطيات لمندخلها 
void serchRoom(int reds_number, int status)
{
    // هادا الشرط مشان نتأكد انو رقم الاسرة لمدخل اكبر من 0 واصغر من 5
    // هلق اذا قليتي انو مافي داعي لانو انا لحدخل الرقم ومستحيل اعطي رقم 30 مثلا 
    // لحقلك انو كلامك غلط انت اي دالة بتعمليها لازم تتأكدي من المدخلات قبل ما تعملي شي 
    // لانو بعدين لح تصيري تشتغلي انتي وفريق كامل بكود واحد 
    // هلق الكود هون ناقص هون اذا دخلتي رقم اكبر من 5 او اصغر من 0  ما لح بصير شي بس انو ما لح ينفز الكود 
    // بس تصيري بمستوا متقدم بتصيري بترفعي أستسناء بوقف البرنامج كلو متل 
    // اذا عرفتي متغير نوعو رقم وجيتي قلتي انو هادا المتغير بساوي نص بس تشغلي الكود لح يعطيكي خطء وما يشتغل البرنامج  
    if (reds_number >= 1 && reds_number <= 4)
    {
        // هون حطينا شرطين بقلب بعض لانو هادا الكود بدو شغلتين ليشتغل بدو عدد الاسرة بلغرفة وحالة الغرفة 
        // 
        if (status >= 1 && status <= 3)
        {

            for (int j = 1; j <= 85; j++)
            {
                print(GREEN, "-", false);
            }

            print(GREEN, "", true);
            string title[] = {"Room Number",
                              "beds Number",
                              "Rent",
                              "Status"};
            for (int j = 0; j <= 3; j++)
            {
                print(GREEN, "|", false);
                int q = 20 - title[j].size();
                if (q % 2 == 0)
                {
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                    print(GREEN, title[j], false);
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
                else
                {
                    q = 20 - title[j].size() - 1;
                    for (int x = 1; x <= (q / 2) + 1; x++)
                    {
                        print(GREEN, " ", false);
                    }
                    print(GREEN, title[j], false);
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
            }
            print(GREEN, "|", true);
            for (int j = 1; j <= 85; j++)
            {
                print(GREEN, "-", false);
            }

            print(GREEN, "", true);
            for (int i = 0; i <= dataSize - 1; i++)
            {
                if (data[i][BEDS_NUMBER] == reds_number && data[i][STATUS] == status)
                {
                    for (int j = 0; j <= 3; j++)
                    {
                        string content;
                        switch (j)
                        {
                        case 0:
                            content = NumberToString(data[i][ROOM_NUMBER]);
                            break;
                        case 1:
                            content = NumberToString(data[i][BEDS_NUMBER]);
                            break;
                        case 2:
                            content = NumberToString(data[i][RENT]);
                            break;
                        case 3:

                            if (data[i][STATUS] == 1)
                            {
                                content = "Free ";
                            }
                            else if (data[i][STATUS] == 2)
                            {
                                content = "Rented";
                            }
                            else if (data[i][STATUS] == 3)
                            {
                                content = "Reserved";
                            }
                            break;
                        }
                        print(GREEN, "|", false);
                        int q = 20 - content.size();
                        if (q % 2 == 0)
                        {
                            for (int x = 1; x <= (q / 2); x++)
                            {
                                print(GREEN, " ", false);
                            }
                            print(GREEN, content, false);
                            for (int x = 1; x <= (q / 2); x++)
                            {
                                print(GREEN, " ", false);
                            }
                        }
                        else
                        {
                            q = 20 - content.size() - 1;
                            for (int x = 1; x <= (q / 2) + 1; x++)
                            {
                                print(GREEN, " ", false);
                            }
                            print(GREEN, content, false);
                            for (int x = 1; x <= (q / 2); x++)
                            {
                                print(GREEN, " ", false);
                            }
                        }
                    }
                    print(GREEN, "|", true);
                }
            }
            for (int j = 1; j <= 85; j++)
            {
                print(GREEN, "-", false);
            }

            print(GREEN, "", true);
            
        }
    }
    else if (status >= 1 && status <= 3)
    {

        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
        string title[] = {"Room Number",
                          "beds Number",
                          "Rent",
                          "Status"};
        for (int j = 0; j <= 3; j++)
        {
            print(GREEN, "|", false);
            int q = 20 - title[j].size();
            if (q % 2 == 0)
            {
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
                print(GREEN, title[j], false);
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
            }
            else
            {
                q = 20 - title[j].size() - 1;
                for (int x = 1; x <= (q / 2) + 1; x++)
                {
                    print(GREEN, " ", false);
                }
                print(GREEN, title[j], false);
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
            }
        }
        print(GREEN, "|", true);
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
        for (int i = 0; i <= dataSize - 1; i++)
        {
            if (data[i][STATUS] == status)
            {

                for (int j = 0; j <= 3; j++)
                {
                    string content;
                    switch (j)
                    {
                    case 0:
                        content = NumberToString(data[i][ROOM_NUMBER]);
                        break;
                    case 1:
                        content = NumberToString(data[i][BEDS_NUMBER]);
                        break;
                    case 2:
                        content = NumberToString(data[i][RENT]);
                        break;
                    case 3:

                        if (data[i][STATUS] == 1)
                        {
                            content = "Free ";
                        }
                        else if (data[i][STATUS] == 2)
                        {
                            content = "Rented";
                        }
                        else if (data[i][STATUS] == 3)
                        {
                            content = "Reserved";
                        }
                        break;
                    }
                    print(GREEN, "|", false);
                    int q = 20 - content.size();
                    if (q % 2 == 0)
                    {
                        for (int x = 1; x <= (q / 2); x++)
                        {
                            print(GREEN, " ", false);
                        }
                        print(GREEN, content, false);
                        for (int x = 1; x <= (q / 2); x++)
                        {
                            print(GREEN, " ", false);
                        }
                    }
                    else
                    {
                        q = 20 - content.size() - 1;
                        for (int x = 1; x <= (q / 2) + 1; x++)
                        {
                            print(GREEN, " ", false);
                        }
                        print(GREEN, content, false);
                        for (int x = 1; x <= (q / 2); x++)
                        {
                            print(GREEN, " ", false);
                        }
                    }
                }
                print(GREEN, "|", true);
                // for (int j = 1; j <= 85; j++)
                // {
                //     print(GREEN, "-", false);
                // }

                // print(GREEN, "", true);
            }
        }
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
        
    }
    else if (status == STATUS_ALL)
    {
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
        string title[] = {"Room Number",
                          "beds Number",
                          "Rent",
                          "Status"};
        for (int j = 0; j <= 3; j++)
        {
            print(GREEN, "|", false);
            int q = 20 - title[j].size();
            if (q % 2 == 0)
            {
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
                print(GREEN, title[j], false);
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
            }
            else
            {
                q = 20 - title[j].size() - 1;
                for (int x = 1; x <= (q / 2) + 1; x++)
                {
                    print(GREEN, " ", false);
                }
                print(GREEN, title[j], false);
                for (int x = 1; x <= (q / 2); x++)
                {
                    print(GREEN, " ", false);
                }
            }
        }
        print(GREEN, "|", true);
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
        for (int i = 0; i <= dataSize - 1; i++)
        {
            for (int j = 0; j <= 3; j++)
            {
                string content;
                switch (j)
                {
                case 0:
                    content = NumberToString(data[i][ROOM_NUMBER]);
                    break;
                case 1:
                    content = NumberToString(data[i][BEDS_NUMBER]);
                    break;
                case 2:
                    content = NumberToString(data[i][RENT]);
                    break;
                case 3:

                    if (data[i][STATUS] == 1)
                    {
                        content = "Free ";
                    }
                    else if (data[i][STATUS] == 2)
                    {
                        content = "Rented";
                    }
                    else if (data[i][STATUS] == 3)
                    {
                        content = "Reserved";
                    }
                    break;
                }
                print(GREEN, "|", false);
                int q = 20 - content.size();
                if (q % 2 == 0)
                {
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                    print(GREEN, content, false);
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
                else
                {
                    q = 20 - content.size() - 1;
                    for (int x = 1; x <= (q / 2) + 1; x++)
                    {
                        print(GREEN, " ", false);
                    }
                    print(GREEN, content, false);
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
            }
            print(GREEN, "|", true);
            // for (int j = 1; j <= 85; j++)
            // {
            //     print(GREEN, "-", false);
            // }

            // print(GREEN, "", true);
        }
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
    }
}

void roomRental(int number_people)
{
    clearConsole();
    while (true)
    {
        try
        {

            print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
            print(CYAN, "*                   Room rental                 *", true);
            print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
            serchRoom(-1, number_people, STATUS_FREE);
            print(GREEN, "[h] Home Page", true);
            print(GREEN, "[e] EXIT", true);
            print(MAGENTA, "Please enter the number of Room", true);
            string S_room_number;
            cin >> S_room_number;
            if (S_room_number == "h")
            {
                HOMEPAGE = true;
                return;
            }
            else if (S_room_number == "e")
            {
                EXIT = true;
                return;
            }
            int room_number = stoi(S_room_number);
            if (room_number < 1 || room_number > dataSize)
            {
                print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
            }
            else if (data[room_number - 1][STATUS] != STATUS_FREE)
            {
                print(RED, "Sorry, the room is occupied", true);
            }
            else if (data[room_number - 1][BEDS_NUMBER] != number_people)
            {
                print(RED, "The number of beds in this room is " + NumberToString(data[room_number - 1][BEDS_NUMBER]), true);
            }
            else
            {
                data[room_number - 1][STATUS] = STATUS_RENTED;
                clearConsole();
                print(YELLOY, "Room " + NumberToString(room_number) + " has been successfully rented out", true);
                break;
            }
        }
        catch (...)
        {
            print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
        }
    }
}

void roomRental()
{
    clearConsole();

    while (true)
    {
        string S_number_people;
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                   Room rental                 *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);
        print(MAGENTA, "Please enter the number of people", true);
        cin >> S_number_people;
        if (S_number_people == "h")
        {
            HOMEPAGE = true;
            break;
        }
        else if (S_number_people == "e")
        {
            EXIT = true;
            break;
        }

        try
        {
            int number_people = stoi(S_number_people);
            switch (number_people)
            {
            case 1:
                roomRental(number_people);
                break;
            case 2:
                roomRental(number_people);
                break;
            case 3:
                roomRental(number_people);
                break;
            case 4:
                roomRental(number_people);
                break;

            default:
                print(RED, "Please enter a number greater than 1 and less than 4 or ( e ) to exit or ( h ) to go to home page ", true);
                break;
            }
        }
        catch (...)
        {
            print(RED, "The number of people is incorrect. Please enter a number between 1 and 4 or ( e ) to exit or ( h ) to go to home page", true);
        }
    }
}

void evacuateRoom()
{
    while (true)
    {
        clearConsole();
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                 Evacuate a Room               *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);

        serchRoom(-1, -1, STATUS_RENTED);
        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
            HOMEPAGE = true;
            break;
        }
        else if (S_room_number == "e")
        {
            EXIT = true;
            break;
        }

        try
        {

            int room_number = stoi(S_room_number);
            if (room_number < 1 || room_number > dataSize)
            {
                print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
            }
            else if (data[room_number - 1][STATUS] != STATUS_RENTED)
            {
                print(RED, "Sorry, room number " + NumberToString(room_number) + " is not rented", true);
            }
            else
            {
                string res;
                print(MAGENTA, "Are you sure to vacate room number " + NumberToString(room_number) + " ? ( y | n )", true);
                cin >> res;
                if (res == "y")
                {
                    data[room_number - 1][STATUS] = STATUS_FREE;
                    clearConsole();
                    print(YELLOY, "Room " + NumberToString(room_number) + "  has been successfully evacuated", true);
                }
            }
        }
        catch (...)
        {
            print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize), true);
        }
    }
}

void roomReservations()
{
    while (true)
    {
        clearConsole();
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                Room reservations              *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);

        serchRoom(-1, -1, STATUS_FREE);
        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
            HOMEPAGE = true;
            break;
        }
        else if (S_room_number == "e")
        {
            EXIT = true;
            break;
        }
        try
        {
            int room_number = stoi(S_room_number);
            if (room_number < 1 || room_number > dataSize)
            {
                print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
            }
            else if (data[room_number - 1][STATUS] != STATUS_FREE)
            {
                print(RED, "Sorry, the room is occupied", true);
            }
            else
            {
                data[room_number - 1][STATUS] = STATUS_RESERVED;
                clearConsole();
                print(YELLOY, "Room " + NumberToString(room_number) + " has been successfully rented out", true);
                print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
                print(CYAN, "*                Room reservations              *", true);
                print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
                print(GREEN, "[Any Key] Home Page", true);
                print(GREEN, "[e] EXIT", true);
                print(GREEN, "[r] Reserve another room", true);
                string input__;
                print(MAGENTA, "Please select an order", true);
                cin >> input__;
                if (input__ == "r")
                {

                    continue;
                    ;
                }
                else if (input__ == "e")
                {
                    EXIT = true;
                    break;
                }
                else
                {
                    HOMEPAGE = true;
                    break;
                }
            }
        }
        catch (...)
        {
            print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
        }
    }
}

void releaseReservation()
{
    while (true)
    {
        clearConsole();
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*            Release a room reservation         *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);

        serchRoom(-1, -1, STATUS_RESERVED);
        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
            HOMEPAGE = true;
            break;
        }
        else if (S_room_number == "e")
        {
            EXIT = true;
            break;
        }

        try
        {

            int room_number = stoi(S_room_number);
            if (room_number < 1 || room_number > dataSize)
            {
                print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
            }
            else if (data[room_number - 1][STATUS] != STATUS_RESERVED)
            {
                print(RED, "Sorry, room number " + NumberToString(room_number) + " is not reserved", true);
            }
            else
            {
                string res;
                print(MAGENTA, "Are you sure to vacate room number " + NumberToString(room_number) + " ? ( y | n )", true);
                cin >> res;
                if (res == "y")
                {
                    data[room_number - 1][STATUS] = STATUS_FREE;
                    clearConsole();
                    print(YELLOY, "Room " + NumberToString(room_number) + "  has been successfully evacuated", true);
                }
            }
        }
        catch (...)
        {
            print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize), true);
        }
    }
}

void showRoomsByStatus(int status)
{
    clearConsole();
    if (status == STATUS_FREE)
    {
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                   empty rooms                 *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
    }
    else if (status == STATUS_RENTED)
    {
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                  Rented rooms                 *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
    }
    else if (status == STATUS_RESERVED)
    {
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                 Reserved rooms                *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
    }
    serchRoom(-1, -1, status);
    print(GREEN, "[Any Key] Home Page", true);
    print(GREEN, "[e] EXIT", true);
    string input_;
    cin >> input_;

    if (input_ == "e")
    {
        EXIT = true;
        return;
    }
    else
    {
        HOMEPAGE = true;
        return;
    }
}

int main()
{

    while (true)
    {
        // clearConsole();
        HOMEPAGE = false;
        string option;
        print(GREEN, "[1] Room rental", true);
        print(GREEN, "[2] Evacuate a Room", true);
        print(GREEN, "[3] Room reservations", true);
        print(GREEN, "[4] Release a room reservation", true);
        print(GREEN, "[5] Show empty rooms", true);
        print(GREEN, "[6] Show rented rooms", true);
        print(GREEN, "[7] Show reserved rooms", true);
        print(GREEN, "[8] Show the status of all rooms", true);
        print(GREEN, "[e] Exit", true);
        cin >> option;
        if (option == "e")
        {
            EXIT = true;
            break;
        }
        try
        {
            int n_option = stoi(option);
            switch (n_option)
            {
            case 1:
                roomRental();
                break;
            case 2:
                evacuateRoom();
                break;
            case 3:
                roomReservations();
                break;
            case 4:
                releaseReservation();
                break;
            case 5:
                showRoomsByStatus(1);
                break;
            case 6:
                showRoomsByStatus(2);
                break;
            case 7:
                showRoomsByStatus(3);
                break;
            case 8:
                clearConsole();
                print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
                print(CYAN, "*               status of all rooms             *", true);
                print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
                print(GREEN, "[Any Key] Home Page", true);
                print(GREEN, "[e] EXIT", true);
                serchRoom(-1, -1, STATUS_ALL);

                string input__;
                cin >> input__;

                if (input__ == "e")
                {
                    EXIT = true;
                    return 0;
                }
                break;
            }
        }
        catch (...)
        {
            print(RED, "Please enter a number between 1 and 8 or ( e ) for exit", true);
        }
        if (EXIT)
        {
            break;
        }
    }

    return 0;
}
