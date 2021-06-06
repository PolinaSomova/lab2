#include <iostream>
#include <fstream>
#include <chrono>

typedef std :: chrono :: time_point<std :: chrono :: high_resolution_clock> timestamp;

using namespace std;

int * createRandomArrSize ( struct Array * arr );
int * createArrayWithoutSize ( struct Array * arr );
int * createFromFile ( struct Array * arr );

int * addElementToArray ( struct Array * arr, int element );
int * addElementToArray ( struct Array * arr, int element );
int * deleteElementIndex ( struct Array * arr, int index );
int * deleteElementValue ( struct Array * arr, int value );
int getElement ( int * arr, int index );
int * doubleUpArray ( struct Array * arr );
int * doubleUpArray ( int * arr, int size );
int * shrinkArray ( int * arr, int newSize );
int * shiftArray ( int * arr, int size, int startIndex );
void printArray ( struct Array * arr );

void printMenu ();
void chooseMenu (struct Array * arr, int menuCase );
void printTime ( timestamp, timestamp, string );


struct Array {
    int * data;
    int size;
    int length;
};

struct List {
    int data;
    List *head;
    List *tail;
    int length;
};

int main() {

    setlocale(LC_ALL, "Russian");

    int menuCase;
    struct Array *arr = new Array();

    while (true) {

        printMenu();

        cin >> menuCase;

        cout << "\n";

        switch (menuCase) {
            case 15:
                delete[] arr;
                return 0;
                break;
            default:
                chooseMenu(arr, menuCase);
                break;
        }

    }
}

void printMenu () {

    cout << "---Массив---:\n"
                << "1 - Создать массив автоматически\n"
                << "2 - Создать массив с клавиатуры\n"
                << "3 - Создать массив с файла\n"
                << "4 - Добавить элемеент в массив\n"
                << "5 - Удалить элемент из массива\n"
                << "6 - Получить элемент из массива\n\n"
               // << "===Double Linked List===\n"
              //  << "7 - Create double linked list automaticly\n"
               // << "8 - Create double linked list from input\n"
              //  << "9 - Create double linked list from file\n"
               // << "10 - Add element to list\n"
               // << "11 - Delete element from list\n"
               // << "12 - Get element from list\n"
               // << "13 - Exit\n"
                << "Введите пункт: ";
}

