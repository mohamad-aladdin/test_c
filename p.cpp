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

//  متغير للخروج من البرنامج
bool EXIT = false;

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
// لازم نعبر عن كلمة فارغة برقم
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
    // هلق اذا قلتيي انو مافي داعي لانو انا لحدخل الرقم ومستحيل اعطي رقم 30 مثلا
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
            //  هي الحلقة لحتطبع 85 شخطة عني عبارة عن السقف تبع الجدول
            for (int j = 1; j <= 85; j++)
            {
                // هو عطينا انو بس نطبع ما بدنا ننزل على سطر جديد
                print(GREEN, "-", false);
            }
            // هون ما طبعنا شي بس طلبنا انو ننزل على سطر جديد
            print(GREEN, "", true);
            // هون عملنا مصفوفة بلعناوين لعنا
            string title[] = {"Room Number",
                              "beds Number",
                              "Rent",
                              "Status"};
            // هون حنبدء بكتابة العناوين
            // هدي الحلقة لازم تفهميها كتير منيح اذا ما فهمتيها قوليلي بشرحلك ياها بمقاطع صوت
            // اول شي طلبنا من الحلقة انو تلف 4 لفات
            for (int j = 0; j <= 3; j++)
            {
                // اول شي لحح نطبع خط مشان يحدد بدايت الجدول وما نزلنا ع صطر جديد
                print(GREEN, "|", false);

                // انا عامل عرض الخانة 20 حرف
                // هون لحنجيب كل عنوان ونشوف اديش عدد الاحرف بهادا العنوان ونقصو من 20
                // مشان نشوف قديش بدنا نحط فراغات قبل الكلمة وبعدا مشان تجي الكلمة بنص الخانة
                int q = 20 - title[j].size();

                // هون لحنشوف اذا الرقم لطلع معنا باقي قسمتة ع 2 بساوي 0 يعني الرقم زوجي فينا نقسمو ع تنين بدون فواصل
                if (q % 2 == 0)
                {
                    // هون عملنا حلقة عدد لفاتا هو نص العدد لطلع معنا بعد ما نقصنا عدد احرف الكلمة لبدنا نكتبها من 20
                    // يعني لح نفترض انو الحلقة وصلة لعند كلمة
                    // Rent
                    // هي الكلمة عدد احرفها 4 منقص 4 من 20 بيعطينا 16 منقصم 16 على 2 بصير عنا 8
                    // يعني عدد الفراغات قبل وبعد الكلمة لازم يكون 8 لحتا تجي الكلمة بنص الخانة
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        // هون كل ما لفت الحلقة لحنطبع فراغ بدون ما ننزل على سطر جديد
                        print(GREEN, " ", false);
                    }
                    // هون لحنطبع الكلمة
                    print(GREEN, title[j], false);
                    // هون لحنرجع نطيبع نفس عدد الفراغات لطبعناهن فوق بدون ماننزل لسطر جديد
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
                // هون اذا طلع الرقم ما بيقبل القصمة ع 2 يعني رقم فردي
                else
                {
                    // بهي الحالي لحنقص عدد احرف الكلمة من 20 وبعدين منقص واح مشان يصير الرقم زوجي وبيقبل القصمة ع 2
                    // يعني بس نوصل لعند كلمة
                    // beds Number
                    // هي الكلمة عدد احرفها 11 اذا نقصناها من ال 20 لح يطلع عنا 9 اذا نقصنا كمان 1 بصير الرقم 8 وفينا نقصمو ع 2
                    q = 20 - title[j].size() - 1;

                    // هون اذا قلنا للحلقة انو عدد لفاتك هو نص 8 يعني 4 لحيصير عنا خطء برسم
                    // لانو 4 فراغات قبل الكلمة و  4 فراغات بعد الكلمة بصيرو 8 ولكلمة 11 حرف صارو 19
                    // ونحنا عرض الخانة عنا 20 لهيك الحل انو نرج ال 1 لنقصنا يا قبل الكلمة يا بعدها
                    // انا هون خترت انو الفراغ ينضاف قبل الكلمة
                    // هي الحلقة لح تطبع 5 فراغات
                    for (int x = 1; x <= (q / 2) + 1; x++)
                    {
                        print(GREEN, " ", false);
                    }
                    // بعدين لحنطبع الكلمة
                    print(GREEN, title[j], false);
                    // وهن لحنطبع 4 بكون المجموع صار 20 وهيك بتكون صارة الكلمة بنص الخانة بدون ما ننزع شكل الجدول
                    // طبعاهي الارقام بلعتماد ع الكلمة لانا فترضتا هي الحلقة لح تلف ع الاربع كلمات
                    // يعني انت اذا بدك تغيري عنوان اي عامود بجدول بتغيري من مصفوفة العناوين لعرفناها فوق
                    // بجوز تكتبي عنون عدد الاحرف في 15 بهي الحالة لحالو الكود بيحسب ويطبع 3 فراغات قبل العنوان وفراغين بعد العنون
                    // وهيك بصير العنوان الجديد بنص الخانة وما منكون خربنا شكل الجدول
                    // انا فترضت انو مافي عنان اكتر من 20 حرف
                    // الصورة لبعتيلي ياها الدكتور ما ضاف فراغت  قبل الكلمة هوي كتب الكود ع اساس الفراغات كلا تنكتب بعد الكلمة
                    // بس توصلي لهون حكيني لابعتلك صورة تشرحلك شو صار
                    for (int x = 1; x <= (q / 2); x++)
                    {
                        print(GREEN, " ", false);
                    }
                }
            }
            // هلق بعد ما الحلقة لفت ع العناوين كلن وكتبتن ع السطر واحد ضل عنا نحط شخطة مشان نسكر الجدول ونزل ع صطر جديد
            print(GREEN, "|", true);
            // هون لحنطبع 85 شخطة مشان نسكر خانات العناوين
            // يعني لحبتصير العناوين بقلب مربعات
            for (int j = 1; j <= 85; j++)
            {
                print(GREEN, "-", false);
            }

            // بعد ما سكرنا العناوين لازم ننزل ع سطر جديد لنبلش نكتب المحتوا لعنا
            print(GREEN, "", true);
            // هي الحلقة لحتفتل ع كل الداتا لعنا
            for (int i = 0; i <= dataSize - 1; i++)
            {
                // هادا الشرط لح يتاكد من الغرفة اذا كان عدد الاسرة الموجودين بلغرفي بساوي
                // عدد الاسرة لدخلتا للدالة ( و ) حالة الغرفة بساوي حالة الغرفة لدخلتا منطبع بياناتا
                // اذا ما تحققو الشرطين منروح ع الغرفة لبعدها
                // يعني اذا انا بدي اعرض الغرف لعدد الاسرة فيها 2 وتكون حالتها فترغة
                // هادا الشرط لح يطبعلي بس الغرف لعدد السرة فيها 2 وحالتها فارغة
                // يعني اذا في غرفة عدد الاسرة فيها 2 وحلتها مأجرة ما لح يعرضها
                // هادا الجزء من الكود منستخدمو لما بدنا نأجر غرفة
                // منعطي عدد الاشخاص ومنعطي انو بدنا الغرف الفارغة بس

                if (data[i][BEDS_NUMBER] == reds_number && data[i][STATUS] == status)
                {
                    // هلق هون بدن نبلش نطبع بيانات الغرفة بقلب الجدول بنفس الطريقة لطبعنا فيها العناوين مشان يصيرو تحت بعضبنص الخانة

                    // هي الحلقة لحتلف 4 لفات لهني عدد البانات لعنا
                    for (int j = 0; j <= 3; j++)
                    {
                        // هون لحنعرف متغير اسمو محتوى
                        string content;
                        // هون لح نشوف شو رقم اللفة لنحنا فيها
                        switch (j)
                        {
                        case 0:
                            // أذا كنا بلفة رقم 0
                            // لحنخلي قيمة المحتوى بتساوي رقم الغرفة لحققت الشرط
                            content = NumberToString(data[i][ROOM_NUMBER]);
                            // هي الكلمة مشان الكود ما يروح يتاكد من باقي الحالات
                            break;
                        case 1:
                            // أذا كنا بلفة رقم 1
                            // لحنخلي قيمة المحتوى بتساوي عدد السرة لحققت الشرط
                            content = NumberToString(data[i][BEDS_NUMBER]);
                            // هي الكلمة مشان الكود ما يروح يتاكد من باقي الحالات

                            break;
                        case 2:
                            // هون كمان متل فوق
                            content = NumberToString(data[i][RENT]);
                            break;
                        case 3:
                            // اذا كنا لفة رقم 3 يعني بدنا نطبع حالة الغرفة
                            // اذا عملنا متل فوق لحيطبعلنا حالة الغرفة عبارة عن رقم
                            // نحنا بدنا ياها كلمة
                            // هون لحنشوف شو قيمة الحالة
                            // ونخلي قيمة المحتوى بتساوي الكلمة
                            if (data[i][STATUS] == STATUS_FREE)
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
                        // هون لحنبلش رسم سطر جديد بجدول في بيانات الغرفة
                        // اذا فهمتي طريقة رسم العناوين لح تفهمي هادا الجزء من الكود
                        // انا عاملو نسخ لصق مع شويت تعديلات
                        print(GREEN, "|", false);
                        // التعديلهو انو غيرنا العنوان ب المحتوى
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
            // هون طبعناخط متل فوق بعد ما يكون طبع بيانات كل الغرف المطابقة للشرط
            // هادا الخط مشان نسكر الجدول من السفل
            for (int j = 1; j <= 85; j++)
            {
                print(GREEN, "-", false);
            }

            print(GREEN, "", true);
        }
    }

    // هون اذا بدنا نفلتر الغرف بنسبة للحالة بس
    // منتأكد النو الحالة المدخلة اكبر من 0 واصغر من 5
    // ومنعملمتل فوق بضبط بس في اختلاف واحد
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
            // الاختلاف هون
            /*
            هادا الشرط لكان فوق
            // هادا الشرط لح يتاكد من الغرفة اذا كان عدد الاسرة الموجودين بلغرفي بساوي
            // عدد الاسرة لدخلتا للدالة ( و ) حالة الغرفة بساوي حالة الغرفة لدخلتا منطبع بياناتا

            */
            // الشرط هو انو اذا كانت حالة الغرفة بتساوي الحالة المدخلة بيطبع بيانات الغرفة
            // هادا الجزء من الكود لحنستعملو وقت بدنا نبحث عن الغرف المؤجرة او المحجوزة او الغرف الفارغة
            // يعني اذا بدي شوف الغرف المأجورة لحدخل للدالة رقم الاسرة = -1 مشان ما يتحقق الشرط لفوق ولحدخل الحالة مأجورة
            // باقي الكود ناسخو من فوق يعني اذا فهمتي الشرح فوق لحتفهمي هون
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
            }
        }
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
    }
    // هون اذا دخلنا انو الحالة كل شي
    // ها الشرط لحنستخدمو وقت بدنا نعرض حالة كل الغرف رقم 8 بصفحة الرئيسية لتطبيق
    else if (status == STATUS_ALL)
    {
        // هون مافي شطرط لعرض الغرف
        // هون لحنعرض كل الغرف
        // وهادا الكود ناسخو من فوق بس لحنطبع البيانات بشكل مرتب بجدول

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
        }
        for (int j = 1; j <= 85; j++)
        {
            print(GREEN, "-", false);
        }

        print(GREEN, "", true);
    }
}

