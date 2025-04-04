#include <iostream> 

int depth = 0;//������� ��������

template <typename T>
auto _max(T value)//������� ������
{
    std::cout << "Value x: " << value << '\n';//�������� ���������� �������� ����
    return value;
}


template<typename Arg, typename... Args>
auto _max(Arg first, Args... rest)
{
    Arg res{};
    depth++;
    std::cout << "depth >>: " << depth << '\n';//������ ��� ��������

    res = std::max(first, _max(rest...));//��������� max ������ ����

    std::cout << "depth <<: " << depth << '\n';//�������� ��� ��������
    depth--;

    std::cout << "first: " << first <<'\n';//����������� �������
    std::cout << "Value x: " << res << '\n';//������� �������� ���������
    
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
