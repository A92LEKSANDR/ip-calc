#include <iostream>
#include <vector>
using namespace std;

//---------------DEC-to-Bit------------------------//
vector<int> dec_to_bit(unsigned int a)
{
    vector<int> result(8);
    int bit = 0;
    size_t count = result.size() - 1;
    while (a > 0)
    {
        bit = a % 2;
        a /= 2;
        result[count] = bit;
        count--;
    }
    return result;
}

//___________________fund-oktate___________________//
int bit(int oktet)
{
    int bit[ ] = {128,192,224,240,248,252,254,255};

    int i = 0;
    if (oktet >= 0 && oktet <= 7)
    {
       return bit[oktet];
    }
    return -1;
}

//___________________bit-mask_______________________//
vector<int> mask(int N)
{
    vector<int> ip;
    int a = N, b = N % 32;
    
    if (b >= 1 && b <= 8)
    {
        N = bit(b);
    }

    if (N == 0)
    {
        return { 0, 0, 0, 0 };
    }
    else if (a > 0 && a <= 8)
    {
        int oktate0 = N;
        return { oktate0, 0, 0, 0 };
    }
    else if (a >= 9 && a <= 16)
    {
        int oktate0 = bit(7);
        int oktate1 = bit(a-7);
        return { oktate0, oktate1, 0, 0 };
    }
    else if (a >= 17 && a <= 24)
    {
        int oktate0 = bit(7);
        int oktate1 = oktate0;
        int oktate2 = bit(a - 15);
        return { oktate0, oktate1, oktate2, 0 };
    }
    else if (a >= 25 && a <= 32)
    {
        int oktate0 = bit(7);
        int oktate1 = oktate0;
        int oktate2 = oktate1;
        int oktate3 = bit(a - 23);
        return { oktate0, oktate1, oktate2, oktate3 };
    }

    return { 0u, 0, 0, 0 };
}

vector<int> network(vector<int> a, vector<int> b)
{
    vector<int> result(4);
    
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = a[i] & b[i];
    }
    return result;
}

//------------wildcard------------------------------//
vector<int> wildcard(vector<int> wild)
{
    vector<int> result(4);
    for (int i = 0; i < result.size(); i++)
    {
        result[i] =wild[i] ^ 255;
    }
    return result;
}
//-----------------class_mask----------------------//
char class_mask(int bit_mask)
{
    if (bit_mask >= 0 && bit_mask <= 8)
    {
        return 'A';
    }
    else if (bit_mask >= 9 && bit_mask <= 16)
    {
        return 'B';
    }
    else if (bit_mask >= 17 && bit_mask <= 32)
    {
        return 'C';
    }
    return -1;
}

//----------------------IP___________________________//
vector<int> fund_of_ip(int a, int b, int c, int e)
{
    return { a, b, c, e };
}
//--------------------min max------------------------//
vector<int> min_ip(vector<int> ip, int bit)
{
    vector<int> min(4);
    vector<int> a = mask(bit);
    if (bit > 0 && bit <= 8)
    {
        return { ip[0], 0, 0, 0 };
    }
    else if (bit >= 9 && bit <= 16)
    {
        return { ip[0],ip[1],0,0 };
    }
    else if (bit >= 17 && bit <= 24)
    {
        return { ip[0],ip[1],ip[2],1 };
    }
    else if (bit >= 25 && bit <= 32)
    {
        return { ip[0],ip[1],ip[2],ip[3]+1};
    }
    return {0,0,0,0};
}

vector<int> max_ip(vector<int> ip, int bit)
{
    vector<int> max(4);
    vector<int> a = mask(bit);
    if (bit > 0 && bit < 8)
    {
        return { 255 - a[0] + ip[0], 255, 255, 254 };
    }
    else if (bit >= 8 && bit < 16)
    {
        return { ip[0], 255 - a[1] + ip[1], 255, 254};
    }
    else if (bit >= 16 && bit < 24)
    {
        return { ip[0], ip[1], 254 - a[2] + ip[2], 254 };
    }
    else if (bit >= 24 && bit <= 32)
    {
        return { ip[0], ip[1], ip[2], ip[3] };

        while (max[3] != 254)
        {
            max[3]++;
        }
    }
    return max;
}

//-----------number-of-host----------------------//
int max_host(int a)
{
    int result = 1;
    if (a == 0)
    {
        return 0;
    }
    else if (a > 0 && a < 31)
    {
        for (int i = 0; i < 32 - a; i++)
        {
            result *= 2;
        }
        result -= 2;
    }
    else if (a == 31)
    {
        return 2;
    }
    else if (a == 32)
    {
        return 1;
    }

    return result;
}

//-------------print func----------------------//
void print_func(vector<int>& a)
{
    cout << "[";
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i];
        if (i != a.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "]\n";
}

int main()
{
    //*******************************variable**************************//
    int bit_mask = 0;
    vector<int> ip(4);
    vector<int> mask_ip(4);
    int oktet_ip_0 = 0, oktet_ip_1 = 0, oktet_ip_2 = 0, oktet_ip_3 = 0;
    /***********************Start***************************************/

    while (true)
    {
        cout << "Press enter ip (for example 192 168 0 1 [0.0.0.0 - 254.254.254.254]): \n";
        cin >> oktet_ip_0 >> oktet_ip_1 >> oktet_ip_2 >> oktet_ip_3;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "enter error, try again\n";
        }
        else
        {
            if (oktet_ip_0 >= 0 && oktet_ip_0 <= 255 && oktet_ip_1 >= 0 && oktet_ip_1 <= 255 && oktet_ip_2 >= 0 && oktet_ip_2 <= 255 && oktet_ip_3 >= 0 && oktet_ip_3 <= 255)
            {
                break;
            }
        }
    }

    while (true)
    {
        cout << "Press enter mask bit: (0, 1 ... 32): ";
        cin >> bit_mask;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "enter error, try again\n";
        }
        else
        {
            break;
        }
    }
    
    ip = fund_of_ip(oktet_ip_0, oktet_ip_1, oktet_ip_2, oktet_ip_3);
    cout << "\tSource Data: \n";
    cout << "*************************************************\n";
    cout << "ip addres ";
    print_func(ip);

    mask_ip =  mask(bit_mask);
    cout << "network mask ";
    print_func(mask_ip);
    cout << "*************************************************\n";

    cout << "wildcard [";
    vector<int> wild_card = wildcard(mask_ip);
    print_func(wild_card);
    
    vector<int> network_ip = network(ip, mask_ip);  
    cout << "network ";
    print_func(network_ip);

    vector<int> min = min_ip(ip,bit_mask);
    cout << "min ip";
    print_func(min);

    vector<int> max = max_ip(ip, bit_mask);
    cout << "min ip";
    print_func(max);

    cout << "subnet class ";
    cout << class_mask(bit_mask);

    unsigned long long number_of_hosts = max_host(bit_mask);
    cout << "number_of_hosts ";
    cout << number_of_hosts;
    
    cout << "\n*************************************************\n";
    return 0;
}