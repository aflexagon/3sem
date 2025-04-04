#include <iostream> 

int depth = 0;//глубина рекурсии

template <typename T>
auto _max(T value)//базовый случай
{
    std::cout << "Value x: " << value << '\n';//проверка корректной передачи типа
    return value;
}


template<typename Arg, typename... Args>
auto _max(Arg first, Args... rest)
{
    Arg res{};
    depth++;
    std::cout << "depth >>: " << depth << '\n';//прямой ход рекурсии

    res = std::max(first, _max(rest...));//аргументы max одного типа

    std::cout << "depth <<: " << depth << '\n';//обратный ход рекурсии
    depth--;

    std::cout << "first: " << first <<'\n';//отщепляемый элемент
    std::cout << "Value x: " << res << '\n';//текущее значение максимума
    
    return res;
}

int main()
{
    std::cout << "Final result: " << _max(4, 3, 8, 99, -10) << '\n';
    std::cout << "######################" << '\n';
    depth = 0;
    std::cout << "Final result: " << _max('c', 'd', 'a') << '\n';
    std::cout << "######################" << '\n';
    depth = 0;
    std::cout << "Final result: " << _max(std::string("c"), std::string("d"), std::string("a"), std::string("100")) << '\n';
    std::cout << "######################" << '\n';
    return 0;
}
