#include <iostream>
#include <string>
#include <locale>
#include <cwctype>

void Task_1_BigBukvi(std::wstring &strochka)
{
    if (strochka.empty())
        return;

    bool inWord = false;
    wchar_t FirstBukava = L'\0';
    bool FirstProideno = false;

    for (size_t i = 0; i < strochka.length(); i++)
    {
        if (iswalpha(strochka[i]))
        {
            if (!inWord)
            {
                inWord = true;
                FirstBukava = strochka[i];
                FirstProideno = false;
            }
            if (towlower(strochka[i]) == towlower(FirstBukava))
            {
                if (FirstProideno)
                {
                    strochka[i] = towupper(strochka[i]);
                }
                else
                {
                    FirstProideno = true;
                }
            }
        }
        else
        {
            inWord = false;
        }
    }
}

int main()
{
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::wcout << std::endl;
    std::wcout << L"Task 1:" << std::endl;

    std::wstring prinyato;

    std::wcout << L"Enter the line: ";
    std::getline(std::wcin, prinyato);

    Task_1_BigBukvi(prinyato);
    std::wcout << L"Answer for Task 1: " << prinyato << std::endl;

    return 0;
}