// هي دالة تأجير غرفة الجزء ال 2
// الجزء الاول تحت بلشي بجزء الاول
// بعدين الجزء التاني

// هي الدالة منعطيها عدد الاشخاص بعد ما نكون تأكدنا انو عدد الاشخاص مقبول
void roomRental(int number_people)
{
    // منمسح كل شي مكتوب
    clearConsole();
    // حلقة لللانهاية مشروحة بجزء الاول اذا ما فهمتيها بشرحلك ياها وتس اب
    while (true)
    {
        // معالجة اخطاء مشروحة بجزء الاول
        try
        {
            // هون مرجع منكتب العنوان
            print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
            print(CYAN, "*                   Room rental                 *", true);
            print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);

            // هي الدالة شرحتا فوق
            // هون بطلب منا تطبعلي كل الغرف الفارغة الموجود فيها عدد اسرة بساوي عدد الاسرة لدخلو المستخدم
            serchRoom(number_people, STATUS_FREE);

            // هون بطبع الخيارات فينا نرجع نغير عدد الاسرة وفينا نطلع من البرنامج
            print(GREEN, "[h] BACK", true);
            print(GREEN, "[e] EXIT", true);
            print(MAGENTA, "Please enter the number of Room", true);

            // هون منجيب البيانات لدخلها المستخدم ونتأكد منا متل الجزء الاول
            // هون البيانات بتعبر عن رقم الغرفة
            string S_room_number;
            cin >> S_room_number;
            if (S_room_number == "h")
            {
                // هون ما حطينا كلمة
                // break
                // لانو نحنا ما بدنا ترجع الحلقة تعيد حالها مرا تانيه
                // هون نحنا منكون بدنا نتراجع عن خيار خطء صار مع المستخدم
                // يعني المستخدم اجا لعندو 3 اشخاص وقالولو بدنا نستأجر غرفة بعد ما ادخل رقم 3 مشان
                // يأجر غرفة فيها 3 اسرة قالولو لا نحنا 4 اشخاص في شخص فات ع الحمام
                // بهي الحالة لازم نرجع نغير عدد الاشخاص صح ؟؟؟
                // لهيك منخلي الدالة توقف

                /*
                ملاحظة كلمة
                البرنامج بس يوصل لعند اول كلمة
                return
                بوقف الدالة ما بنفز باقي الاوامر المحطوطة بدالة
                */
                return;
            }
            // هون اذا بدو يطلع من البرنامج منوقف الدالة كلا ومنغير الخروج ل صحيح
            // باخر الجزء الاول في شرط بيفحص قيمة الخروح اذا صح بيووقف الحلقة
            else if (S_room_number == "e")
            {
                EXIT = true;
                return;
            }
            // هون حولانا النص لرقم
            // ملاحظة بس يدخلك بيانات من المستخدم بتدخل  كنص يعني
            // string
            // ولو دخل رقم بيوصل لعندك نص يعني اذا دخل 1 بيوصل لعنا "1" هيك
            int room_number = stoi(S_room_number);
            // هون منشوف انو رقم الغرفي اصغر من 0 و اكبر  من عدد عناصر الداتا لعنا
            // هون بكون في خط مافيني اجر غرفة رقمها -1
            // او 134 لانو انا عندي بس 20غرفة
            // لهيك اذا تحقق الشرط بطبع خطء وما بوقف الحلقة بخليها تعيد حالها وتطلب منو يدخل رقم غرفة صحيح طيعا هادا الحكي لللانهاية
            if (room_number < 1 || room_number > dataSize)
            {
                print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
            }
            // هون بشوف رقم الغرفة لدخلها المستخدم اذا ما كانت حالتها فارغة بقلو انو الغرفة مشغولة
            // data[room_number -1 ]
            // ليش ما قلنا
            // data[room_number]
            // لانو نحنا مسميين الغرف من 1 الى 20
            // بس الكود بيحفظن من 0 الى 19
            // لانو المصفوفة بتبلش تخزين من 0
            // يعني الغرفة رقم 1 موقعها بلمصفوفة هو 0 وموقهعا بقصد في ال
            // index
            else if (data[room_number - 1][STATUS] != STATUS_FREE)
            {
                print(RED, "Sorry, the room is occupied", true);
            }
            // هون بتحقق كمان انو الغرفة لدخلها المستخدم عدد الاسرة فيها اذا ما بساوي عدد الاشخاص بطبعلو خط

            else if (data[room_number - 1][BEDS_NUMBER] != number_people)
            {
                print(RED, "The number of beds in this room is " + NumberToString(data[room_number - 1][BEDS_NUMBER]), true);
            }
            // هون اذا ما تحقق ولا شرط يعني
            // رقم الغرفة صحيح
            // الغرفة فارغة
            // عدد السرة بلغرفي بساوي عدد الشخاص
            else
            {
                // هون عدلنا ع بيانات الغرفة وخلينا حالتها مأجرة
                data[room_number - 1][STATUS] = STATUS_RENTED;
                // بعدين مسحنا كل شي مكتوب
                clearConsole();
                // وبهدين طبعنا انو تم حجز الغرفة رقم كذا بنجاح
                print(YELLOY, "Room " + NumberToString(room_number) + " has been successfully rented out", true);
                break;
            }
        }
        catch (...)
        {
            // هون اذا دخل حرف بدال ما يدخل رقم منقلو انو لازم دخل رقم من 1 الى 20
            print(RED, "Please enter a number greater than 0 and less than " + NumberToString(dataSize) + " or ( e ) to exit or ( h ) to go to home page", true);
        }
    }
}

