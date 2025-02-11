# String
_Напишем класс динамической саморасширяющейся строки, заодно познакомимся со стандартным классом std::string._

## std::string
Класс _std::string_ предоставляет удобный и безопасный интерфейс работы со строками в C++. Одна из главных проблем стековых и выделяемых в куче строк (массивов char) заключается в том, что они имеют фиксированный размер и не умеют автоматически расширяться при необходимости. При создании строк в динамической области возникает потребность в ручном отслеживании возможных утечек памяти, что накладывает дополнительные сложности на процесс разработки. Кроме того, C-style строки не хранят информацию о своем размере, что тоже не упрощает взаимодействие с ними.

Эти проблемы можно обойти, используя ООП функционал C++. В частности, механизм инкапсуляции позволяет хранить размер строки в отдельном поле, реализовать методы, при вызове которых массив будет автоматически расширяться, создавая иллюзию неограниченной строки, а механизмы работы с ресурсами гарантируют своевременное выделение и очищение памяти.

Пример:\

std::string s = "hello";\
s.Size();        // 5, работает за O(1)\
s[0] = 'H';\
s += ", world!"  // строка расширяется\
std::cout << s;  // "Hello, world!"\
Подробнее о возможностях std::string здесь.\

## Задание
Реализуйте класс динамической строки - аналог std::string, с эффективной стратегией расширения (мультипликативная схема).

Введем понятия "размера" строки (size) и ее "вместимости" (capacity). С++ в каждый момент времени позволяет поддерживать массивы конечной _вместимости_ (сколько выделено памяти), при этом фактический размер (количество реально используемых символов) может быть меньше этого значения. Почему бы постоянно не поддерживать равенство между этими величинами? - Это не эффективно. Допустим, мы добавляем символы в конец строки по одному. Тогда при каждом обновлении будет происходить перевыделение исходной памяти с последующим копированием всех старых элементов в новый буфер. Легко видеть, что в этом случае общее число копирований будет квадратичным образом зависеть от числа добавленных элементов. Оказывается, что, если при каждом переполнении массива увеличивать его вместимость в константное число раз, то можно добиться линейной зависимости числа операций над массивом от числа добавляемых элементов. В вашем решении будет проверяться корректность работы данной схемы при множителе равном 2 (то есть, при переполнении буфера его вместимость должна увеличиваться **минимум в 2 раза**).

## Детали реализации
Реализуйте класс String со следующим интерфейсом:

* Конструктор по умолчанию - создает пустую строку (nullptr);
* Конструктор, принимающий size и symbol, - создает строку длины size, заполненную символами symbol.
* Конструктор, принимающий С-style строку (const char*) и создающий на ее основе строку. Этот конструктор должен уметь выполнять неявные преобразования, поэтому не нужно объявлять его explicit. Это не понравится кодстайл чекеру, поэтому к строке с объявлением добавьте комментарий // NOLINT, чтобы он проигнорировал эту строку.
* Конструктор, принимающий массив char (const char*) и количество первых символов (size), которые нужно скопировать.
* Правило "трех".
* Константный и неконстантный оператор доступа по индексу []. Последний должен позволять изменять полученный символ (s[0] = 'H');
* Константный и неконстантный метод доступа по индексу At. При выходе за границы строки должен бросать исключение StringOutOfRange, которое уже написано за вас (об этом ниже).
* Методы Front() и Back()
  - доступ к первому и последнему символам (тоже по две версии).
* Методы CStr() и Data()
   - возвращают указатель на начало строки (C-style строку).
* Метод Empty()
  - true, если строка пуста (размер 0).
* Методы Size() и Length()
  - размер строки.
* Метод Capacity()
  - текущая вместимость.
* Метод Clear()
  - устанавливает размер в 0, удаления выделенной памяти при этом НЕ происходит.
* Метод Swap(other)
  - обменивает содержимое с другой строкой other.
* Метод PopBack()
    - удаляет последний символ.
* Метод PushBack(symbol)
  - добавляет символ symbol в конец строки (при необходимости строка расширяется).
* Операция +=
  - принимает другую строку (String) и приписывает ее в конец текущей.
* Метод Resize(new_size, symbol)
  - изменяет размер на new_size. Если вместимость не позволяет хранить столько символов, то выделяется новый буфер с вместимостью new_size. В случае new_size > size заполняет недостающие символы значением symbol.
* Метод Reserve(new_capacity)
  - изменяет вместимость на max(new_capacity, текущая вместимость). Размер при этом не изменяется.
* Метод ShrinkToFit()
  - уменьшает capacity до size (убирает излишек).
* Конкатенация с помощью операции +.
* Операции сравнения (<, >, <=, >=, ==, !=), задающие лексикографический порядок.
* Операция вывода в поток.
\
## Замечания.

Решение должно состоять из файлов cppstring.h и cppstring.cpp.

В этой задаче запрещается использование стандартной библиотеки C++. Если нужны какие-либо служебные классы или функции, реализуйте их самостоятельно.

Проверка устроена таким образом, что требует от вас жесткого следования принятым (выше) сигнатурам и именованиям сущностей (то есть никакие MyString, __string_, push_back, superSolver3000 не пройдут). Если вы реализовали требуемый функционал не полностью или интерфейс отличается от заявленного, вы получите ошибку компиляции.

В тесты включены проверки функциональности (методы работают так как требует условие), проверка эффективности реализации (что значит эффективно описано выше), проверка корректности работы с памятью (утечки памяти, обращения к памяти не принадлежащей процессу будут приводить к провалу).

"Бросить исключение типа E" значит - написать строку throw E{};. В этот момент выполнение функции прекращается и, если исключение не будет обработано, программа завершится аварийно. Тестирующий код корректно обработает эту ошибку, вам этого делать не нужно.
