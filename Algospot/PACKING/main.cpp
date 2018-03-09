#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef struct item
{
    string name;
    int capacity;
    int preference;
} ITEM;

int getMaxPreference(int** memory,const vector<ITEM>& inventory, int max_n, int max_capacity, int idx_item, int now_capacity);
void countItemList(int** memory,const vector<ITEM>& inventory, vector<string>& getIt,int max_n, int max_capacity, int idx_item, int now_capacity, int answer);

int main()
{
    int c;
    freopen("input.txt","r", stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n,w;
        vector<ITEM> inventory;
        vector<string> getIt;
        int answer = 0;
        int** memory;

        cin >> n >> w;

        memory = new int*[n+1];
        for(int j = 0; j < n+1; j++)
        {
            memory[j] = new int[w+1];
            memset(memory[j],-1,sizeof(int)*(w+1));
        }

        for(int j = 0; j < n; j++)
        {
            ITEM one;

            cin >> one.name;
            cin >> one.capacity;
            cin >> one.preference;

            inventory.push_back(one);
        }

        answer = getMaxPreference(memory,inventory,n,w,0,0);

        /*for(int j = 0; j < n+1; j++)
        {
            for(int k = 0; k < w+1; k++)
            {
                cout << memory[j][k] << " ";
            }
            cout << endl;
        }*/

        countItemList(memory,inventory,getIt,n,w,0,0,answer);

        cout << answer << " " << getIt.size() << endl;
        for(int j = 0; j < getIt.size(); j++)
            cout << getIt[j] << endl;

        for(int j = 0; j < n; j++)
            delete [] memory[j];
        delete [] memory;
    }

    return 0;
}

int getMaxPreference(int** memory,const vector<ITEM>& inventory, int max_n, int max_capacity, int idx_item, int now_capacity)
{
    if(idx_item >= max_n)
        return 0;
    if(now_capacity > max_capacity)
        return 0;

    int& answer = memory[idx_item][now_capacity];

    if(answer != -1)
        return answer;

    answer = getMaxPreference(memory,inventory,max_n,max_capacity, idx_item + 1, now_capacity);

    if(now_capacity + inventory[idx_item].capacity <= max_capacity)
        answer = max(answer, inventory[idx_item].preference + getMaxPreference(memory,inventory,max_n,max_capacity, idx_item + 1, now_capacity + inventory[idx_item].capacity));

    return answer;
}

void countItemList(int** memory,const vector<ITEM>& inventory, vector<string>& getIt,int max_n, int max_capacity, int idx_item, int now_capacity, int answer)
{

    if(idx_item >= max_n)
        return ;
    if(now_capacity > max_capacity)
        return ;

    if(memory[idx_item][now_capacity] == memory[idx_item+1][now_capacity])
        countItemList(memory,inventory,getIt,max_n,max_capacity,idx_item+1,now_capacity,answer);
    else
    {
        //cout << idx_item << " " << now_capacity << endl;
        if(memory[idx_item][now_capacity] > 0)
            getIt.push_back(inventory[idx_item].name);
        countItemList(memory,inventory,getIt,max_n,max_capacity,idx_item+1,now_capacity+inventory[idx_item].capacity,answer);
    }

    return ;
    /*int temp = memory[0][0];
    int temp_capacity = 0;
        for(int j = 1; j < max_n+1; j++)
        {
            for(int k = temp_capacity; k < max_capacity+1; k++)
            {
                if(temp == memory[j][k] + inventory[j-1].preference)
                {
                    temp = memory[j][k];
                    temp_capacity + inventory[j-1].capacity;
                    getIt.push_back(inventory[j-1].name);
                    //cout << "temp : " << temp << endl;
                    break;
                }
            }
            if(temp == 0)
                break;
        }
        if(temp > 0 && temp == inventory[max_n-1].preference)
            getIt.push_back(inventory[max_n-1].name);
        if(answer == 0)
            getIt.clear();
*/
}