//  هي الدالة لتاجير غرفة الجزء 1
void roomRental()
{
    // اول شي لحنمسح كل شي مكتوب قديم
    clearConsole();
    // هي الحاقة بتلف لللانهاية
    while (true)
    {
        // اول شي منعرف متغير مشان نخزن في القيمة لبدو يدخلها المستخدم
        string S_number_people;
        // هون طبعنا عنوان الصفحة
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                   Room rental                 *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);

        // هون طبعنا الخيارات لعنا
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);
        print(MAGENTA, "Please enter the number of people", true);

        // هون بوقف البرنامج وبينطر من المستخدم يدخل بيانات
        cin >> S_number_people;

        // هون منتحقق من البيانات
        // اذا دخل حرف ال
        // h

        if (S_number_people == "h")
        {
            // هادا الكود بوقف الحلقة وبس توقف الحلقة بتكون خلصة الدالة
            break;
        }

        // او اذا دخل حرف ال
        // e

        else if (S_number_people == "e")
        {
            // هون منخلي المتغير لعرفنا للخروج من البرنامج قيمتو صحيحة
            // ومنوقف الحلقة
            // هلق بس توقف الحلقة بترجع ع القائمة الرئيسية
            // بلقائمة الرئيسية في حلقة لللانهاية كمان بس كل لفة بتتأكد من قيمة المتغير الخروج اذا قيمتو صحيحة بتطلع من البرنامج
            // اذا خاطء بتمسح كل شي قبلا وبترجع بتطبع مكونات الشاشة الرئيسية
            EXIT = true;
            break;
        }

        // هون اذا المستخدم ما دخل واحد من الحرفين
        // بهي الحالة بكون بدو يدخل عدد الاشخاص أو بكون كاتب حرف مو مجود بلقائمة
        // مثلا بجوز يدخل حرف
        // q
        // بهي الحالة لازمن نعطي خطء للمستخدم انو البيانات غير صحيحة ونرجع نطلب منو يدخل بيانات صحيحة
        // جزء انو نرجع  نطلب منو بيانات صحيحة هادا شغلت الحلقة لخليناها تلف لللاناية
        // يعني اذا المستخدم ضل يدخل بيانات غلط للانهاية نحنا منضل نقلو انو بياناتك غلط دخل بيانات صح
        // لو كنا عاملي حلقة فور عادية وعاطينا عدد لفات 100 مثلا كان البرنامج بيستقبل من المستخدم 100 خطء
        // بعدين بضوج منو وبقلعو
        else
        {
            // هون كتبتلك تلخيص لجملة ال
            // try catch
            // اذا عنا كود شاكين انو يصير في غلط يوقف البرنامج
            // منحطو بقلب جملة
            // try
            // اذا صار الخطء ما بيوقف البرنامج بس بشغل الكود لموجود بجملة ال
            // catch

            // نحنا ستخدمناها هون لانو بدنا نحول البيانات لبدخلها المستخدم لرقم
            // اذا فترضنا انو المستخدم بدال ما يدخل عدد السرة 3 دخل حرف
            // x
            // نحنا بهي الحالة لح ناخد حرف الأكس ونحولو لرقم واكيد لحيعطينا خطء ويوقف البرنامج
            // بس بما انو نحنا حاطين الكود بجملة
            // try
            // ما لحيوقف البرنامج بس لح يشغل الكود الموجود بجملة
            // catch

            /*
            try
            {
                // Protected Code
                // هنا نكتب الأوامر التي قد تسبب إستثناء
            }
            catch(ExceptionType e)
            {
                // Error Handling Code
                // برمي إستثناء try هنا نكتب أوامر تحدد للبرنامج ماذا يفعل إذا قامت الـ
            }

            */
            try
            {
                // عرفا متغير بعبر عنن عدد الاسرة كعدد وبحول البيانات لدخلها المستخدم لعدد
                // اذا المستحدم دخل نص ما بصير خطء بلبرنامج بس بشغل جملة
                // catch
                // هادا الشي اسمو معالجة الاخطاء
                int number_people = stoi(S_number_people);

                // هون منشوف الرقم لدخلو المستخدم
                // اذا كان 1 او 2 او 3 او 4
                // منشغل الدالة لعرفناها فوق لهي المرلة التانية من تأجير غرفة

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
                // هادا الجزء من الكود بيشتغل اذا ما تحققت ولا حالة من ليحاطينا فوق

                // يعني بجوز المستخدم يتحيون ويدخل -1 او 20 بهي الحالة ما لحبصير خط لانو هو ارقام
                // لهيك قلنا هون انو اذا الرقم لدخلو المستخدم غير الاربع ارقام لمتوقعينا نحنا
                // منطبعلو خطئ
                default:
                    print(RED, "Please enter a number greater than 1 and less than 4 or ( e ) to exit or ( h ) to go to home page ", true);
                    break;
                }
            }
            // هي جملة ما حددنالا خطء محدد ال 3 نقط يعني اي خطء بصير بجملة
            // try
            // شغل هادا الكود
            catch (...)
            {
                print(RED, "The number of people is incorrect. Please enter a number between 1 and 4 or ( e ) to exit or ( h ) to go to home page", true);
            }
        }
        // هون اذا كانت خيمة الخروج صحيحة منطلع من الحلقة
        if (EXIT)
        {

            break;
        }
    }
}

