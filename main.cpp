#include <iostream>
#include <vector>
using namespace std;

//---------------DEC-to-Bit------------------------//
vector<int> decTobit(unsigned int a)
{
    vector<int> result(8);
    int bit = 0;
    int count = result.size() - 1;
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
    int result = 0;
    int bit[8][2] =
    {{1, 128},
     {2, 192},
     {3, 224},
     {4, 240},
     {5, 248},
     {6, 252},
     {7, 254},
     {8, 255}, };

    if (oktet >= 0 && oktet <= 8)
    {
        int i = 0;
        for (; i < 8; i++)
            if (bit[i][0] == oktet)break;
        result = bit[i][1];
    }
    else
    {
        return -1;
    }

    return result;
}

//---------------2^N-------------------------------//
unsigned long long two(unsigned long long a)
{
    for (int i = 0; i < 32 - a; i++)
    {
        a *= 2;
    }
    a = a - 1;

    return a;
}

//___________________bit-mask_______________________//
vector<int> Mask(int N)
{
    vector<int> ip;
    int a = N, b = N % 32, oktate0 = 0, oktate1 = 0, oktate2 = 0, oktate3 = 0;

    switch (b)
    {
    case 1: N = bit(b); break;//128
    case 2: N = bit(b); break;//192
    case 3: N = bit(b); break;//224
    case 4: N = bit(b); break;//240
    case 5: N = bit(b); break;//248
    case 6: N = bit(b); break;//252
    case 7: N = bit(b); break;//254
    case 8: N = bit(b); break;//255
    }

    if (N == 0)
    {
        ip.push_back(0);
        ip.push_back(0);
        ip.push_back(0);
        ip.push_back(0);
    }
    else if (a > 0 && a <= 8)
    {
        oktate0 = N;
        ip.push_back(oktate0);
        ip.push_back(0);
        ip.push_back(0);
        ip.push_back(0);
    }

    else if (a >= 9 && a <= 16)
    {
        oktate0 = bit(8);
        oktate1 = bit(a - 8);
        ip.push_back(oktate0);
        ip.push_back(oktate1);
        ip.push_back(0);
        ip.push_back(0);
    }
    else if (a >= 17 && a <= 24)
    {
        oktate0 = bit(8);
        oktate1 = oktate0;
        oktate2 = bit(a - 16);
        ip.push_back(oktate0);
        ip.push_back(oktate0);
        ip.push_back(oktate2);
        ip.push_back(0);
    }
    else if (a >= 25 && a <= 32)
    {
        oktate0 = bit(8);
        oktate1 = oktate0;
        oktate2 = oktate1;
        oktate3 = bit(a - 24);
        ip.push_back(oktate0);
        ip.push_back(oktate0);
        ip.push_back(oktate2);
        ip.push_back(oktate3);
    }

    return ip;
}

vector<int> NETWORK(vector<int> a, vector<int> b)
{
    vector<int> result(4);
    
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = a[i] & b[i];
    }
    return result;
}

//------------Wildcard------------------------------//
vector<int> WILDCARD(vector<int>& wild)
{
    vector<int> result(4);
    for (int i = 0; i < result.size(); i++)
    {
        result[i] =wild[i] ^ 255;
    }
    return result;
}

char CLASS_MASK(int bit_mask)
{
    char clas = '0';
    if (bit_mask >= 0 && bit_mask <= 8)
    {
        clas = 'A';
    }
    else if (bit_mask >= 9 && bit_mask <= 16)
    {
        clas = 'B';
    }
    else if (bit_mask >= 17 && bit_mask <= 32)
    {
        clas = 'C';
    }
    else
    {
        return -1;
    }
    return clas;
}

//----------------------IP___________________________//
vector<int> fund_of_ip(int a, int b, int c, int e)
{
    vector<int> enter_ip;
    enter_ip.push_back(a);
    enter_ip.push_back(b);
    enter_ip.push_back(c);
    enter_ip.push_back(e);

    return enter_ip;
}

vector<int> MIN_IP(vector<int>& min)
{
    min[3] = 1;
    return min;
}

vector<int> MAX_IP(vector<int> max)
{


    return max;
}

//-----------number-of-host----------------------//
int max_host(int a)
{
    int result = 1;
    if (a == 0)
    {
        result = 0;
    }
    else if (a > 0 && a < 31)
    {
        for (int i = 0; i < 32 - a; i++)
        {
            result *= 2;
        }
        result = result - 2;
    }
    else if (a == 31)
    {
        result = 2;
    }
    else if (a == 32)
    {
        result = 1;
    }

    return result;
}

