/*
This source file implement the virtual machine
*/

#include<vector>
#include<functional>
#include<map>
#include<iostream>

int mem[50000];
int &rip = mem[0];

class Command{
public:
    Command(int _x = 0,int _y = 0,int _z = 0)
        :x(_x),y(_y),z(_z){};
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void ripIncrement(){rip++;};
protected:
    int x,y,z;
};

Command* cmdlst[10010];

class Command0:public Command{
public:
    Command0(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){mem[y] = x;}
};

class Command1:public Command{
public:
    Command1(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[y+mem[z]] = mem[x];}
};

class Command2:public Command{
public:
    Command2(int _x,int _y,int _z):Command(_x,_y,_z){};
    virtual void execute(){mem[z] = mem[x+mem[y]];}
};

class Command3:public Command{
public:
    Command3(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){mem[y] = mem[x];}
};

class Command4:public Command{
public:
    Command4(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = mem[x]+mem[y];}
};

class Command5:public Command{
public:
    Command5(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = mem[x]-mem[y];}
};

class Command6:public Command{
public:
    Command6(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = mem[x]*mem[y];}
};

class Command7:public Command{
public:
    Command7(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = mem[x]/mem[y];}
};

class Command8:public Command{
public:
    Command8(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = mem[x]%mem[y];}
};

class Command9:public Command{
public:
    Command9(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] == mem[y]);}
};

class Command10:public Command{
public:
    Command10(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] > mem[y]);}
};

class Command11:public Command{
public:
    Command11(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] < mem[y]);}
};

class Command12:public Command{
public:
    Command12(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] && mem[y]);}
};

class Command13:public Command{
public:
    Command13(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] || mem[y]);}
};

class Command14:public Command{
public:
    Command14(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){mem[y] = !mem[x];}
};

class Command15:public Command{
public:
    Command15(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] & mem[y]);}
};

class Command16:public Command{
public:
    Command16(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] | mem[y]);}
};

class Command17:public Command{
public:
    Command17(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] ^ mem[y]);}
};

class Command18:public Command{
public:
    Command18(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] << mem[y]);}
};

class Command19:public Command{
public:
    Command19(int _x,int _y,int _z):Command(_x,_y,_z){}
    virtual void execute(){mem[z] = (mem[x] >> mem[y]);}
};


class Command20:public Command{
public:
    Command20(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){}
    virtual void ripIncrement() override{
        if(mem[x]) rip = y;
        else rip++;
    }
};

class Command30:public Command{
public:
    Command30(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){}
    virtual void ripIncrement() override{rip = x;}
};

class Command40:public Command{
public:
    Command40(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){}
    virtual void ripIncrement() override{rip = mem[x];}
};

class Command50:public Command{
public:
    Command50(int _x,int _y = 0,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){std::cout << mem[x] << ' ';}
};

class Command60:public Command{
public:
    Command60(int _x,int _y = 0,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){std::cin >> mem[x];}
};

class Command70:public Command{
public:
    Command70(int _x,int _y = 0,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){std::cout << (char)mem[x] << ' ';}
};

// class Command80:public Command{
// public:
//     public:
//     Command80(int _x,int _y,int _z = 0):Command(_x,_y,_z){}
//     virtual ~Command80() = default;
//     virtual void execute(){}
//     virtual void ripIncrement() override{
//         if(mem[x]) rip = mem[y];
//         else rip++;
//     }
// };

class Command100:public Command{
public:
    Command100(int _x = 0,int _y = 0,int _z = 0):Command(_x,_y,_z){}
    virtual void execute(){
        std::cerr << "successfully exit" << std::endl;
        exit(1);
    }
};

namespace cmdCreator{
    Command* f0(int x,int y,int z){ return new Command0(x,y,z);}
    Command* f1 (int x,int y,int z){ return new Command1(x,y,z);}
    Command* f2 (int x,int y,int z){ return new Command2(x,y,z);}
    Command* f3 (int x,int y,int z){ return new Command3(x,y,z);}
    Command* f4 (int x,int y,int z){ return new Command4(x,y,z);}
    Command* f5 (int x,int y,int z){ return new Command5(x,y,z);}
    Command* f6 (int x,int y,int z){ return new Command6(x,y,z);}
    Command* f7 (int x,int y,int z){ return new Command7(x,y,z);}
    Command* f8 (int x,int y,int z){ return new Command8(x,y,z);}
    Command* f9 (int x,int y,int z){ return new Command9(x,y,z);}
    Command* f10 (int x,int y,int z){ return new Command10(x,y,z);}
    Command* f11 (int x,int y,int z){ return new Command11(x,y,z);}
    Command* f12 (int x,int y,int z){ return new Command12(x,y,z);}
    Command* f13 (int x,int y,int z){ return new Command13(x,y,z);}
    Command* f14 (int x,int y,int z){ return new Command14(x,y,z);}
    Command* f15 (int x,int y,int z){ return new Command15(x,y,z);}
    Command* f16 (int x,int y,int z){ return new Command16(x,y,z);}
    Command* f17 (int x,int y,int z){ return new Command17(x,y,z);}
    Command* f18 (int x,int y,int z){ return new Command18(x,y,z);}
    Command* f19 (int x,int y,int z){ return new Command19(x,y,z);}    
    Command* f20 (int x,int y,int z){ return new Command20(x,y,z);}
    Command* f30 (int x,int y,int z){ return new Command30(x,y,z);}
    Command* f40 (int x,int y,int z){ return new Command40(x,y,z);}
    Command* f50 (int x,int y,int z){ return new Command50(x,y,z);}
    Command* f60 (int x,int y,int z){ return new Command60(x,y,z);}
    Command* f70 (int x,int y,int z){ return new Command70(x,y,z);}
    Command* f100 (int x,int y,int z){ return new Command100(x,y,z);}
}

std::map<int,std::function<Command*(int,int,int)>> cmdTable = {
    {0,cmdCreator::f0},
    {1,cmdCreator::f1},
    {2,cmdCreator::f2},
    {3,cmdCreator::f3},
    {4,cmdCreator::f4},
    {5,cmdCreator::f5},
    {6,cmdCreator::f6},
    {7,cmdCreator::f7},
    {8,cmdCreator::f8},
    {9,cmdCreator::f9},
    {10,cmdCreator::f10},
    {11,cmdCreator::f11},
    {12,cmdCreator::f12},
    {13,cmdCreator::f13},
    {14,cmdCreator::f14},
    {15,cmdCreator::f15},
    {16,cmdCreator::f16},
    {17,cmdCreator::f17},
    {18,cmdCreator::f18},
    {19,cmdCreator::f19},
    {20,cmdCreator::f20},
    {30,cmdCreator::f30},
    {40,cmdCreator::f40},
    {50,cmdCreator::f50},
    {60,cmdCreator::f60},
    {70,cmdCreator::f70},
    {100,cmdCreator::f100}
};

//#endif

using namespace std;

int main(){
    int tt,op,x,y,z;
    cin >> tt;
    for(int i = 0;i < tt;i++){
        cin >> op;
        x = y = z = 0;
        if(op == 100)
            ;
        else if(op == 50 || op == 60 || op == 30 || op == 40 || op == 70)
            cin >> x;
        else if(op == 0 || op == 3 || op == 14 || op == 20)
            cin >> x >> y;
        else 
            cin >> x >> y >> z;
        cmdlst[i] = cmdTable[op](x,y,z);
    }
    rip = 0;
    while(true){
        cmdlst[rip]->execute();
        cmdlst[rip]->ripIncrement();
    }
    return 0;
}