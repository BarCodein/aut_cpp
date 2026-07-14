#include"aphw1.h"
//---define--
Matrix multiply(const Matrix& a, const Matrix& b);
Matrix transpose(const Matrix& a);
double det(Matrix& a);
Matrix inv(Matrix& a);
void show(Matrix& a);

Matrix getData(char* filename);
Matrix getX(Matrix& data);
Matrix gety(Matrix& data);

Matrix solve(char* filename);

//---implement---

void show(Matrix& a){
    for(auto line:a){
        for (auto item:line)
            printf("%lf ",item);
        printf("\n");
    }
}

static Matrix newMatrix(int x,int y){
    std::vector<double> newL(y);
    Matrix newM(x,newL);
    return newM;
}

static Matrix newMatrix(int x){
    return newMatrix(x,x);
}

Matrix transpose(const Matrix& a){
    int x=a.size();
    int y=a[0].size();
    Matrix oup = newMatrix(y,x);
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++){
            oup[j][i]=a[i][j];
        }
    
    return oup;
}

Matrix multiply(const Matrix& a,const Matrix& b){
    int ax=a.size(),ay=a[0].size();
    int bx=b.size(),by=b[0].size();
    if (ay!=bx)
        throw std::invalid_argument("first's colons must equals "
            "to second's rows\n");
    
    Matrix oup = newMatrix(ax,by);
    for(int i=0;i<ax;i++)
        for(int j=0;j<by;j++){
            double sum=0;
            for(int k=0;k<ay;k++)
                sum+=a[i][k]*b[k][j];
            oup[i][j]=sum;
        }
    return oup;
}

static double minor(Matrix& a,int x,int y){
    if(a.size()!=a[0].size())
        throw std::invalid_argument("");
    int size = a.size();
    Matrix mm=newMatrix(size-1);
    for(int i=0;i<size-1;i++)
        for(int j=0;j<size-1;j++){
            int dx=i,dy=j;
            if (dx>=x)dx++;
            if (dy>=y)dy++;
            mm[i][j]=a[dx][dy];
        }
    return pow(-1,x+y+2)*det(mm);

}

double det(Matrix& a){
    int ax=a.size(),ay=a[0].size();
    if(ax!=ay)
        throw std::invalid_argument("rows must equals colons\n");
    if (ax==2)
        return a[0][0]*a[1][1]-a[0][1]*a[1][0];
    if (ax==1)
        return a[0][0];
    double sum=0;
    for(int i=0;i<ax;i++)
        sum+=minor(a,i,0)*a[i][0];
    return sum;
}

Matrix inv(Matrix& a){
    if (a.size()!=a[0].size())
        throw std::invalid_argument("");
    int size = a.size();
    Matrix oup = newMatrix(size);
    double d = det(a);
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            oup[j][i] = minor(a,i,j)/d;
    return oup;
}

Matrix getData(char* filename){
    std::ifstream infile(filename);
    if (!infile){
        std::cerr<<"cannot open file "<<filename<<std::endl;
    }   
    std::string line;
    Matrix oup;
    while(std::getline(infile,line)){
        std::vector<std::string> nums;
        std::stringstream ss(line);
        std::string item;
        while(getline(ss,item,',')){
            nums.push_back(item);
        }
        double x = std::stof(nums[0]);
        double y = std::stof(nums[1]);
        std::vector<double> ln={1,x,sin(x),sqrt(x),y};
        oup.push_back(ln);
    }

    return oup;
}

Matrix getX(Matrix& data){
    Matrix oup;
    for(auto line:data){
        line.pop_back();
        oup.push_back(line);
    }
    return oup;
}

Matrix gety(Matrix& data){
    Matrix oup;
    for(auto line:data){
        oup.push_back({line.back()});
    }
    return oup;
}

Matrix solve(char* filename){
    Matrix oup;
    Matrix data = getData(filename);
    Matrix x = getX(data);
    Matrix y = gety(data);
    Matrix t;
    t = multiply(transpose(x),x);
    Matrix t2 = multiply(inv(t),transpose(x));
    oup = multiply(t2,y);
    return oup;

}

int mains(){

    // Matrix a={{1,2,3,4},{2,3,4,5}};
    // show(a);
    // Matrix b=transpose(a);
    // show(b);
    // Matrix mdet={{1,2,3},
    //              {0,4,0},
    //              {2,2,3}};
    // show(multiply(b,a));
    // std::cout<<det(mdet)<<std::endl;
    // show(inv(mdet));
    // show(multiply(mdet,inv(mdet)));
    // Matrix data = getData("D:/codes/ap1399-2-hw1-master/data.txt");
    // show(data);
    // show(getX(data));
    // show(gety(data));
    //show(solve("data.txt"));
    Matrix w=solve("../data.txt");
    show (w);
    return 0;
}