// فك تأجير  غرفة
void evacuateRoom()
{
    // حلقة لانهاية مشان اذا دخلنا بيانات غلط
    while (true)
    {
        // مسحنا كل شي
        clearConsole();
        // طبعنا عنوان
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);
        print(CYAN, "*                 Evacuate a Room               *", true);
        print(CYAN, "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*", true);

        // طبعنا الخيارات
        print(GREEN, "[h] Home Page", true);
        print(GREEN, "[e] EXIT", true);

        // هي الدالة بتطبعلنا كل الغرف لحالتها مأجرة و -1 يعني مو مهم عدد الاسرة بلغرفي
        // يعني تطبعلي اي غرفة مأجرة قد ما كان عدد الاسرة فيها

        serchRoom(-1, STATUS_RENTED);

        // اخدنا البيانات وتاكدنا اذا المستخدم بدو يرحع ع الصفحة الرئيسية منرجعو
        // واذا بدو يخرج من البرنامج منقلعو

        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
            break;
        }
        else if (S_room_number == "e")
        {
            EXIT = true;
            break;
        }

        try
        {
            // هون اذا المستخدم دخل رقم غرفة
            int room_number = stoi(S_room_number);
            // نفس الشروط لحطيناهن بدالة تأجير غرفة الجزء 2
            // منتحقق انو الرقم مانو اصغر من الصفر ولا اكبرمن 20
            // وانو حالة الغرفة المطلعوب فك تأجيرا هي ماجرة بلاصل
            // مشان ما نفك تأجير غرفة وهي بلاصل فارغة
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
                // هون بعد ما تحققنا انو كل شي تمام
                // منسال المستخدم هل انت متأكد من فك تأجير الغرفة رقم كذا
                // اذا دخل حرف
                // y
                // منغير حالة الغرفة من مأجورة الى فارغة
                // اذا كبس اي حرف غير حرف
                // y
                // ما بصير شي
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
            // هون اذا حرف بدال رقم الغرفة
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

        serchRoom(-1, STATUS_FREE);
        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
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

        serchRoom(-1, STATUS_RESERVED);
        string S_room_number;
        print(MAGENTA, "Please enter the number of Room", true);
        cin >> S_room_number;
        if (S_room_number == "h")
        {
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
    serchRoom(-1, status);
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
        return;
    }
}

int main()
{

    while (true)
    {
        // clearConsole();
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
                serchRoom(-1, STATUS_ALL);

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