int main()
{
    //*******************************variable**************************//
    const int host = 254;
    int bit_mask = 0;
    vector<int> ip;
    vector<int> mask_ip;
    int oktet_ip_0 = 0, oktet_ip_1 = 0, oktet_ip_2 = 0, oktet_ip_3 = 0;
    //*****************************************************************//
    system("color F0");
    /***********************Start***************************************/

    ip://ticket goto
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
            else
            {
                goto ip;
            }
        }
    }
mask_restart://ticket goto
    while (true)
    {
        cout << "Press enter mask bit: (0, 1 , 2 ... 32): ";
        cin >> bit_mask;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "enter error, try again\n";
        }
        else
        {
            if ((bit_mask >= 0 && bit_mask <= 32))
            {
                goto Source_Data;
            }
            else
            {
                goto mask_restart;
            }
        }
    }
    /*---------------------Cout IP----------------------------*/
Source_Data:

    ip = fund_of_ip(oktet_ip_0, oktet_ip_1, oktet_ip_2, oktet_ip_3);

    cout << "\tSource Data: \n";
    cout << "*************************************************\n";
    cout << "ip adres = [";

    for (int i = 0; i < ip.size(); i++)
    {
        cout << ip[i];
        if (i != ip.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "] \n";

    cout << "ip_binary [";
    vector<int> ok0 = decTobit(oktet_ip_0);
    for (int i = 0; i < ok0.size(); i++)
    {
        cout << ok0[i];
    }
    cout << '.';
    vector<int> ok1 = decTobit(oktet_ip_1);
    for (int i = 0; i < ok1.size(); i++)
    {
        cout << ok1[i];
    }
    cout << '.';
    vector<int> ok2 = decTobit(oktet_ip_2);
    for (int i = 0; i < ok1.size(); i++)
    {
        cout << ok1[i];
    }
    cout << '.';
    vector<int> ok3 = decTobit(oktet_ip_3);
    for (int i = 0; i < ok3.size(); i++)
    {
        cout << ok3[i];
    }
    cout << "]\n";

    //---------------cout<<-mask---------------------------//
    mask_ip = Mask(bit_mask);
    cout << "network mask = [";

    for (int i = 0; i < mask_ip.size(); i++)
    {
        cout << mask_ip[i];
        if (i != mask_ip.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "]\n";
 
    cout << "mask_binary [";
    vector<int> m0 = decTobit(mask_ip[0]);
    vector<int> m1 = decTobit(mask_ip[1]);
    vector<int> m2 = decTobit(mask_ip[2]);
    vector<int> m3 = decTobit(mask_ip[3]);

    for (int i = 0; i < m0.size(); i++)
    {
        cout << m0[i];
    }
    cout << ".";
    for (int i = 0; i < m1.size(); i++)
    {
        cout << m1[i];
    }
    cout << ".";
    for (int i = 0; i < m2.size(); i++)
    {
        cout << m2[i];
    }
    cout << ".";
    for (int i = 0; i < m3.size(); i++)
    {
        cout << m3[i];
    }
    cout << "]\n";
    cout << "bit mask = " << bit_mask << "\n";
    cout << "binary bit mask [";
    vector<int> bit_bi = decTobit(bit_mask);
    for (int i = 0; i < bit_bi.size(); i++)
    {
        cout << bit_bi[i];
    }
    cout << "]\n";
    cout << "*************************************************\n";

    //----------------WILDCARD--------------------//
    cout << "wildcard [";
    vector<int> wildcard = WILDCARD(mask_ip);

    for (int i = 0; i < wildcard.size(); i++)
    {
        cout << wildcard[i];
        if (i != wildcard.size() - 1)
        {
            cout << '.';
        }
    }
    cout << "]\n";
    //---------------network----------------------//
    vector<int> network_ip = NETWORK(ip, mask_ip);
   
    cout << "network [";
    for (int i = 0; i < network_ip.size(); i++)
    {
        cout << network_ip[i];
        if (i != network_ip.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "] \n";

    //------------min/max------------------------//
    vector<int> minip = ip;
    vector<int> maxip = ip;

    cout << "min ip [";
    minip[3] = 0;
    for (int i = 0; i < minip.size(); i++)
    {
        cout << minip[i];
        if (i != minip.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "]\n";
    maxip[3] = 255;
    cout << "max ip [";
    for (int i = 0; i < maxip.size(); i++)
    {
        cout << maxip[i];
        if (i != maxip.size() - 1)
        {
            cout << ".";
        }
    }
    cout << "]\n";

    //---------------Class mask----------------//
    cout << "subnet class [";
    cout << CLASS_MASK(bit_mask);
    cout << "]\n";

    //--------maximum number of hosts--------//
    unsigned long long number_of_hosts = max_host(bit_mask);
    cout << "number_of_hosts [";
    cout << number_of_hosts;
    cout << "]\n";
    //--------------------------------------//
    cout << "*************************************************\n";

    goto ip;//restart
    return 0;
}