void chooseMenu ( struct Array * arr, int menuCase ) {

    switch (menuCase) {

        case 1: {
            cout << "Введите размер массива: ";
            cin >> arr->size;
            arr->length = arr->size - 1;
            arr->data = createRandomArrSize(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 2: {
            std::cout << "Введите элементы массива: \n";
            arr->data = createArrayWithoutSize(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 3: {
            arr->data = createFromFile(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 4: {
            int newEl;
            cout << "Введите элемент для добавления в массив: ";
            cin >> newEl;
            arr->data = addElementToArray(arr, newEl);
            printArray(arr);
            break;
        }
        case 5: {
            int toDelete, type;
            cout << "Выберите вариант: 1 - по индексу; 2 - по значению\n";
            cin >> type;
            switch (type) {
                case 1:
                    cout << "Введите индекс для удаления: ";
                    cin >> toDelete;
                    arr->data = deleteElementIndex(arr, toDelete);
                    break;
                case 2:
                    cout << "Введите значение для удаления: ";
                    cin >> toDelete;
                    arr->data = deleteElementValue(arr, toDelete);
                    break;
            }
            printArray(arr);
            break;
        }
        case 6: {
            int index;
            cout << "Введите индекс для получения: ";
            cin >> index;
            cout << "Индекс значения: " << getElement(arr->data, index) << "\n";
            break;
        }
    }
}






/*
 * Array
 */
int * createRandomArrSize ( struct Array * arr ) {

    int * newArr = new int[arr->size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i < arr->size; i++ ) {
        newArr[i] = rand() % 100;
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array created: ");

    return newArr;

}

int * createArrayWithoutSize ( struct Array * arr ) {

    int size = 2;
    int * newArr = new int[size];
    int num, index = 0;
    bool end = false;

    arr->length = size - 1;
    arr->size = size;

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    while ( !end ) {

        cout << "Введите " << index << " элемент ( или -1, чтобы прекратить ввод ): ";

        cin >> num;

        if ( num == -1 ) {
            end = true;
            break;
        } else if ( index < size ) {
            newArr[index] = num;
            index++;
        } else {
            index = size;
            int * temp = newArr;
            newArr = doubleUpArray(temp, size);
            newArr[index] = num;
            size = size * 2;
            index++;
        }

    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array created ");

    arr->length = index - 1;

    return newArr;

}

int * createFromFile ( struct Array * arr ) {

    ifstream file;
    int index = 0, size = 2;
    int * newArr = new int[size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    file.open("array.txt");

    if ( file.is_open() ) {

        string line;

        while ( getline(file, line) ) {

            int num = stoi(line);

            if (index < size) {
                newArr[index] = num;
                index++;
            } else {
                index = size;
                int* temp = newArr;
                newArr = doubleUpArray(temp, size);
                newArr[index] = num;
                size = size * 2;
                index++;
            }

        }

    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array creation ");

    arr->length = index - 1;

    return newArr;

}


int * addElementToArray ( struct Array * arr, int element ) {

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    if ( arr->length < arr->size ) {
        arr->length++;
        arr->data[arr->length] = element;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Добавлен элемент ");

        return arr->data;
    } else {
        int * newArr = doubleUpArray(arr);
        arr->length++;
        newArr[arr->length] = element;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Добавлен элемент ");

        return newArr;
    }
}


int * deleteElementIndex ( struct Array * arr, int index ) {

    if ( arr->length == -1 ) {
        cout << "Массив пустой\n";
        return arr->data;
    }

    if ( index == arr->length ) {
        arr->length--;
        arr->size = arr->length;
        return shrinkArray(arr->data, arr->length);
    } else {
        arr->length--;
        arr->size = arr->length;
        return shiftArray(arr->data, arr->length, index);
    }

}

int * deleteElementValue ( struct Array * arr, int value ) {

    int index;

    for (int i = 0; i < arr->length; i++) {
        if ( arr->data[i] == value ) {
            return deleteElementIndex(arr, i);
        }
    }

    cout << "Значение удалено\n";

    return arr->data;

}

int getElement ( int * arr, int index ) {

    cout << "Элемент был получен за 0 ms: ";

    return arr[index];

}


//доп к массивам

int * doubleUpArray ( struct Array * arr ) {

    int newSize = arr->size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= arr->length; i++ ) {
        newArr[i] = arr->data[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "");

    arr->size = newSize;

    return newArr;

}

int * doubleUpArray ( int * arr, int size ) {

    int newSize = size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= size; i++ ) {
        newArr[i] = arr[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "");

    return newArr;

}

int * shrinkArray ( int * arr, int newSize ) {

    int * newArr = new int[newSize + 1];

    for ( int i = 0; i < newSize + 1; i++ ) {
        newArr[i] = arr[i];
    }

    return newArr;

}

int * shiftArray ( int * arr, int size, int startIndex ) {

    int * newArr = new int[size];

    for ( int i = 0; i < startIndex; i++ ) {
        newArr[i] = arr[i];
    }

    for ( int i = startIndex; i < size + 1; i++ ) {
        newArr[i] = arr[i + 1];
    }

    return newArr;

}

void printArray ( struct Array * arr ) {

    for ( int i = 0; i <= arr->length; i++ ) {
        cout << arr->data[i] << " ";
    }

    cout << "\n\n";
}

void printTime ( timestamp startTime, timestamp endTime, string type ) {

    cout << type << "ended in: "
                << std :: chrono :: duration_cast <std :: chrono :: microseconds> (endTime - startTime).count()
                << " microseconds\n";

}

/*
 * List
 */

/*
void createRandomeList ( List * list ) {

    timestamp startTime, endTime;
    startTime = chrono :: high_resolution_clock :: now();

    for ( int i = 0; i < list->length; i++ ) {
        push(list, rand() % 100);
    }

    endTime = chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "List created ");

}

void populateListUndefined ( List * list ) {

    int num, index = 0;
    bool end = false;

    timestamp startTime, endTime;
    startTime = chrono :: high_resolution_clock :: now();

    while ( !end ) {

        cout << "Введите " << index << " элемент ( или -1, чтобы прекратить ввод ): ";

        cin >> num;

        if ( num == -1 ) {
            end = true;
            break;
        } else {
            index++;
            push(list, num);
        }

    }

    endTime = chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "List createdн ");

}
*/