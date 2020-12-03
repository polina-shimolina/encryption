#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    string input;                                         //введенная строка
    string codeLine;                                      //кодовая строка
    int wordCounter = 1;                                  //количество слов в кодововй строке
    //getline(cin, codeLine);
    codeLine = "gf hghj jhGHGFGGF hSDGFF FZS";
    for (size_t i = 1; i < codeLine.size(); i++)          //подсчет слов в кодовой строке
    {       
        if ((int)codeLine[i] == 32 && (int)codeLine[i - 1] != 32) 
        {
            wordCounter++;
        }
    }

    int* summAsciiLetter = new int[wordCounter];          //массив с суммами ascii кодов букв каждого слова

    for (int i = 0; i < wordCounter; i++)                 //заполнение нулями
    {
        summAsciiLetter[i] = 0; 
    }

    int numberWordInCodeLine = 0;
    for (size_t i = 0; i < codeLine.size(); i++)          //заполнение summAsciiLetter 
    {
        if ((int)codeLine[i] != 32)
        {
            summAsciiLetter[numberWordInCodeLine] += (int)codeLine[i];
        }
        else 
        {
            summAsciiLetter[numberWordInCodeLine] %= 256; //получение ключа шифрования для каждого слова кроме последнего
            numberWordInCodeLine++;
        }
    }
    summAsciiLetter[numberWordInCodeLine] %= 256;         //получение ключа шифрования последнего слова
    getline(cin, input);
    size_t sizeEncriptionText = input.size();
 
    int* intArrayEncryptedString = new int[sizeEncriptionText];//массив для численного представления зашифрованной строки

    for (size_t i = 0; i < sizeEncriptionText; i++)        //цикл шифрования
    { 
        numberWordInCodeLine = i;                          //запоминаем номер буквы в исходной строке
        if (numberWordInCodeLine >= wordCounter)           //если букв больше чем слов в ключе шифрования, идём в начало ключа 
        {
            while (numberWordInCodeLine > wordCounter) 
            {
                numberWordInCodeLine -= wordCounter;
            }
        }

        intArrayEncryptedString[i] = ((int)input[i] + summAsciiLetter[numberWordInCodeLine]) % 256; // Шифруем посимвольно

        char outputLetter(intArrayEncryptedString[i]);               //зашифрованный символ
        cout << outputLetter;                                        //вывод строки по символу
    }
    cout << endl;


    int* decryptedString = new int[sizeEncriptionText];   //Цикл расшифровки
    for (size_t i = 0; i < sizeEncriptionText; i++) 
    {
        numberWordInCodeLine = i;                         //Запоминаем номер буквы в исходной строке
        if (numberWordInCodeLine >= wordCounter)           //Если букв больше чем слов в ключе шифрования, идём в начало ключа 
        {
            while (numberWordInCodeLine > wordCounter) 
            {
                numberWordInCodeLine -= wordCounter;
            }
        }
        decryptedString[i] = intArrayEncryptedString[i] - summAsciiLetter[numberWordInCodeLine]; //Расшифровываем
        char outputLetter(decryptedString[i]);                      //Расшифрованный символ
        cout << outputLetter;                                       //Вывод строки по символу
    }
    

    int checkTable[256][256] = {};
    for (size_t i = 0; i < sizeEncriptionText; i++) 
    {
        checkTable[(int)input[i]][intArrayEncryptedString[i]]++;

    }
    cout << endl;

    for (int i = 0; i < 256; i++) 
    {
        cout << i << " " << (char)i;
        for (int j = 0; j < 256; j++) 
        {
            if (checkTable[i][j] != 0) 
            {
                cout << "  " << (char)(j) << "  (" << checkTable[i][j] << ")   ";
            }
        }
        cout << endl;
    }
    
    return 0;
}

