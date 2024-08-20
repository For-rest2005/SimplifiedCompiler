/*
This source file implement the virtual machine
*/
#include<map>
#include<iostream>

int mem[50000];
int &rip = mem[0];
int cmdlst[10010][4];
void Command0(int x = 0,int y = 0,int z = 0){
    mem[y] = x;
    rip++;
}
void Command1(int x = 0,int y = 0,int z = 0){
    mem[y+mem[z]] = mem[x];
    rip++;
}
void Command2(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x+mem[y]];
    rip++;
}
void Command3(int x = 0,int y = 0,int z = 0){
    mem[y] = mem[x];
    rip++;
}
void Command4(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x]+mem[y];
    rip++;
}
void Command5(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x]-mem[y];
    rip++;
}
void Command6(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x]*mem[y];
    rip++;
}
void Command7(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x]/mem[y];
    rip++;
}
void Command8(int x = 0,int y = 0,int z = 0){
    mem[z] = mem[x]%mem[y];
    rip++;
}
void Command9(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] == mem[y]);
    rip++;
}
void Command10(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] > mem[y]);
    rip++;
}
void Command11(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] < mem[y]);
    rip++;
}
void Command12(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] && mem[y]);
    rip++;
}
void Command13(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] || mem[y]);
    rip++;
}
void Command14(int x = 0,int y = 0,int z = 0){
    mem[y] = !mem[x];
    rip++;
}
void Command15(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] & mem[y]);
    rip++;
}
void Command16(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] | mem[y]);
    rip++;
}
void Command17(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] ^ mem[y]);
    rip++;
}
void Command18(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] << mem[y]);
    rip++;
}
void Command19(int x = 0,int y = 0,int z = 0){
    mem[z] = (mem[x] >> mem[y]);
    rip++;
}
void Command20(int x = 0,int y = 0,int z = 0){
    if(mem[x]) rip = y;
    else rip++;
};
void Command30(int x = 0,int y = 0,int z = 0){
    rip = x;
}
void Command40(int x = 0,int y = 0,int z = 0){
    rip = mem[x];
}
void Command50(int x = 0,int y = 0,int z = 0){
    std::cout << mem[x] << ' ';
    rip++;
}
void Command60(int x = 0,int y = 0,int z = 0){
    std::cin >> mem[x];
    rip++;
}
void Command70(int x = 0,int y = 0,int z = 0){
    std::cout << (char)mem[x] << ' ';
    rip++;
}
void Command100(int x = 0,int y = 0,int z = 0){
    std::cerr << "successfully exit" << std::endl;
    exit(1);
}

const std::map<int,void(*)(int,int,int)> cmdTable = {
    {0,Command0},{1,Command1},{2,Command2},{3,Command3},{4,Command4},{5,Command5},{6,Command6},{7,Command7},
    {8,Command8},{9,Command9},{10,Command10},{11,Command11},{12,Command12},{13,Command13},{14,Command14},
    {15,Command15},{16,Command16},{17,Command17},{18,Command18},{19,Command19},{20,Command20},{30,Command30},
    {40,Command40},{50,Command50},{60,Command60},{70,Command70},{100,Command100}
};

using namespace std;
int main(){
    int tt,op,x,y,z;
    cin >> tt;
    for(int i = 0;i < tt;i++){
        cin >> op;
        x = y = z = 0;
        if(op == 100);
        else if(op == 50 || op == 60 || op == 30 || op == 40 || op == 70)
            cin >> x;
        else if(op == 0 || op == 3 || op == 14 || op == 20)
            cin >> x >> y;
        else 
            cin >> x >> y >> z;
        cmdlst[i][0] = op;
        cmdlst[i][1] = x;
        cmdlst[i][2] = y;
        cmdlst[i][3] = z;
    }
    rip = 0;
    while(true)
        cmdTable.at(cmdlst[rip][0])(cmdlst[rip][1],cmdlst[rip][2],cmdlst[rip][3]);
    return 0;
}