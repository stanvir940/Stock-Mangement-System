#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<ctime>
using namespace std;

// This is the product class. Here we defined the attributes of the products and there are some method of that products.

class Product{
    private:
    string name;
    int quantity;
    int shareIndex;
    public:
    Product(string name,int quantity,int shareIndex): name(name),quantity(quantity),shareIndex(shareIndex){}

    // getter and setter method to access data

    string getName() const {return name;}
    int getQuantity() const {return quantity;}
    int getIndex() const {return shareIndex;}

    // to update the product quantity and index.
    
    void updateProductQuantity(int Quantity){ quantity=Quantity;}

    // if the index is chaged then the stock of that product will also be changed
    // because we have to stock the product according to our stock market index

    void updateIndex(int ShareIndex){
        int x=ShareIndex-shareIndex;
        quantity=quantity+x*2;
        shareIndex=ShareIndex;

        }

};

class StockManagement{
    private:
    vector<Product>goods;
    public:

    void addProducts(const Product& products){
        goods.push_back(products);
    } 

    void display(ostream& out) const {
        out<< "Stock Final Report"<<endl;
        out<<"Update Time: "<<time(NULL)<<endl;
        out<<"-------------------"<<endl;
        for(const auto& products:goods){
            out<< "Product Name: "<< products.getName()<<endl;
            out<< "Quantity: "<< products.getQuantity()<<endl;
            out<< "Index: "<< products.getIndex()<<endl;
        }
    } 

    void updateIndex(const string& name,int index){
        for(auto & products: goods){
            if(products.getName()==name){
                products.updateIndex(index);
                return;
            }
        }
        cout<<"No such products found!"<<endl;
    }
};

int main()
{
    StockManagement a;

    // opening a file.
    ifstream inputFile("/Users/tanvirahmed/Downloads/input.txt"); // here it is the pathname of that input file 
    if(!inputFile){
        cout<<" Failed to open the input.txt file"<<endl;
        return -1;
    }

    string productName;
    int quantity;
    int index;

    while(inputFile >> productName >> quantity >> index){
        Product product(productName,quantity,index);
        a.addProducts(product);
    }
    inputFile.close();

    // opening file where the output will be written

    ofstream outputFile("/Users/tanvirahmed/Downloads/output.txt");

    // check if output.txt exist or not
    if(!outputFile){
        cout<<"No such a output file exists"<<endl;
        return -1;
    } 

    // display intial stage
    a.display(outputFile);

    // updating the index

    a.updateIndex("shirt",10);

    a.display(outputFile); // after updating the index

    outputFile.close();
    

    return 0;
}